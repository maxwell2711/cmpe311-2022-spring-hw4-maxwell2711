[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=7680393&assignment_repo_type=AssignmentRepo)

Part 1: Timer values have been updated accurately. The prescalar divides the oscillating clock by 256, so this is effectively a 32khz clock. The period for the pwm and frequency are determined by taking the period in us, and dividing it by 64 to get down to the scale of the clock.
I cannot perceive the 60Hz refresh of the LED, but using the slow mo on my phone, the LED is flashing on and off at approximately 60Hz (the light is on half the time at 120fps). The servo motor moves and stays in place.

Added LCD driver files.

Updated main with LCD initialization and added comments. Also added code to refresh OCR1A on the LCD every second, and toggle an LED every second.

Part 2: Update 2.1 - Moved MusicSetNote() outside of the while function, and divide the period in half to get double the frequency. Also created a timer.h and moved main to its own file.

2.2 - Added the SetOCR1A(int value) function. This function takes in an integer value, and checks that the value is between the upper and lower bounds for OCR1A. If it is out of bounds, OCR1A is set to the closest bound value (max or min).

2.3 - Fixed the LCD so now it actually displays OCR1A, whereas before it would initialize and was being fed invalid data. Tidied up main.

2.4 - Addition of the helper.h and helper.c files. These currently only have helper functions for initializing the joystick input and checking input to change OCR1A. Also added a header guard to timer.h.

Part 2 Note: After doubling the frequency, I checked the LED with my slow mo camera. At 120 fps, the flashing is not visible on the camera anymore, but at 240 fps the flashing occurs every other frame, implying a rate of 120 Hz.

Part 3: Included PinChangeInterrupt.c