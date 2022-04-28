[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=7680393&assignment_repo_type=AssignmentRepo)

Part 1 (1.1) - Timer values have been updated accurately. The prescalar divides the oscillating clock by 256, so this is effectively a 32khz clock. The period for the pwm and frequency are determined by taking the period in us, and dividing it by 64 to get down to the scale of the clock.

Part 1 Notes: I cannot perceive the 60Hz refresh of the LED, but using the slow mo on my phone, the LED is flashing on and off at approximately 60Hz (the light is on half the time at 120fps). The servo motor moves and stays in place.

(1.2) Added LCD driver files.

(1.3) - Updated main with LCD initialization and added comments. Also added code to refresh OCR1A on the LCD every second, and toggle an LED every 1000ms; however, the LED appears to blink as much as 5x faster than 1000ms.

Part 2 (2.1) - Moved MusicSetNote() outside of the while function, and divide the period in half to get double the frequency. Also created a timer.h and moved main to its own file.

(2.2) - Added the SetOCR1A(int value) function. This function takes in an integer value, and checks that the value is between the upper and lower bounds for OCR1A. If it is out of bounds, OCR1A is set to the closest bound value (max or min).

(2.3) - Fixed the LCD so now it actually displays OCR1A, whereas before it would initialize and was being fed invalid data. Tidied up main.

(2.4) - Addition of the helper.h and helper.c files. These currently only have helper functions for initializing the joystick input and checking input to change OCR1A. Also added a header guard to timer.h.

Part 2 Note: After doubling the frequency, I checked the LED with my slow mo camera. At 120 fps, the flashing is not visible on the camera anymore, but at 240 fps the flashing occurs every other frame, implying a rate of 120 Hz.

Part 3 (3.1) - Included PinChangeInterrupt.c

(3.2) - Created header file for PinChangeInterrupt with the function prototypes and global variables, and removed the PlayA function from the the header and c file. Moved the F_CPU define to proj4main. SetupInterrupts was altered such that it enables interrupts for PE2/PCINT2 and PE3/PCINT3 and the ISR vector was changed to PCINT0_vect. Cleaned up includes and comments in helpers.c.

Part 3 Note: Adding support for interrupt driven inputs allowed for the inputs to feel more responsive. Using the code from part 2, the OCR1A value would only change if you held the button during the check on the input pins, which occurs approximately every 1000ms. After adding interrupt driven joystick input support, the program will still only allow you to update the OCR1A about once every 1000ms, but now an input which occurs in the duration of the 1000ms delay period will still be registered and handled by the program at the end of the delay period. This gives the system a much more responsive feel because all of your inputs are actually responded to.

Part 4 (4.1) - Included ADC.c discussion code and created a header file with the appropriate function prototypes. 

(4.2) - Modified the discussion code for our purposes: Checked that ADCSetup uses ADC2 channel, filled out ADCGet function. Added ADCSetup call in main. Called the write to LCD function using the value in each digit position of the ADC value and displayed them on displays 0-3.

Part 4 Note: The ADC result is 10 bits, meaning that the adc has 2^10 possible values or 1024 values. Four display positions allows for representation of all possible values from 0000-1024.

Part 5 (5.1) - Included UART.c and UART.h.

