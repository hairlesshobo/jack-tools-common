#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cfile.h"
#include "failure.h"
#include "int.h"
#include "memory.h"

#include "dx7.h"

/* Require p & q to be equal */
void u64_verify_eq(const char *err, u64 p, u64 q)
{
	die_when(p != q, "U64_VERIFY_EQ: %s: 0x%lX != 0x%lX\n", err, (unsigned long)p, (unsigned long)q);
}

/* DX7 checksum algorithm */
u8 dx7_checksum(u8 *p, int n)
{
	u8 sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += (p[i] & 0x7F);
	}
	sum = (~sum) + 1;
	sum &= 0x7F;
	return sum;
}

/* Pack operator data, input is 21 bytes, output is 17 bytes */
struct dx7_operator_packed dx7_pack_operator(u8 *b)
{
	struct dx7_operator_packed o;
	memcpy(&(o.op_00_10), b, 11); /* b[0-10] are copied directly */
	o.op_11 = b[11];
	o.op_12 = b[12];
	o.op_13 = b[13];
	o.op_14 = b[14];
	o.op_15 = b[15];
	o.op_16 = b[16];
	o.op_17 = b[17];
	o.op_18 = b[18];
	o.op_19 = b[19];
	o.op_20 = b[20];
	return o;
}

/* Pack voice data, input is 155 bytes (6 * 21 + 29), output is 128 bytes */
struct dx7_voice_packed dx7_pack_voice(u8 *b)
{
	struct dx7_voice_packed v;
	for (int i = 0; i < 6; i++) {
		v.op[i] = dx7_pack_operator(b + (i * 21));
	}
	memcpy(&(v.vc_126_133), b + 126, 8);
	v.vc_134 = b[134];
	v.vc_135 = b[135];
	v.vc_136 = b[136];
	memcpy(&(v.vc_137_140), b + 137, 4);
	v.vc_141 = b[141];
	v.vc_142 = b[142];
	v.vc_143 = b[143];
	v.vc_144 = b[144];
	memcpy(&(v.vc_145_154), b + 145, 10);
	return v;
}

/* Pack 32 voice sequence, input is 4960 bytes (32 * 155), output is 4096 bytes (32 * 128) */
struct dx7_bank_packed dx7_pack_bank(u8 *d)
{
	struct dx7_bank_packed b;
	for (int i = 0; i < 32; i++) {
		b.vc[i] = dx7_pack_voice(d + (i * 155));
	}
	return b;
}

/* Inverse of dx7_pack_operator */
void dx7_unpack_operator(struct dx7_operator_packed o, u8 *b)
{
	memcpy(b, o.op_00_10, 11); /* b[0-10] are copied directly */
	b[11] = o.op_11;
	b[12] = o.op_12;
	b[13] = o.op_13;
	b[14] = o.op_14;
	b[15] = o.op_15;
	b[16] = o.op_16;
	b[17] = o.op_17;
	b[18] = o.op_18;
	b[19] = o.op_19;
	b[20] = o.op_20;
}

/* Inverse of dx7_pack_voice */
void dx7_unpack_voice(struct dx7_voice_packed v, u8 *b)
{
	for (int i = 0; i < 6; i++) {
		dx7_unpack_operator(v.op[i], b + (i * 21));
	}
	memcpy(b + 126, v.vc_126_133, 8);
	b[134] = v.vc_134;
	b[135] = v.vc_135;
	b[136] = v.vc_136;
	memcpy(b + 137, v.vc_137_140, 4);
	b[141] = v.vc_141;
	b[142] = v.vc_142;
	b[143] = v.vc_143;
	b[144] = v.vc_144;
	memcpy(b + 145, v.vc_145_154, 10);
}

/* Inverse of dx7_pack_bank */
void dx7_unpack_bank(struct dx7_bank_packed b, u8 *d)
{
	for (int i = 0; i < 32; i++) {
		dx7_unpack_voice(b.vc[i], d + (i * 155));
	}
}

/* DX7 FORMAT-9 SYSEX 6-byte header (channel=0x0) */
u8 dx7_fmt9_sy_begin[6] = { 0xF0, 0x43, 0x00, 0x09, 0x20, 0x00 };

/* DX7 FORMAT-9 sysex header verification */
void dx7_fmt9_sysex_verify(u8 *sy_begin, u8 *sy_dat, u8 *sy_end)
{
	u8_verify_eq("F0", sy_begin[0], 0xF0);
	u8_verify_eq("43", sy_begin[1], 0x43);
	u8_verify_eq("0.", sy_begin[2] >> 4, 0x00);
	u8_verify_eq("09", sy_begin[3], 0x09);
	u8_verify_eq("20", sy_begin[4], 0x20);
	u8_verify_eq("00", sy_begin[5], 0x00);
	u8_verify_eq("CS", sy_end[0], dx7_checksum(sy_dat, 4096));
	u8_verify_eq("F7", sy_end[1], 0xF7);
}

/* Copy the 10-byte VOICE NAME to s and add NUL terminal at index 10. */
void dx7_voice_name_cstr(const uint8_t *data, char *s)
{
	for (int i = 0; i < 10; i++) {
		s[i] = (char)data[145 + i];
	}
	s[10] = '\0';
}

/* Load 4104 byte FORMAT=9 DX7 sysex file and unpack data. */
void dx7_syx_load(const char *fn, uint8_t *data)
{
	uint8_t syx[4104];
	struct dx7_bank_packed b;
	FILE *fp = xfopen(fn, "rb");
	xfread(syx, 1, 4104, fp);
	fclose(fp);
	dx7_fmt9_sysex_verify(syx, syx + 6, syx + 4102);
	xmemcpy(&b, syx + 6, 4096);
	dx7_unpack_bank(b, data);
}

const uint8_t dx7_init_voice_static[155] = {
	/* OPERATORS */
	99, 99, 99, 99, 99, 99, 99, 00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7,
	99, 99, 99, 99, 99, 99, 99, 00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7,
	99, 99, 99, 99, 99, 99, 99, 00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7,
	99, 99, 99, 99, 99, 99, 99, 00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7,
	99, 99, 99, 99, 99, 99, 99, 00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7,
	99, 99, 99, 99, 99, 99, 99, 00, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 1, 0, 7,
	/* SHARED */
	99, 99, 99, 99, 50, 50, 50, 50, 0, 0, 1, 35, 0, 0, 0, 1, 0, 3, 24,
	/* VOICE NAME */
	73, 78, 73, 84, 32, 86, 79, 73, 67, 69
};

/* Copy of INIT VOICE data. */
void dx7_init_voice(uint8_t *d)
{
	memcpy(d, dx7_init_voice_static, 155);
}
