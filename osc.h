#ifndef _COMMON_OSC_H
#define _COMMON_OSC_H

#include <stdint.h>
#include <stdbool.h>

#include "int.h"
#include "float.h"

typedef struct
{
  const u8 *data;
  i32 size;
} osc_blob_t;

typedef union
{
  i32 i; /* Signed Integer (32 bits) */
  i64 h; /* Signed Integer (64 bits) */
  u64 t; /* NTP TimeStamp */
  f32 f; /* IEEE Float (32 bits) */
  f64 d; /* IEEE Float (64 bits) */
  const char *s; /* ASCII String (NULL suffix) */
  const char *S; /* Symbol */
  u32 c; /* ASCII Character */
  u32 m; /* MIDI message (4 bytes) */
  u32 r; /* RGBA Colour (4 bytes) */
  osc_blob_t b; /* Blob (bytestring) */
} osc_data_t;

typedef struct
{
  u8 type;
  osc_data_t value;
} osc_arg_t;

i32 osc_align(i32 n);
i32 osc_cstr_bound(i32 n);
i32 osc_blob_bound(i32 n);
void osc_print_packet(const u8 *packet, i32 packet_sz);
bool osc_is_numerical_type(u8 c);
bool osc_is_string_type(u8 c);
bool osc_can_coerce(u8 u, u8 d);
void osc_coerce(u8 u, u8 d, osc_data_t *o);
void osc_coerce_arguments(const char *u_dsc, const char *p_dsc, osc_data_t *data);
i32 osc_collect_arguments(const char *dsc, const u8 *p, osc_data_t *data);
i32 osc_pack_arguments(const char *dsc, const osc_data_t *data, u8 *p);
i32 osc_dsc_read_arg_len(const char *dsc, const u8 *p);
i32 osc_dsc_calculate_arg_len(const char *dsc, const osc_data_t *data);
i32 osc_match_address(const char *addr, const u8 *packet);
i32 osc_match_dsc(const char *u_dsc, const char *p_dsc);
i32 osc_parse_message(const char *addr, const char *dsc, const u8 *packet, i32 packet_sz, osc_data_t *data);
i32 osc_construct_message(const char *addr, const char *dsc, const osc_data_t *data, u8 *packet, i32 packet_sz);
i32 osc_build_message(u8 *packet, i32 packet_sz, const char *addr, const char *dsc, ...);

#ifdef DEBUG
#define osc_debug_print(pkt,sz) osc_print_packet(pkt,sz);
#else
#define osc_debug_print(pkt,sz)
#endif

#endif
