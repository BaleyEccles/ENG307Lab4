#define F_CPU 16000000UL

#define BAUD 9600
#define MY_UBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>
#include "usart.h"

#define ADC_CHANNEL 0
void ADC_init() {
    ADMUX = (1 << REFS0); // AVcc with external capacitor at AREF pin
    ADMUX |= (ADC_CHANNEL & 0b00000111);

    // Enable the ADC and set the prescaler to 64 (for 16 MHz clock)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

uint16_t ADC_read(uint8_t channel) {
  ADMUX = (ADMUX & 0xF8) | (channel & 0b00000111);

  ADCSRA |= (1 << ADSC);

  while (ADCSRA & (1 << ADSC));

  return ADC;
}

//void adcStartMeasurement() {
//  ADCSRA |= (1 << ADSC);
//}
//
//int ADC_get() {
//  adcStartMeasurement();
//  
//  while (!(ADCSRA & (1 << ADIF))); // Wait for conversion to complete
//  
//  uint16_t low = ADCL; // Read low byte
//  uint16_t high = ADCH; // Read high byte
//  int Vcc_value = (1.1 * 1024 * 1000) / (low + (high << 8)); // Calculate Vcc in mV
//  
//  ADCSRA |= (1 << ADIF); // Clear the ADIF flag
//  return Vcc_value;
  //}



int main(void) {
  ADC_init();
  USART_Init(MY_UBRR);
  DDRB |= (1 << PB5); // set PB5 as output pin
  while (1) {
    uint16_t adc_value = ADC_read(ADC_CHANNEL); // Read ADC value

    char str[20];
    double voltage = 1000.f*(((float)adc_value / 1023.0f) * 5.0f);

    sprintf(str, "ADC val = %d mV\n", (uint16_t)voltage);
    USART_Transmit_String(str);    


    _delay_ms(1000);
    PORTB ^= (1 << PB5); // set PB5 high

  }
}

