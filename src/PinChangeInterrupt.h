#ifndef PINCHANGEINTERRUPT_H
#define PINCHANGEINTERRUPT_H

//////////////
//globals   //
//////////////
char g_servoLeft;
char g_servoRight;

//////////////
//prototypes//
//////////////
void SetupInterrupts(void);
void BootLoaderFixes(void);

#endif