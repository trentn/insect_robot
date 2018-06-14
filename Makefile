###### Project Specific Details ######
######################################

MCU = atmega328
F_CPU = 1000000UL
BAUD = 9600UL


LIBDIR = /home/trent/avr_projects/lib

##### Programmer Defaults #####
###############################

PROGRAMMER_TYPE = usbasp
PROGRAMMER_ARGS =

##### Program Locations #####
#############################

CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRDUDE = avrdude


##### Makefile Magic #####
##########################

TARGET = program

SOURCES=$(wildcard *.c $(LIBDIR)/*.c)
OBJECTS=$(SOURCES:.c=.o)
HEADERS=$(SOURCES:.c=.o)


##Compilation Options
CPPFLAGS = -DF_CPU=$(F_CPU) -DBAUD=$(BAUD) -I. -I$(LIBDIR)

CFLAGS = -Os -g -std=gnu99 -Wall

# Use short (8-bit) data types
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums

# Splits up object files per function
CFLAGS += -ffunction-sections -fdata-sections

LDFLAGS = -Wl,-Map,$(TARGET).map

TARGET_ARCH = -mmcu=$(MCU)


%.o: %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c -o $@ $<;

$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $(TARGET_ARCH) $^ $(LDLIBS) -o $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@


# These targets from have files named after them
.PHONY: all disassemble disasm clean flash


all: $(TARGET).lst

debug:
	@echo
	@echo "Source files:"   $(SOURCES)
	@echo "MCU, F_CPU, BAUD:"  $(MCU), $(F_CPU), $(BAUD)
	@echo 

disasm: disassemble

size: $(TARGET).elf
	#(AVRSIZE) -C --mcu=$(MCU) $(TARGET).elf

clean:
	rm -f $(TARGET).elf $(TARGET).hex $(TARGET).obj \
	$(TARGET).o $(TARGET).d $(TARGET).eep $(TARGET).lst \
	$(TARGET).lss $(TARGET).sym $(TARGET).map $(TARGET)~ \
	$(TARGET).eeprom

flash: $(TARGET).hex
	$(AVRDUDE) -c $(AVRDUDE) -c$(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -U flash:w:$<

program: flash
