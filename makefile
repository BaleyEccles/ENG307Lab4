
write: compile
	sudo avrdude -p m328pb -c xplainedmini -U flash:w:out.hex

compile: 
	avr-gcc -mmcu=atmega328pb main.c -o out.hex

clean:
	rm -rf *.hex
