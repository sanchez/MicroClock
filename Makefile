SOURCES=io.c util.c print.c serial.c spi.c dmd.c
MEGASOURCES=main.c
TESTSOURCES=tester.c test.c testIO.c
CFLAGS=-Wall -std=gnu99 -pedantic -g

all: tester program

print:
	@printf "Printing files\n"
	@printf "Sources: $(SOURCES)\n"
	@printf "MegaSources: $(MEGASOURCES)\n"
	@printf "TestSources: $(TESTSOURCES)\n"

tester:
	@printf "Tests\n"
	gcc $(CFLAGS) $(SOURCES) $(TESTSOURCES) -o test
	./test

hex:
	avr-gcc -g -std=gnu99 -mmcu=atmega328p $(SOURCES) $(MEGASOURCES) -o project.elf
	avr-objcopy -j .text -j .data -O ihex project.elf project.hex

flash:
	#avrdude -F -p m2560 -c avrispmkII -U flash:w:project.hex
	avrdude -p m328p -c arduino -P /dev/ttyACM0 -U flash:w:project.hex

program: hex flash clean

clean:
	rm project.elf
	rm project.hex

serial:
	sudo screen /dev/ttyACM0 19200