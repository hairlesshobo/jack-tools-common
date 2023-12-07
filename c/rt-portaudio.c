#include <stdio.h>
#include <stdlib.h>

#include <portaudio.h>

#include "rt-portaudio.h"

int pa_callback(const void *in, void *out, unsigned long frameCount, const PaStreamCallbackTimeInfo *time, PaStreamCallbackFlags status, void *user)
{
	rt_sys_t *p = (rt_sys_t *)user;
	// fprintf(stderr, "pa_callback: in=%p out=%p frameCount=%lu user=%p f=%p d=%p\n", in, out, frameCount, user, (void *)p->f, p->d);
	p->f((const float **)in, (float **)out, (int)frameCount, p->d);
	return paContinue;
}

void pa_die_on_error(PaError err)
{
	if (err != paNoError) {
		fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText(err));
		exit(1);
	}
}

rt_sys_t *rt_open(int numInputChannels, int numOutputChannels, double sampleRate, int framesPerBuffer, rt_process_t *f, void *d)
{
	rt_sys_t *p = malloc(sizeof(rt_sys_t));
	p->f = f;
	p->d = d;
	pa_die_on_error(Pa_Initialize());
	pa_die_on_error(
		Pa_OpenDefaultStream(
			&(p->s),
			numInputChannels,
			numOutputChannels,
			paFloat32 | paNonInterleaved,
			sampleRate,
			(unsigned long)framesPerBuffer,
			pa_callback,
			(void *)p));
	pa_die_on_error(Pa_StartStream(p->s));
	return p;
}

void rt_close(rt_sys_t *sys)
{
	pa_die_on_error(Pa_StopStream(sys->s));
	pa_die_on_error(Pa_Terminate());
	free(sys);
}
