#include "pluginterfaces/vst2.x/aeffectx.h" /* VST SDK */

#include "dl.h"
#include "failure.h"
#include "vst.h"

void vst_verify_platform(void)
{
    printf("HOST> SIZEOF VSTINTPTR = %lu\n", sizeof(VstIntPtr));
    printf("HOST> SIZEOF VSTINT32 = %lu\n", sizeof(VstInt32));
    printf("HOST> SIZEOF VOID* = %lu\n", sizeof(void *));
    printf("HOST> SIZEOF AEFFECT = %lu\n", sizeof(AEffect));
    if (sizeof(VstIntPtr) != sizeof(void *)) {
        printf("HOST> PLATFORM VERIFICATION FAILED\n");
        exit(EXIT_FAILURE);
    }
}


/* Print VST parameter data (IX, NAME, LABEL, DISPLAY) */
void vst_param_pp(AEffect *e)
{
    for (VstInt32 i = 0; i < e->numParams; i++) {
        char nm[kVstMaxParamStrLen];
        char lbl[kVstMaxParamStrLen];
        char disp[kVstMaxParamStrLen];
        e->dispatcher (e, effGetParamName, i, 0, nm, 0);
        e->dispatcher (e, effGetParamLabel, i, 0, lbl, 0);
        e->dispatcher (e, effGetParamDisplay, i, 0, disp, 0);
        printf ("HOST> PARAM> %03d, %s, %s, %s\n", i, nm, disp, lbl);
    }
}

/* e = effect, c = opcode, i = index, v = value, p = ptr, o = opt */
VstIntPtr VSTCALLBACK
vst_callback(AEffect * e, VstInt32 c, VstInt32 i, VstIntPtr v, void *p, float o)
{
    VstIntPtr result = 0;
    switch (c) {
    case audioMasterVersion:
        result = kVstVersion;
        break;
    }
    return result;
}

/* m is a DL module. 1. dlsym VSTPluginMain; 2. run with vst_callback; 3. call effOpen */
AEffect *vst_begin(void *m)
{
    PluginEntryProc f = (PluginEntryProc)xdlsym(m, "VSTPluginMain");
    printf("HOST> RUN VSTPLUGINMAIN\n");
    AEffect *e = f(vst_callback);
    die_when(e == NULL,"HOST> VSTPLUGINMAIN FAILED\n");
    printf("HOST> CALL EFFOPEN\n");
    e->dispatcher(e, effOpen, 0, 0, 0, 0);
    return e;
}

void vst_set_program(AEffect *e,VstInt32 k)
{
    if (k < e->numPrograms) {
        e->dispatcher(e, effSetProgram, 0, k, NULL, 0);
    }
}

bool vst_check_midi(AEffect *e)
{
    return (e->dispatcher(e, effCanDo, 0, 0, (void *)"receiveVstMidiEvent", 0) == 1);
}

void vst_require_midi(AEffect *e)
{
    printf("HOST> REQUIRE MIDI I/O\n");
    die_when(!vst_check_midi(e),"HOST> NO MIDI I/O\n");
}

void vst_require_audio_io(AEffect *e,VstInt32 i,VstInt32 o)
{
    printf("HOST> REQUIRE AUDIO I/O\n");
    if ((e->numInputs != i) || (e->numOutputs != o)) {
        die("HOST> NOT %d-IN/%d-OUT\n",(int)i, (int)o);
    }
}
