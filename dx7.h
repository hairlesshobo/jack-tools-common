#ifndef _COMMON_DX7_H
#define _COMMON_DX7_H

#include "int.h"

/* 21 operator parameters (0 - 20) packed into 17 bytes */
struct dx7_operator_packed
{
    u8 op_00_10[11];
    u8 op_11 : 2; u8 op_12 : 2; u8 : 4;
    u8 op_13 : 3; u8 op_20 : 4; unsigned : 1;
    u8 op_14 : 2; u8 op_15 : 3; u8 : 3;
    u8 op_16;
    u8 op_17 : 1; u8 op_18 : 5; u8 : 2;
    u8 op_19;
};

/* (17 * 6) + 16 + 10 = 128 ; 19 shared parameters (126 - 144) packed into 16 bytes */
struct dx7_voice_packed
{
    struct dx7_operator_packed op[6];
    u8 vc_126_133[8];
    u8 vc_134 : 5; u8 : 3;
    u8 vc_135 : 3; u8 vc_136 : 1; u8 : 4;
    u8 vc_137_140[4];
    u8 vc_141 : 1; u8 vc_142 : 3; u8 vc_143 : 4;
    u8 vc_144;
    u8 vc_145_154[10];
};

/* DX7 FORMAT=9 SYSEX ; 6 + (32 * 128) + 2 = 4104 */
struct dx7_fmt9_sysex
{
    u8 sy_begin[6];
    struct dx7_voice_packed vc[32];
    u8 sy_end[2];
};

void u64_verify_eq(char *err,u64 p,u64 q);
#define u8_verify_eq(err,p,q) u64_verify_eq(err,(u64)p,(u64)q)

u8 dx7_checksum(u8 *p,int n);
void dx7_fmt9_sysex_verify(struct dx7_fmt9_sysex *sysex);
struct dx7_operator_packed dx7_pack_operator(u8 *b);
struct dx7_voice_packed dx7_pack_voice(u8 *b);
struct dx7_fmt9_sysex dx7_pack_fmt9_sysex(u8 *b);
void dx7_unpack_operator(struct dx7_operator_packed o,u8 *b);
void dx7_unpack_voice(struct dx7_voice_packed v,u8 *b);
void dx7_unpack_fmt9_sysex(struct dx7_fmt9_sysex s,u8 *b);


#endif
