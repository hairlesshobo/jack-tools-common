PREFIX = $(HOME)/opt
OBJ =	alsa-seq-endpoint.o \
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
	img-ppm.o \
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
	rgba.o \
	segment-transfer.o \
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
	trace.o \
	vector.o \
	window.o \
	ximg.o \
	xregcomp.o

%.o : %.c %.h
	gcc -Wall -O2 -c $*.c

all: $(OBJ)
	ar -rcs lib-c-common.a $(OBJ)

clean:
	rm -f *.o *.a

install:
	cp lib-c-common.a $(PREFIX)/lib
	mkdir -p $(PREFIX)/include/c-common
	cp *.h $(PREFIX)/include/c-common

uninstall:
	rm -f $(PREFIX)/lib/lib-c-common.a
	rm -Rf $(PREFIX)/include/c-common
