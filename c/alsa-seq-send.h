#ifndef _COMMON_ALSA_SEQ_SEND_H
#define _COMMON_ALSA_SEQ_SEND_H

#include "int.h"
#include <alsa/asoundlib.h>

int alsa_seq_make_default_queue(snd_seq_t *seq);

void alsa_seq_send(snd_seq_t *seq, int queue,
	int port,
	snd_midi_event_t *encoder,
	u8 *c, int n);

void alsa_seq_send_to(snd_seq_t *seq, int queue,
	int src_port,
	int dst_client, int dst_port,
	snd_midi_event_t *encoder,
	u8 *c, int n);

#endif
