#include <stdbool.h>

#include "int.h"

/* https://www.midi.org/specifications/item/table-1-summary-of-midi-message */
#define MIDI_Note_Off            0x80
#define MIDI_Note_On             0x90
#define MIDI_Aftertouch          0xA0 /* Polyphonic Key Pressure */
#define MIDI_Control_Change      0xB0
#define MIDI_Program_Change      0xC0
#define MIDI_Channel_Pressure    0xD0 /* Aftertouch */
#define MIDI_Pitch_Bend          0xE0

u8 status_ty(u8 st);
u8 status_ch(u8 st);
bool is_note_data(u8 ty);
