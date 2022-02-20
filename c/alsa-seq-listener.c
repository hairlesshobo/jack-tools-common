#include <pthread.h>
#include <alsa/asoundlib.h>

#include "alsa-seq-listener.h"
#include "int.h"
#include "print.h"

/* ALSA provides a blocking read interface for midi data.  Create a
   thread that will listen at an input port and pass incoming packets
   to `reciever'. */

void alsa_seq_listener_debug_receiver(void *context, const snd_seq_event_t *event,
				      const u8 *data, int data_n)
{
  dprintf("%s: received packet: context=%p, event=%p, data=%p, data_n=%d\n",
	  __func__, context, event, data, data_n);
}

void *alsa_seq_listener_thread(void *PTR)
{
  alsa_seq_listener_t *l = (alsa_seq_listener_t *) PTR;
  while(true) {
    snd_seq_event_t *e;
    snd_seq_event_input(l->seq, &e);
    dprintf("%s: event received: e=%p\n", __func__, e);
    if(snd_seq_ev_is_channel_type(e) || e->type == SND_SEQ_EVENT_SYSEX) {
      int data_extent = 512;
      u8 data[data_extent];
      int data_n;
      data_n = snd_midi_event_decode(l->decoder, data, data_extent, e);
      l->receiver(l->context, e, data, data_n);
    }
  }
  return NULL;
}

pthread_t alsa_seq_listener(snd_seq_t *seq,
			    snd_midi_event_t *decoder,
			    alsa_seq_listener_recv_t receiver,
			    void *context)
{
  pthread_t thread;
  alsa_seq_listener_t *l;
  l = (alsa_seq_listener_t *)malloc(sizeof(alsa_seq_listener_t));
  l->seq = seq;
  l->decoder = decoder;
  l->receiver = receiver;
  l->context = context;
  pthread_create(&(thread), NULL, alsa_seq_listener_thread, l);
  return thread;
}
