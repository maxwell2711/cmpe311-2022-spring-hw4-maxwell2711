///////////////////////////////////////////////////////////////////////////////
// File: timer.c
// Name: Robucci
// 
// Desc: Uses timer to play notes
///////////////////////////////////////////////////////////////////////////////

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "util/delay.h"
#include "avr/interrupt.h"

#define MIN_PULSE_WIDTH 10

void main(){
   MusicSetupPort();
   MusicSetupTimer1();
   MusicSetNote(2552);
   _delay_ms(1000);
   MusicRest();

   

	};

// ******************************************************************************
//  MUSIC FUNCTIONS USING TIMER 1
// ******************************************************************************

void MusicSetupPort(){
	#define PORTB5_MASK  0b00100000
	DDRB |= PORTB5_MASK; //enable PORTB5 as output
}

void MusicSetNote(int period_us){
	ICR1=period_us/2;
	OCR1A=period_us/4;
	TCNT1=0;
}

void MusicRest(){
	OCR1A=0;
};

void MusicPlayG(){
	MusicSetNote(2552);
	MusicRest();
}

void MusicPlayA(){
	MusicSetNote(2272);
	MusicRest();
}

void MusicPlayB(){
	MusicSetNote(2024);
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
	int value_TCCR1B_CS1_3b = 2; //use clock prescaler 8...see page 131 of datasheet...1Mhz for 8Mhz clk
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