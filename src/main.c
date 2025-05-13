#define F_CPU 16000000UL

#define BAUD 9600
#define MY_UBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>
#include "usart.h"


void ADC_init(uint8_t channel) {
    ADMUX = (1 << REFS0); // AVcc with external capacitor at AREF pin
    ADMUX |= (channel & 0b00000111);

    // Enable the ADC and set the prescaler to 64 (for 16 MHz clock)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

uint16_t ADC_read(uint8_t channel) {
  ADMUX = (ADMUX & 0b11111000) // Keep first 5 bits
    | (channel & 0b00000111); // Set the channel to read from
  
  ADCSRA |= (1 << ADSC); // Start conversion

  while (ADCSRA & (1 << ADSC)); // Wait untill conversion is done

  return ADC;
}


int main(void) {
  // Number from 0 -> 15
  // 0 -> 7 map to PC0 -> PC7
  // See data sheet for 8 -> 15
  uint8_t channel = 0;
  ADC_init(channel);
  USART_Init(MY_UBRR);
  DDRB |= (1 << PB5); // set PB5 as output pin

  while (1) {
    uint16_t adc_value = ADC_read(channel); // Read ADC value

    char str[20];
    double voltage = 1000.f*(((float)adc_value / 1023.0f) * 5.0f);

    sprintf(str, "ADC val = %d mV\n", (uint16_t)voltage);
    USART_Transmit_String(str);    


    _delay_ms(100);
    PORTB ^= (1 << PB5); // set PB5 high

  }
}

