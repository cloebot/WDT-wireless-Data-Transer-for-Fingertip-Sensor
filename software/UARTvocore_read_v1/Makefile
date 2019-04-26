PROFILE = -O2 -s
CFLAGS = $(PROFILE)
LIBS = -DDISPLAY_STRING
CC = /home/cloe/openwrt/staging_dir/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/bin/mipsel-openwrt-linux-gcc

all: main

# build it
main:
	$(CC) -g main.c $(LIBS) -o vocoreUARTRead

# clean it
clean:
	rm vocoreUARTRead
