#include "midi.h"

u8 status_ty(u8 st)
{
	return (st >> 4);
}

u8 status_ch(u8 st)
{
	return (st & 0x0F);
}

bool is_note_data(u8 st)
{
	u8 ty = status_ty(st);
	return (ty == 0x8 || ty == 0x9);
}

bool is_channel_voice_message(u8 st)
{
	u8 n = status_ty(st);
	return (n >= 0x8 && n < 0xF);
}

bool is_sysex_message(u8 st)
{
	return st == 0xF0;
}

u16 u14_combine(u8 d1, u8 d2)
{
	return (((u16)d2 << 7) | (u16)d1);
}
