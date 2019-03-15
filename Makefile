prefix = $(HOME)/opt

obj =	alsa-seq-endpoint.o \
	alsa-seq-listener.o \
	alsa-seq-print.o \
	alsa-seq-send.o \
	bessel.o \
	bezier.o \
	byte-order.o \
	cfile.o cfile-byte.o \
	client.o \
	clip.o \
	colour.o \
	colour-rgba.o \
        cq.o \
	dx7.o \
	file.o \
	gen-trapezoid.o \
	gl-cube.o \
	gl-sphere.o \
	glu-screen-capture.o \
	hermite.o \
	img.o \
	img-png.o \
	img-ppm.o \
	int.o \
	jack-client.o \
	jack-port.o \
	jack-ringbuffer.o \
	jack-transport.o \
	memory.o \
	midi.o \
	network.o \
	numeric-type.o\
	observe-signal.o \
	osc.o \
	plane.o \
	quantize.o \
	rand.o \
	resample-src.o \
	segment-transfer.o \
	sf-au.o \
	sf-sndfile.o \
	signal-clip.o \
	signal-copy.o \
	signal-interleave.o \
	signal-interpolate.o \
	signal-print.o \
	taus88.o \
	time-current.o \
	time-ntp.o \
	time-pause.o \
	time-timespec.o \
	time-timeval.o \
	trace.o \
	vector.o \
	window.o \
	ximg.o \
	xregcomp.o

CPPFLAGS += -g -Wall -pedantic -O2

%.o : %.c %.h
	gcc $(CPPFLAGS) $(CFLAGS) -c $*.c

all: $(obj)
	ar -rcs lib-c-common.a $(obj)

clean:
	rm -f *.o *.a

install:
	cp lib-c-common.a $(prefix)/lib
	mkdir -p $(prefix)/include/c-common
	cp *.h $(prefix)/include/c-common

uninstall:
	rm -f $(prefix)/lib/lib-c-common.a
	rm -Rf $(prefix)/include/c-common

push-rd:
	darcs push -a rd@rohandrape.net:sw/c-common

pull-rd:
	darcs pull -a http://rohandrape.net/sw/c-common

indent:
	indent -kr -nut sf-au.c
