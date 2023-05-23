bin = rt-portaudio

CC = gcc # gcc clang
AR = ar # ar llvm-ar

CPPFLAGS += -Wall -pedantic -g -ffast-math
CFLAGS += -D_POSIX_C_SOURCE=200809 -std=c99
LDLIBS = ../c/lib-r-common.a -lm

all: $(bin)

rt-portaudio: rt-portaudio.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o rt-portaudio rt-portaudio.c $(LDLIBS) -lportaudio

clean:
	rm -f $(bin) *.o
