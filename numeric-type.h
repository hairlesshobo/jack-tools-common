#ifndef _COMMON_NUMERIC_TYPE_H
#define _COMMON_NUMERIC_TYPE_H

enum numeric_type {u8_ty,i8_ty,i16_ty,f32_ty};
enum numeric_type numeric_type_parse(const char *s);
void numeric_type_pp(enum numeric_type ty,char *s);
size_t numeric_type_sz(enum numeric_type ty);

#endif
