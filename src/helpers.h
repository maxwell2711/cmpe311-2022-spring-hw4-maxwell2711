#ifndef HELPERS_H
#define HELPERS_H
#include "PinChangeInterrupt.h"
#include "timer.h"
#include "UART.h"

void CheckInput();
void JoystickInit();
void SendData(int16_t lightDiff, uint16_t ocrVal);


#endif
