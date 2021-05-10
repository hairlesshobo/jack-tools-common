#include <string.h>

#include "int.h"
#include "failure.h"
#include "float.h"
#include "numeric-type.h"

enum numeric_type numeric_type_parse(const char *s)
{
  if(strncmp(s,"u8",2) == 0) return u8_ty;
  if(strncmp(s,"i8",2) == 0) return i8_ty;
  if(strncmp(s,"i16",3) == 0) return i16_ty;
  if(strncmp(s,"f32",3) == 0) return f32_ty;
  FAILURE;
}

void numeric_type_pp(enum numeric_type ty,char *s)
{
  switch(ty) {
    case u8_ty: strcpy(s,"u8"); break;
    case i8_ty: strcpy(s,"i8"); break;
    case i16_ty: strcpy(s,"i16"); break;
    case f32_ty: strcpy(s,"f32"); break;
  }
}

size_t numeric_type_sz(enum numeric_type ty)
{
  switch(ty) {
    case u8_ty: return 1;
    case i8_ty: return 1;
    case i16_ty: return 2;
    case f32_ty: return 4;
  }
  return 0;
}
