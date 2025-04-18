///////////////////////////////////////////////////////////////////////////////
// File: timer.c
// Provided by: Robucci
// Modified by: Max G
// Desc: Uses timer to play notes
///////////////////////////////////////////////////////////////////////////////

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "U0_LCD_Driver.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "timer.h"

#define MIN_PULSE_WIDTH 10
#define MAX_PULSE_WIDTH 38

// ******************************************************************************
//  MUSIC FUNCTIONS USING TIMER 1
// ******************************************************************************

void MusicSetupPort(){
	#define PORTB5_MASK  0b00100000
	DDRB |= PORTB5_MASK; //enable PORTB5 as output
}

void MusicSetNote(int freq_period_us, int pwm_period_us){
	ICR1=(freq_period_us)/(64); //convert to half per. and something usable for 32khz
	OCR1A=(pwm_period_us)/(64); //convert to half pwm per. & usable for 32khz
}

void MusicRest(){
	OCR1A=0;
};

void MusicPlayG(){
	MusicSetNote(2552,2552);
	MusicRest();
}

void MusicPlayA(){
	MusicSetNote(2272,2272);
	MusicRest();
}

void MusicPlayB(){
	MusicSetNote(2024,2024);
	MusicRest();
}

void MusicSetupTimer1() {
	/* Timer/Counter1 Control Register A */
	int value_TCCR1A_COM1A_2b = 2; //clear on match up, set on match down
	int value_TCCR1A_COM1B_2b = 0; //disable
	//this one is spread over both regsters
	int value_TCCR1AB_WGM1_4b = 8; //PWM+frequency control using register ICR1
	/* Timer/Counter1 Control Register B */
	int value_TCCR1B_ICNC1_1b = 0; //no input capture noise cancel
	int value_TCCR1B_ICES1_1b = 0; //Dont Care since not used
	int value_TCCR1B_CS1_3b = 4; //use clock prescaler 256...see page 131 of datasheet...31.25khz for 8Mhz clk
	TCCR1A = (value_TCCR1A_COM1A_2b << COM1A0) + (value_TCCR1A_COM1B_2b << COM1B0) + ((value_TCCR1AB_WGM1_4b&0x3) << WGM10);
	TCCR1B = (value_TCCR1B_ICNC1_1b << ICNC1) + (value_TCCR1B_ICES1_1b << ICES1) + (((value_TCCR1AB_WGM1_4b&0b00001100)>>2) << WGM12) + (value_TCCR1B_CS1_3b<<CS10);
	
	/* Timer/Counter1 Input Capture Register */
	//also used for frequency setting
	ICR1 = 0xFF/2; //16 bits //just some initial value
	
	
	
	/* Timer/Counter 1 Interrupt Mask Register */
	int value_TIMSK1_ICIE1_1b = 0;//input capture int. enable
	int value_TIMSK1_OCIE1B_1b = 0;//output compare int. enable
	int value_TIMSK1_OCIE1A_1b = 0;//output compare int. enable
	int value_TIMSK1_TOIE1_1b = 0;//overflow int. enable
	TIMSK1 = (value_TIMSK1_ICIE1_1b <<ICIE1) + (value_TIMSK1_OCIE1B_1b<<OCIE1B) + (value_TIMSK1_OCIE1A_1b<<OCIE1A) + (value_TIMSK1_TOIE1_1b<<TOIE1);
}

// This function takes in an integer value, and checks that
// the value is between the upper and lower bounds for OCR1A.
// If it is out of bounds, OCR1A is set to the closest bound value 
// (max or min).
void SetOCR1A(int value) {
	// Check lower bound, if value is below 10, default to 10
	if (value < MIN_PULSE_WIDTH) {
		OCR1A = MIN_PULSE_WIDTH;
		return;
	} else if (value > MAX_PULSE_WIDTH) { // do the same for the upper bound
		OCR1A = MAX_PULSE_WIDTH;
		return;
	}
	//The value is within the bounds
	OCR1A = value;
}