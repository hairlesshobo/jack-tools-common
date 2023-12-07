prefix = $(HOME)/opt

alsa =	alsa-seq-endpoint.o \
	alsa-seq-listener.o \
	alsa-seq-print.o \
	alsa-seq-send.o

clk =	time-pause.o

gl =	gl-cube.o \
	gl-sphere.o \
	glu-screen-capture.o

jack =	jack-client.o \
	jack-port.o \
	jack-ringbuffer.o \
	jack-transport.o

pa =	rt-portaudio.o

png =	img-png.o

sf =	sf-sndfile.o

src =	resample-src.o

x11 =	x11.o \
	ximg.o

obj =	beq.o \
	bessel.o \
	bezier.o \
	biquad.o \
	byte-order.o \
	cfile.o \
	cfile-byte.o \
	client.o \
	clip.o \
	colour.o \
	colour-rgba.o \
	compare.o \
	complex.o \
        cq.o \
	denormal.o \
	dl.o \
	dx7.o \
	file.o \
	filter.o \
	float.o \
	gen-trapezoid.o \
	hash.o \
	hermite.o \
	img.o \
	img-ppm.o \
	int.o \
	memory.o \
	midi.o \
	network.o \
	numeric-type.o \
	observe-signal.o \
	osc.o \
	plane.o \
	point.o \
	quantize.o \
	rand.o \
	ringbuffer.o \
	ringbuffer-fd.o \
	segment-transfer.o \
	sf-au.o \
	signal-clip.o \
	signal-copy.o \
	signal-interleave.o \
	signal-interpolate.o \
	signal-print.o \
	svf.o \
	taus88.o \
	time-current.o \
	time-ntp.o \
	time-timespec.o \
	time-timeval.o \
	trace.o \
	vector.o \
	window.o \
	xregcomp.o

CC = gcc # gcc clang
AR = ar # ar llvm-ar-13

CPPFLAGS += -g -Wall -pedantic -O3 -ffast-math
CFLAGS += -D_POSIX_C_SOURCE=200809 -std=c11

%.o : %.c %.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $*.c

all: $(obj)
	$(AR) -rcs lib-r-common.a $(obj)

clean:
	rm -f *.o *.a

indent:
	clang-format -i *.c

diff-ignoring-whitespace:
	git diff --ignore-space-at-eol --ignore-space-change --ignore-all-space
