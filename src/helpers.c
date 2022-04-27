/*
 * File:   helpers.c
 * Author: maxwe
 *
 * Created on April 25, 2022, 9:23 PM
 */


#include <xc.h>
#include "helpers.h"
#include "timer.h"
#include "U0_LCD_Driver.h"
#include "PinChangeInterrupt.c"

// PART 2 CHECKINPUT
//void CheckInput() {
//    //Check input on the left
//    if(!(PINE&(1<<PE2))) {
//        SetOCR1A(OCR1A-1); //reduce pulse width by 1
//    }
//    if (!(PINE&(1<<PE3))) { //check right input
//        SetOCR1A(OCR1A+1); //increase pulse width by 1
//    }
//}

void CheckInput() {
    //check global vars
    if (g_servoLeft) {
        SetOCR1A(OCR1A-1); //reduce pulse width by 1
        g_servoLeft = 0;
    }
    if (g_servoRight) {
        SetOCR1A(OCR1A+1);
        g_servoRight = 0;
    }
}

void JoystickInit() {
    //initialize left joystick on PE2
    DDRE &= !(1<<PE2); //indicate input on the left joystick
    PORTE |= (1<<PE2); //enable pull-up

    //initialize right joystick on PE3
    DDRE &= !(1<<PE3); //indicate input on the right joystick
    PORTE |= (1<<PE3); //enable pull-up
}
