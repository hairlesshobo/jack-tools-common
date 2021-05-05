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
	complex.o \
        cq.o \
	denormal.o \
	dl.o \
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
	point.o \
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
	svf.o \
	taus88.o \
	time-current.o \
	time-ntp.o \
	time-pause.o \
	time-timespec.o \
	time-timeval.o \
	trace.o \
	vector.o \
	window.o \
	x11.o \
	ximg.o \
	xregcomp.o

CC = gcc # gcc clang
AR = ar # ar llvm-ar

CPPFLAGS += -g -Wall -pedantic -O2 -ffast-math
CFLAGS += -D_POSIX_C_SOURCE=200809 -std=c11

%.o : %.c %.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $*.c

all: $(obj)
	$(AR) -rcs lib-c-commonr.a $(obj)

clean:
	rm -f *.o *.a

indent:
	indent -kr -nut sf-au.c

GL_GIT=git@gitlab.com:rd--/c-commonr.git
GL_HTTP=https://gitlab.com/rd--/c-commonr.git

push-gl:
	git push $(GL_GIT)

push-gl-tags:
	git push $(GH_GIT) --tag

pull-gl:
	git pull $(GL_HTTP)

update-rd:
	ssh rd@rohandrape.net "(cd sw/c-commonr ; git pull $(GL_HTTP))"

push-all:
	make push-gl update-rd
