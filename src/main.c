#define F_CPU 16000000UL  // Define CPU frequency
#define BAUD 9600         // Define baud rate
#define MY_UBRR F_CPU/16/BAUD-1  // Calculate UBRR value

#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"

int main(void) {
  // Initialize USART with calculated UBRR value
  USART_Init(MY_UBRR);
  DDRB |= (1 << PB5); // set PB5 as output pin
  while (1) {
    USART_Transmit_String("Hello, USART!\n");
    _delay_ms(1000);
    PORTB ^= (1 << PB5); // set PB5 high
  }
}

