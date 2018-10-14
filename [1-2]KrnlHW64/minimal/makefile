TARGET = minimal.sys
INCLUDE = /c/msys/usr/include/w32api/ddk
LIB = /c/msys/usr/lib/w32api
CFLAGS = -I $(INCLUDE) -DMINGW -std=c99 -m64
LDFLAGS = -shared -lntoskrnl -Wl,--subsystem,native -Wl,--image-base,0x10000 -Wl,--file-alignment,0x1000 \
	  -Wl,--section-alignment,0x1000 -Wl,--entry,DriverEntry@8 -Wl,--stack,0x40000 \
	  -Wl,--dynamicbase -Wl,--nxcompat -nostartfiles -nostdlib

all: $(TARGET)
clean:
	rm -f *.o $(TARGET)
minimal.sys: minimal.c
	gcc  $< $(CFLAGS) $(LDFLAGS) -o $@
