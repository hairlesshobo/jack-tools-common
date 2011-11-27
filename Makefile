OBJ =	alsa-seq-endpoint.o \
	alsa-seq-listener.o \
	alsa-seq-print.o \
	alsa-seq-send.o \
	byte-order.o \
	client.o \
	file.o \
	img.o \
	img-ppm.o \
	jack-client.o \
	jack-port.o \
	jack-ringbuffer.o \
	jack-transport.o \
	memory.o \
	network.o \
	observe-signal.o \
	osc.o \
	rand.o \
	signal-clip.o \
	signal-copy.o \
	signal-interleave.o \
	signal-interpolate.o \
	signal-print.o \
	sound-file.o \
	taus88.o \
	time-current.o \
	time-ntp.o \
	time-timespec.o \
	time-timeval.o \
	ximg.o \
	xregcomp.o

%.o : %.c %.h
	gcc -Wall -O2 -c $*.c

all: $(OBJ)
	ar -rcs lib-c-common.a $(OBJ)

clean:
	rm -f *.o *.a
