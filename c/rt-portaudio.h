#ifndef _COMMON_RT_PORTAUDIO_H
#define _COMMON_RT_PORTAUDIO_H

#include <portaudio.h>

typedef void rt_process_t(const float **in, float **out, int frameCount, void *userData);

typedef struct rt_sys {
	PaStream *s;
	rt_process_t *f;
	void *d;
} rt_sys_t;

rt_sys_t *rt_open(int numInputChannels, int numOutputChannels, double sampleRate, int framesPerBuffer, rt_process_t *f, void *d);
void rt_close(rt_sys_t *sys);

#endif
