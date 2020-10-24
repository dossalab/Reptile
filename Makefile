#
# Part of the Reptile - simple 3d printer firmware
#
# See LICENSE.md for licensing information
# Roman Luitko, 2020
#

include scripts/build.mk

$(call check-defined, BOARD, See 'board' directory for available boards)

ECHO	:= printf "[%s]\t%s\n"

elf	:= reptile.elf

objects	:= \
	core/main.o \
	libs/crc7.o \
	libs/fatfs/pff.o \
	libs/fatfs/diskio.o \
	misc/delay.o \
	mcu/common.o

# FIXME: is -Wno-discarded-qualifiers really a good idea?
CFLAGS	:= \
	-std=gnu99 \
	-Wall \
	-Wshadow \
	-Wno-main \
	-Wno-discarded-qualifiers \
	-I. -g3 -Og \
	-fdata-sections -ffunction-sections

LDFLAGS	:= -lm -Wl,--gc-sections

include board/$(BOARD)/board.mk
$(call check-defined, MCU, Probably you have selected unsupported board!)

include mcu/$(MCU)/mcu.mk
$(call check-defined, ARCH)

include arch/$(ARCH)/arch.mk

# MCU_SPECIFIC_HEADER contains mcu-specific stuff
# Usually inits are hardware-specific, peripheral api is common
CFLAGS	+= -DMCU_SPECIFIC_HEADER="<mcu/$(MCU)/mcu.h>"

# Board-specific header will contain definitions that rest of the program
# can use (where is leds, where are buttons, etc...)
CFLAGS	+= -DBOARD_SPECIFIC_HEADER="<board/$(BOARD)/board.h>"

# ARCH-specific header will contain at least way to disable/enable interrupts
# to implement some sort of locking
CFLAGS	+= -DARCH_SPECIFIC_HEADER="<arch/$(ARCH)/arch.h>"

# Export ARCH, MCU, BOARD to C preprocessor just in case...
CFLAGS	+= -DARCH_$(ARCH) -DMCU_$(MCU) -DBOARD_$(BOARD)

all: $(elf) size $(lib)

# Firmware target (cross-compilation)
%.o : %.c
	@ $(ECHO) CC "$@"
	@ $(CC) $(CFLAGS) -c $< -o $@

$(elf) : $(objects)
	@ $(ECHO) LD "$@"
	@ $(LD) $^ $(LDFLAGS) -o $@

size:
	@ $(SIZE) $(elf)

flash: $(elf)
	$(call check-defined, FLASH_CHIP)
	$(call check-defined, FLASH_ADAPTER)

	@ $(ECHO) FLASH "$^"
	@ scripts/flash.sh $(FLASH_CHIP) $(FLASH_ADAPTER) $<

debug: $(elf)
	$(call check-defined, GDB, only gdb + openocd is supported)
	$(call check-defined, DEBUG_CHIP, is debug supported on your chip?)
	$(call check-defined, DEBUG_ADAPTER)

	@ $(ECHO) DEBUG "$^"
	@ scripts/debug.sh $(GDB) $(DEBUG_CHIP) $(DEBUG_ADAPTER) $<

clean:
	@ $(ECHO) RM "$(objects) $(elf)"
	@ $(RM) $(objects) $(elf)

distclean: clean
	@ $(ECHO) CLEAN *.o
	@ find . -type f -name '*.o' -exec rm {} \;

.PHONY: all size flash debug clean distclean

