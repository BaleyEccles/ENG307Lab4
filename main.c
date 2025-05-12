
#define F_CPU 16000000UL  // Define CPU frequency
#define BAUD 9600         // Define baud rate
#define MY_UBRR F_CPU/16/BAUD-1  // Calculate UBRR value

#include <avr/io.h>
#include <util/delay.h>

void USART_Init(unsigned int ubrr) {
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8); // Set high byte
    UBRR0L = (unsigned char)ubrr;        // Set low byte

    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    
    // Set frame format: 8data, 2stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) | (1 << USBS0);
}

void USART_Transmit(unsigned char data) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));
    
    // Put data into buffer, sends the data
    UDR0 = data;
}

void USART_Transmit_String(const char* str) {
    while (*str) {
        USART_Transmit(*str++);
    }
}

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

