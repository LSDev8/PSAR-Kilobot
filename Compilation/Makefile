EXEC= phototaxis

all: bootldr ohc ohc-big ohc-arduino-8mhz ohc-arduino-16mhz blank $(EXEC)

.PHONY: docs bootldr blank ohc ohc-big ohc-arduino-8mhz ohc-arduino-16mhz phototaxis
KILOLIB = build/kilolib.a
bootldr: build/bootldr.elf build/bootldr.hex build/bootldr.lss
blank: build/blank.elf build/blank.hex build/blank.lss
$(EXEC) : build/$(EXEC).elf build/$(EXEC).hex #build/$(EXEC).lss
ohc: build/ohc.elf build/ohc.hex build/ohc.lss
ohc-big: build/ohc-big.elf build/ohc-big.hex build/ohc-big.lss
ohc-arduino-8mhz: build/ohc-arduino-8mhz.elf build/ohc-arduino-8mhz.hex build/ohc-arduino-8mhz.lss
ohc-arduino-16mhz: build/ohc-arduino-16mhz.elf build/ohc-arduino-16mhz.hex build/ohc-arduino-16mhz.lss

CC = avr-gcc
AVRAR = avr-ar
AVROC = avr-objcopy
AVROD = avr-objdump
AVRUP = avrdude

PFLAGS = -P usb -c avrispmkII # user to reprogram OHC
CFLAGS = -mmcu=atmega328p -Wall -gdwarf-2 -O3 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -DF_CPU=8000000
ASFLAGS = $(CFLAGS)
BOOTLDR_FLAGS = -Wl,-section-start=.text=0x7000 -DBOOTLOADER
OHC_FLAGS = -Wl,-section-start=.text=0x7000 -DOHC
OHC_ARDUINO_FLAGS = -DOHC -DARDUINO
OHC_BIG_FLAGS = $(OHC_FLAGS) -DBIGOHC
COMPILFLAGS=-U "flash:w:build/bootldr.hex"


FLASH = -R .eeprom -R .fuse -R .lock -R .signature
EEPROM = -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0  

%.lss: %.elf
	@echo ""
	@echo "###########"
	@echo "LSS : $@"
	@echo "###########"
	$(AVROD) -d -S $< > $@

%.hex: %.elf
	@echo ""
	@echo "###########"
	@echo "HEX : $@"
	@echo "###########"
	$(AVROC) -O ihex $(FLASH) $< $@

%.eep: %.elf
	@echo ""
	@echo "###########"
	@echo "EEP : $@"
	@echo "###########"
	$(AVROC) -O ihex $(EEPROM) $< $@

%.bin: %.elf
	@echo ""
	@echo "###########"
	@echo "BIN : $@"
	@echo "###########"
	$(AVROC) -O binary $(FLASH) $< $@ 

build:
	mkdir -p $@

message_send.o: message_send.S
	$(CC) $(CFLAGS) -c -o $@ $<

$(KILOLIB): kilolib.o message_crc.o message_send.o | build
	$(AVRAR) rcs $@ kilolib.o message_crc.o message_send.o 
	rm -f *.o

build/$(EXEC).elf: $(EXEC).c $(KILOLIB) | build
	$(CC) $(CFLAGS) -o $@ $< $(KILOLIB) 

build/blank.elf: blank.c $(KILOLIB) | build
	$(CC) $(CFLAGS) -o $@ $< $(KILOLIB) 

build/ohc.elf: ohc.c message_crc.c message_send.S | build
	$(CC) $(CFLAGS) $(OHC_FLAGS) -o $@ ohc.c message_crc.c message_send.S

build/ohc-big.elf: ohc.c message_crc.c message_send.S | build
	$(CC) $(CFLAGS) $(OHC_BIG_FLAGS) -o $@ ohc.c message_crc.c message_send.S

build/ohc-arduino-8mhz.elf: ohc.c message_crc.c message_send.S | build
	$(CC) $(CFLAGS) $(OHC_ARDUINO_FLAGS) -o $@ ohc.c message_crc.c message_send.S

build/ohc-arduino-16mhz.elf: ohc.c message_crc.c message_send.S | build
	$(CC) $(CFLAGS) $(OHC_ARDUINO_FLAGS) -DARDUINO_16MHZ -o $@ ohc.c message_crc.c message_send.S

build/bootldr.elf: bootldr.c kilolib.c message_crc.c | build
	$(CC) $(CFLAGS) $(BOOTLDR_FLAGS) -o $@ bootldr.c kilolib.c message_crc.c

program-ohc: build/ohc.hex
	$(AVRUP) -p m328  $(PFLAGS) -U "flash:w:$<:i"

program-ohc-big: build/ohc-big.hex
	$(AVRUP) -p m328  $(PFLAGS) -U "flash:w:$<:i"

program-ohc-arduino-8mhz: build/ohc-arduino-8mhz.hex
	$(AVRUP) -p m328p $(PFLAGS) -U "flash:w:$<:i"

program-ohc-arduino-16mhz: build/ohc-arduino-16mhz.hex
	$(AVRUP) -p m328p $(PFLAGS) -U "flash:w:$<:i"

program-boot: build/bootldr.hex
	$(AVRUP) -p m328p $(PFLAGS) -U "flash:w:$<:i"

program-blank: build/blank.hex build/bootldr.hex
	$(AVRUP) -p m328p $(PFLAGS) -U "flash:w:build/blank.hex:i" -U "flash:w:build/bootldr.hex"

program-phototaxis: build/phototaxis.hex build/bootldr.hex
	echo "PHOTOTAXIS"
	$(AVRUP) -p m328p $(PFLAGS) -U "flash:w:"$<":i" $(COMPILFLAGS)

docs:
	cat message.h kilolib.h message_crc.h | grep -v "^\#" > docs/kilolib.h
	(cd docs; doxygen)

clean:
	rm -fR build *~

remove:
	@rm -f build/$(EXEC).elf
