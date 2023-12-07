#include <alsa/asoundlib.h>

#include "alsa-seq-print.h"
#include "print.h"

/* Print some basic system information to stderr. */

void alsa_seq_print_system_info(snd_seq_t *seq)
{
	snd_seq_system_info_t *info;
	snd_seq_system_info_malloc(&info);
	snd_seq_system_info(seq, info);
	eprintf("System Information:\n");
	eprintf("Number of queues          : %d\n",
		snd_seq_system_info_get_queues(info));
	eprintf("Number of clients         : %d\n",
		snd_seq_system_info_get_clients(info));
	eprintf("Number of ports           : %d\n",
		snd_seq_system_info_get_ports(info));
	eprintf("Number of channels        : %d\n",
		snd_seq_system_info_get_channels(info));
	eprintf("Number of current clients : %d\n",
		snd_seq_system_info_get_cur_clients(info));
	eprintf("Number of current queues  : %d\n",
		snd_seq_system_info_get_cur_queues(info));
	snd_seq_system_info_free(info);
	return;
}
