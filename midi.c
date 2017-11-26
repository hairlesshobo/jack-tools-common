#include "midi.h"

u8 status_ty(u8 st) {return (st >> 4);}
u8 status_ch(u8 st) {return (st & 0x0F);}
bool is_note_data(u8 ty) {return (ty == 0x8 || ty == 0x9);}
