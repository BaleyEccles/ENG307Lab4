#include "usart.h"

void USART_Init(unsigned int ubrr) {
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;

  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) | (1 << USBS0);
}

void USART_Transmit(unsigned char data) {
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}

void USART_Transmit_String(const char* str) {
  while (*str) {
    USART_Transmit(*str++);
  }
}
