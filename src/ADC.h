#include <avr/io.h>
#ifndef ADC_H
#define ADC_H
void ADCSetup();
void ADCStartConversion();
int ADCIsConversionCompleteFlagSet();
uint16_t ADCGet();
int ADCAquire();
#endif
