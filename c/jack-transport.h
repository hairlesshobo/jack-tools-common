#ifndef _COMMON_JACK_TRANSPORT_H
#define _COMMON_JACK_TRANSPORT_H

#include <jack/jack.h>
#include <stdbool.h>

bool jack_transport_is_rolling(jack_client_t *client);

#endif
