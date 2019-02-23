#include "midi.h"

u8 status_ty(u8 st) {
    return (st >> 4);
}

u8 status_ch(u8 st) {
    return (st & 0x0F);
}

bool is_note_data_ty(u8 ty) {
    return (ty == 0x8 || ty == 0x9);
}

bool is_note_data(u8 st) {
    return is_note_data_ty(status_ty(st));
}

bool is_channel_voice_message(u8 st) {
    u8 n = status_ty(st);
    return (n >= 0x8 && n < 0xF);
}

bool is_sysex_message(u8 st) {
    return st == 0xF0;
}
