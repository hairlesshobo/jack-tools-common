#include <alsa/asoundlib.h>

#include "alsa-seq-send.h"
#include "int.h"
#include "print.h"

/* Make a basic seq queue. */
int alsa_seq_make_default_queue(snd_seq_t *seq)
{
  int queue;
  queue = snd_seq_alloc_queue(seq);
  snd_seq_start_queue(seq, queue, 0);
  snd_seq_drain_output(seq);
  return queue;
}

/* Apart from setting the event destination, all the code for _send
   and _send_to is shared. */
static void alsa_seq_send_common(snd_seq_t *seq, int queue,
				 int src_port,
				 snd_midi_event_t *encoder,
				 u8 *c, int n,
				 snd_seq_event_t e)
{
  if(n <= 0) {
    eprintf("%s: empty packet\n", __func__);
    return;
  }
  snd_seq_real_time_t time;
  int err;
  snd_seq_ev_set_source(&e, src_port);
  snd_midi_event_reset_encode(encoder);
  err = snd_midi_event_encode(encoder, c, n, &e);
  if(err < 0 || e.type == SND_SEQ_EVENT_NONE) {
    eprintf("%s: encoding failed: err=%d e.type=%d strerr=%s\n", __func__, err, e.type, snd_strerror(errno));
    return;
  }
  time.tv_sec = time.tv_nsec = 0;
  snd_seq_ev_schedule_real( &e, queue, 1, &time);
  err = snd_seq_event_output_direct(seq, &e);
  if(err < 0) {
    eprintf("%s: output failed: %s\n", __func__, snd_strerror(errno));
    return;
  }
}

/* Encode the MIDI data at `c' as an ALSA sequencer event and send it
   to the registered subscribers. */
void alsa_seq_send(snd_seq_t *seq, int queue,
		   int src_port,
		   snd_midi_event_t *encoder,
		   u8 *c, int n)
{
  snd_seq_event_t e;
  snd_seq_ev_clear(&e);
  snd_seq_ev_set_subs(&e);
  alsa_seq_send_common(seq, queue, src_port, encoder, c, n , e);
}

/* Encode the MIDI data at `c' as an ALSA sequencer event and send it
   to indicated destination port. */
void alsa_seq_send_to(snd_seq_t *seq, int queue,
		      int src_port,
		      int dst_client, int dst_port,
		      snd_midi_event_t *encoder,
		      u8 *c, int n)
{
  snd_seq_event_t e;
  snd_seq_ev_clear(&e);
  snd_seq_ev_set_dest(&e, dst_client, dst_port);
  alsa_seq_send_common(seq, queue, src_port, encoder, c, n , e);
}
