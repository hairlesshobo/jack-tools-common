#include <stdio.h>
#include <math.h>

#include "../c/rt-portaudio.h"
#include "../c/time-pause.h"

#define PI 3.14159265
#define TABLE_SIZE 200

struct sinOsc {
	float sine[TABLE_SIZE];
	int phase[2];
};

void process(const float **in, float **out, int framesPerBuffer, void *user) {
	struct sinOsc *data = (struct sinOsc *)user;
	//printf("out = %p = [%p, %p], phase = [%d, %d], framesPerBuffer = %d\n", (void *)out, (void *)out[0], (void *)out[1], data->phase[0], data->phase[1], framesPerBuffer);
	for(int c = 0; c < 2; c++ ) {
		for(int i = 0; i < framesPerBuffer; i++ ) {
			out[c][i] = data->sine[data->phase[c]] * 0.1;
			data->phase[c] += c == 0 ? 1 : 3;
			if(data->phase[c] >= TABLE_SIZE ) {
				data->phase[c] -= TABLE_SIZE;
			}
		}
	}
}

int main(void) {
	struct sinOsc data;
	for(int i = 0; i < TABLE_SIZE; i++) {
		data.sine[i] = sinf(((float)i / TABLE_SIZE) * PI * 2);
		// printf("sine[%d] = %f\n", i, data.sine[i]);
	}
	data.phase[0] = data.phase[1] = 0;
	rt_sys_t *sys = rt_open(0, 2, 48000, 48, process, &data);
	pause_for(23);
	rt_close(sys);
}
