#ifndef _COMMON_ALSA_SEQ_ENDPOINT_H
#define _COMMON_ALSA_SEQ_ENDPOINT_H

#include <stdbool.h>
#include <alsa/asoundlib.h>

typedef struct
{
  int client;
  int port;
  bool source;
  bool destination;
} alsa_seq_endpoint_t;

void
alsa_seq_endpoint_count(snd_seq_t *seq, int *source_n, int *destination_n);

void
alsa_seq_endpoint_name(snd_seq_t *seq, const alsa_seq_endpoint_t *e,
		       char *device_name, char *port_name, int size);

void
alsa_seq_endpoint_print(snd_seq_t *seq, const alsa_seq_endpoint_t *e);

void
alsa_seq_endpoint_print_set(snd_seq_t *seq, const alsa_seq_endpoint_t *e, int e_n);

void
alsa_seq_endpoint_read(snd_seq_t *seq,
		       alsa_seq_endpoint_t **source, int *source_n,
		       alsa_seq_endpoint_t **destination, int *destination_n);

void
alsa_seq_endpoint_connect_from(snd_seq_t *seq, int port,
			       const alsa_seq_endpoint_t *e, int e_n);

void
alsa_seq_endpoint_connect_to(snd_seq_t *seq, int port,
			     const alsa_seq_endpoint_t *e, int e_n);

int
alsa_seq_endpoint_index(const alsa_seq_endpoint_t *e, int e_n,
			int client, int port);

#endif

