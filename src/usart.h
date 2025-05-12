#include <avr/io.h>

void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
void USART_Transmit_String(const char* str);
