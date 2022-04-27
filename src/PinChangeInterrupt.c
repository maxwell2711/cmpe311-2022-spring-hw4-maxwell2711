//include for MPLAB (when using MPLAB, might not need some includes that follow)
#include <xc.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "PinChangeInterrupt.h"
#include "U0_LCD_Driver.h"



////////////////////////
//Function Definitions//
////////////////////////


void SetupInterrupts(void)
{
	//Setup for Center Button Interrupt
    //Unmask bit for Left Button on Butterfly, 
    //PE2->PCINT2 to allow it to trigger interrupt flag PCIF0
	PCMSK0  |= (1<<PCINT2) | (1<<PCINT3); 
    

    EIMSK   = (1<<PCIE0);    //Enable interrupt for flag PCIF0
}


//This performs adjustments needed to undo actions of Butterfly boot loader
void BootLoaderFixes(void)
{
	//Boot loader Disables E2 and E3 digital input drivers, which are used for left and right
	//The following code re-enables them by clearing the appropriate disable bits
	DIDR1 &= ~((1<<AIN0D)|(1<<AIN1D));
}


////////////////////
// ISR DEFINITIONS//
////////////////////


ISR(PCINT0_vect) 		//remember this is called on pin change 0->1 and 1->0
{
	static uint8_t pinEPrev=1; //for storing previous value of port to detect 

	//change global vars based on L/R button status being newly pressed, but not when it is released
	if(((PINE & (1<<PE2))  == 0) &&
	((pinEPrev & (1<<PE2))  != 0))
	{
		//if button pressed (bit is zero) and previous it wasn't
		g_servoLeft = 1; //set global variable
	}
	else if (((PINE & (1<<PE3)) == 0) &&
          ((pinEPrev & (1<<PE3)) != 0))
	{
        //if button pressed (bit is zero) and previous it wasn't
		g_servoRight = 1; //set global variable
	}

	pinEPrev = PINE; //save button status
}