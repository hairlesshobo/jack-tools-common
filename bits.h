#ifndef _COMMON_BITS_H
#define _COMMON_BIST_H

/* printf("..."BYTE_TO_BINARY_PRINTF_PATTERN"...", ..., BYTE_TO_BINARY_CHAR_SEQUENCE(x), ...) */

#define BYTE_TO_BINARY_PRINTF_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY_CHAR_SEQUENCE(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

#endif
