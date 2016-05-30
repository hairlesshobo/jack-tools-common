prefix = $(HOME)/opt
obj =	alsa-seq-endpoint.o \
	alsa-seq-listener.o \
	alsa-seq-print.o \
	alsa-seq-send.o \
	bessel.o \
	byte-order.o \
	cfile.o \
	client.o \
	clip.o \
	cq.o \
	file.o \
	gen-trapezoid.o \
	gl-cube.o \
	gl-sphere.o \
	glu-screen-capture.o \
	img.o \
	img-png.o \
	img-ppm.o \
	int.o \
	jack-client.o \
	jack-port.o \
	jack-ringbuffer.o \
	jack-transport.o \
	memory.o \
	network.o \
	observe-signal.o \
	osc.o \
	plane.o \
	quantize.o \
	rand.o \
	resample-src.o \
	rgba.o \
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

%.o : %.c %.h
	gcc -g -Wall -pedantic -O2 -c $*.c

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

push-sp:
	darcs push -a rd@slavepianos.org:sw/c-common

pull-sp:
	darcs pull -a http://rd.slavepianos.org/sw/c-common

indent:
	indent -kr -nut sf-au.c
