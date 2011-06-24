#include <alsa/asoundlib.h>

#include "alsa-seq-endpoint.h"
#include "failure.h"
#include "print.h"

/* Write the number of source and destination endpoints to respective
   counter locations. */

void alsa_seq_endpoint_count(snd_seq_t *seq, int *source_n, int *destination_n)
{
  *source_n = 0;
  *destination_n = 0;

  snd_seq_client_info_t *c;
  snd_seq_client_info_malloc(&c);
  snd_seq_client_info_set_client(c, -1);

  snd_seq_port_info_t *p;
  snd_seq_port_info_malloc(&p);

  while(snd_seq_query_next_client(seq, c) >= 0) {
    int  client;
    client = snd_seq_client_info_get_client(c);

    snd_seq_port_info_set_client(p, client);
    snd_seq_port_info_set_port(p, -1);
    while(snd_seq_query_next_port(seq, p) >= 0) {

      int  capability;
      capability = snd_seq_port_info_get_capability(p);
      if(capability & SND_SEQ_PORT_CAP_READ) {
	*source_n += 1;
      }
      if(capability & SND_SEQ_PORT_CAP_WRITE) {
	*destination_n += 1;
      }
    }
  }

  snd_seq_client_info_free(c);
  snd_seq_port_info_free(p);

  return;
}

/* Write the name of the endpoint `e' to `device_name' and
   `port_name'. */

void alsa_seq_endpoint_name(snd_seq_t *seq, const alsa_seq_endpoint_t *e,
			    char *device_name, char *port_name, int size)
{
  snd_seq_client_info_t *c;
  snd_seq_client_info_malloc(&c);
  snd_seq_get_any_client_info( seq, e->client, c);
  if(device_name) {
    strncpy(device_name, snd_seq_client_info_get_name(c), size);
  }
  snd_seq_client_info_free(c);

  snd_seq_port_info_t *p;
  snd_seq_port_info_malloc(&p);
  snd_seq_get_any_port_info( seq, e->client, e->port, p);
  if(port_name) {
    strncpy(port_name, snd_seq_port_info_get_name(p), size);
  }
  snd_seq_port_info_free(p);

  return;
}

/* Print the endpoint `e' to stderr. */

void alsa_seq_endpoint_print(snd_seq_t *seq, const alsa_seq_endpoint_t *e)
{
  const int size = 512;
  char client_name[size];
  char port_name[size];
  alsa_seq_endpoint_name(seq, e, client_name, port_name, size);
  eprintf("Endpoint:\n");
  eprintf("  Client      : %d, '%s'\n", e->client, client_name);
  eprintf("  Port        : %d, '%s'\n", e->port, port_name);
  eprintf("  Source      : %s\n", e->source ? "Yes" : "No");
  eprintf("  Destination : %s\n", e->destination ? "Yes" : "No");
}

/* Print the `e_n' endpoints at `e' to stderr. */

void alsa_seq_endpoint_print_set(snd_seq_t *seq,
				 const alsa_seq_endpoint_t *e, int e_n)
{
  int i;
  for(i = 0; i < e_n; i++) {
    alsa_seq_endpoint_print(seq, e + i);
  }
}

/* Allocate required memory and read the set of endpoints at `seq'
   into `source' and `destination.  This allows endpoints to be
   addressed using zero indexed <integer> values. */

void alsa_seq_endpoint_read(snd_seq_t *seq,
			    alsa_seq_endpoint_t **source,
			    int *source_n,
			    alsa_seq_endpoint_t **destination,
			    int *destination_n)
{
  alsa_seq_endpoint_count(seq, source_n, destination_n);

  alsa_seq_endpoint_t *s;
  s = malloc(*source_n * sizeof(alsa_seq_endpoint_t));

  alsa_seq_endpoint_t *d;
  d = malloc(*destination_n * sizeof(alsa_seq_endpoint_t));

  snd_seq_client_info_t *c;
  snd_seq_client_info_malloc(&c);
  snd_seq_client_info_set_client(c, -1);

  snd_seq_port_info_t *p;
  snd_seq_port_info_malloc(&p);

  int s_n;
  s_n = 0;

  int d_n;
  d_n = 0;

  while(snd_seq_query_next_client(seq, c) >= 0) {
    int  client;
    client = snd_seq_client_info_get_client(c);

    snd_seq_port_info_set_client(p, client);
    snd_seq_port_info_set_port(p, -1);

    while(snd_seq_query_next_port(seq, p) >= 0) {
      alsa_seq_endpoint_t e;
      e.client = snd_seq_port_info_get_client(p);
      e.port = snd_seq_port_info_get_port(p);

      int  capability;
      capability = snd_seq_port_info_get_capability(p);
      e.source = capability & SND_SEQ_PORT_CAP_READ;
      e.destination = capability & SND_SEQ_PORT_CAP_WRITE;

      if(e.source) {
	s[s_n] = e;
	s_n += 1;
	if(s_n > *source_n) {
	  eprintf("%s: source endpoint race triggered\n", __func__);
	  FAILURE;
	}
      }

      if(e.destination) {
	d[d_n] = e;
	d_n += 1;
	if(d_n > *destination_n) {
	  eprintf("%s: destination endpoint race triggered\n", __func__);
	  FAILURE;
	}
      }
    }
  }

  snd_seq_client_info_free(c);
  snd_seq_port_info_free(p);

  *source = s;
  *destination = d;

  return;
}

/* Establish a connection from each of the source endpoints to
   indicated port at `seq'. */

void alsa_seq_endpoint_connect_from(snd_seq_t *seq, int port,
				    const alsa_seq_endpoint_t *e, int e_n)
{
  int self;
  self = snd_seq_client_id(seq);
  int i;
  for(i = 0; i < e_n; i++) {
    if(e[i].source && e[i].client != self) {
      int err;
      err = snd_seq_connect_from(seq, port, e[i].client, e[i].port);
    }
  }
}

/* Establish a connection to each of the destination endpoints from
   indicated port at `seq'. */

void
alsa_seq_endpoint_connect_to(snd_seq_t *seq, int port,
			     const alsa_seq_endpoint_t *e, int e_n)
{
  int self;
  self = snd_seq_client_id(seq);
  int i;
  for(i = 0; i < e_n; i++) {
    if(e[i].source && e[i].client != self) {
      int err;
      err = snd_seq_connect_to(seq, port, e[i].client, e[i].port);
    }
  }
}

/* Get the index of of the endpoint for 'client' and 'port'. */

int alsa_seq_endpoint_index(const alsa_seq_endpoint_t *e, int e_n,
			    int client, int port)
{
  int i;
  for(i = 0; i < e_n; i++) {
    if(e[i].client == client && e[i].port == port) {
      return i;
    }
  }
  return -1;
}
