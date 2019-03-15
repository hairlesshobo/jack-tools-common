#ifndef _COMMON_CFILE_BYTE_H
#define _COMMON_CFILE_BYTE_H

u16 fread_u16(FILE *fp);
u32 fread_u32(FILE *fp);
u64 fread_u64(FILE *fp);
i16 fread_i16(FILE *fp);
i32 fread_i32(FILE *fp);
i64 fread_i64(FILE *fp);
f32 fread_f32(FILE *fp);
f64 fread_f64(FILE *fp);

#endif
