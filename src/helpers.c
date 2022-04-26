#include "helpers.h"
#include "timer.h"
#include "U0_LCD_Driver.h"

void CheckInput() {
    //Check input on the left
    if(PINE&&(1<<PE2)) {
        SetOCR1A(OCR1A-1); //reduce pulse width by 1
    } else if (PINE&&(1<<PE3)) { //check right input
        SetOCR1A(ORC1A+1); //increase pulse width by 1
    }
}

void JoystickInit() {
    //initialize left joystick on PE2
    DDRE &= !(1<<PE2); //indicate input on the left joystick
    PORTE |= (1<<PE2); //enable pull-up

    //initialize left joystick on PE3
    DDRE &= !(1<<PE3); //indicate input on the left joystick
    PORTE |= (1<<PE3); //enable pull-up
}