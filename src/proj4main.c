#include "U0_LCD_Driver.h"
#include "timer.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "helpers.h"
#include <xc.h>

void main(){
    MusicSetupPort();
    MusicSetupTimer1();
	LCD_Init();
    JoystickInit();

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