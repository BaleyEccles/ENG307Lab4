#include <avr/io.h>


int main() {
  DDRB |= (1 << PB5); // set PB5 as output pin
  while (1) {
    PORTB |= (1 << PB5); // set PB5 high
  }
 return 0;
}
