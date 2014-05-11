TARGET = ctrhw

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OC = arm-none-eabi-objcopy

CFLAGS = -g -march=armv6 -mlittle-endian -O2
LDFLAGS = -nostdlib -T ctr.ld

OBJS = main.o fnt.o

all: Launcher.dat

Launcher.dat: kfs.bin
	python ./tools/append.py S0.DAT $< $@

kfs.bin: $(TARGET).bin
	python ./tools/kfs.py $< 0x21000000

$(TARGET).bin: $(TARGET).elf
	$(OC) -O binary $< -S $@

$(TARGET).elf: $(OBJS)
	$(LD) $(LDFLAGS) $^ ./libgcc.a -o $@

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).bin kfs.bin Launcher.dat
