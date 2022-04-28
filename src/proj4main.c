//comment out the following line if not using the bootloader
//#define USING_BOOTLOADER

//set F_CPU if not set already, dependent on use of boot loader
#ifndef F_CPU

#ifdef USING_BOOTLOADER
#define F_CPU 2000000UL
#else
#define F_CPU 8000000UL
#endif

#endif

#include "U0_LCD_Driver.h"
#include "timer.h"
#include "util/delay.h"
#include "helpers.h"
#include "ADC.h"
#include "PinChangeInterrupt.h"
#include "UART.h"
#include <xc.h>
#include <avr/interrupt.h>

void main(){
    MusicSetupPort();   //Setup the timer ports
    MusicSetupTimer1(); //Setup the timer
	LCD_Init();         //Initalize the LCD
    JoystickInit();     //Initialize the joystick inputs
    SetupInterrupts();	//setup the interrupts
	sei();				//enable global interrupts
    ADCSetup();         //setup ADC
    stderr = stdout = stdin  = &uart_stream; //redirect standard i/o
    UARTInit();         //initialize UART


    DDRB |= (1<<PB0);

	MusicSetNote(16667/2,1500); //set note
    while(1) {
        _delay_ms(500); //delay half second
        int adcValue = ADCAquire(); //Get an ADC reading
        LCD_WriteDigit((adcValue%10)+'0',3); //Display ones place
        LCD_WriteDigit((adcValue%100/10)+'0',2); //display tens place
        LCD_WriteDigit((adcValue%1000/100)+'0',1); //display hundreds place
        LCD_WriteDigit((adcValue/1000)+'0',0); //display thousands place

        int adc1  = adcValue; //save for compare

        //refresh the LCD
		LCD_WriteDigit((OCR1A/10)+'0',4);
		LCD_WriteDigit((OCR1A%10)+'0',5);

        CheckInput(); //check for an input and adjust OCR1A
        
        PORTB ^= (1 << PB0); //toggle LED
        
        _delay_ms(500); //delay for a second

        adcValue = ADCAquire(); //Get an ADC reading
        LCD_WriteDigit((adcValue%10)+'0',3); //Display ones place
        LCD_WriteDigit((adcValue%100/10)+'0',2); //display tens place
        LCD_WriteDigit((adcValue%1000/100)+'0',1); //display hundreds place
        LCD_WriteDigit((adcValue/1000)+'0',0); //display thousands place

        int16_t lightDiff = adcValue - adc1;

        SendData(lightDiff, OCR1A);

    }
};