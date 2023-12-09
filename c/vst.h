#ifndef _COMMON_VST_H
#define _COMMON_VST_H

#include "pluginterfaces/vst2.x/aeffectx.h" /* VST SDK */

typedef AEffect *(*PluginEntryProc)(audioMasterCallback audioMaster);

static VstIntPtr VSTCALLBACK
vst_callback(AEffect *effect, VstInt32 opcode, VstInt32 index, VstIntPtr value, void *ptr, float opt);

#define VST_MAX_MIDI_MESSAGES 64

struct VstEventSet {
	VstInt32 numEvents;
	VstIntPtr reserved;
	VstEvent *events[VST_MAX_MIDI_MESSAGES];
};

#endif
