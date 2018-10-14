OBJECTS = ddk.o
TARGET = minimal.sys
INCLUDE = /c/msys/usr/include/w32api/ddk
LIB = /c/msys/usr/lib/w32api
CFLAGS = -c -I $(INCLUDE) -DMINGW -std=c99 -Wall -m64 -shared
LDFLAGS = -L $(LIB) --subsystem native --image-base 0x10000 --file-alignment 0x1000 \
	  --section-alignment 0x1000 --entry DriverEntry@8 --stack 0x40000 \
	  --dynamicbase --nxcompat -nostartfiles -nostdlib -lntoskrnl -shared

all: $(TARGET)
clean:
	rm -f *.o $(TARGET)
minimal.sys: minimal.o
	ld $< $(LDFLAGS) -o $@
minimal.o: minimal.c
	gcc  $< $(CFLAGS) -o $@
