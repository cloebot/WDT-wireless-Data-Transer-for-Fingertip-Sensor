PROFILE = -O2 -s
CFLAGS = $(PROFILE)
LIBS = -L/home/cloe/openwrt/staging_dir/target-mipsel_24kec+dsp_uClibc-0.9.33.2/usr/lib -lusb-1.0
CC = /home/cloe/openwrt/staging_dir/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/bin/mipsel-openwrt-linux-gcc

all: main

# build it
main:
        $(CC) -g main.c $(LIBS) -o vocoreUSBdriver

# clean it
clean:
        rm vocoreUSBdriver