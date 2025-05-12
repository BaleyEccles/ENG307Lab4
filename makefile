
SRC_FILES = ./src/*.c

write: obj
	sudo avrdude -p m328pb -c xplainedmini -B 10 -U flash:w:main.hex:a

compile: 
	avr-gcc -Wall -g2 -O1 -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328pb $(SRC_FILES) -o main.elf

obj: compile 
	avr-objcopy -R .eeprom -O ihex main.elf main.hex
clean:
	rm -rf *.hex
