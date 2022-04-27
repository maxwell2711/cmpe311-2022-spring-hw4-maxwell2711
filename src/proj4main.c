#include "U0_LCD_Driver.h"
#include "timer.h"
#include "util/delay.h"
#include "helpers.h"
#include "PinChangeInterrupt.h"
#include <xc.h>
#include <avr/interrupt.h>

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

void main(){
    MusicSetupPort();   //Setup the timer ports
    MusicSetupTimer1(); //Setup the timer
	LCD_Init();         //Initalize the LCD
    JoystickInit();     //Initialize the joystick inputs
    SetupInterrupts();	//setup the interrupts
	sei();				//enable global interrupts

	MusicSetNote(16667/2,1500); //set note
    while(1) {
        //refresh the LCD
		LCD_WriteDigit((OCR1A/10)+'0',4);
		LCD_WriteDigit((OCR1A%10)+'0',5);

        CheckInput(); //check for an input and adjust OCR1A
        
        PORTB ^= (1 << PB0); //toggle LED
        _delay_ms(1000);
    }
};