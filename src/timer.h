#ifndef TIMER_H
#define TIMER_H
void MusicSetupPort();
void MusicSetNote(int freq_period_us, int pwm_period_us);
void MusicRest();
void MusicPlayG();
void MusicPlayA();
void MusicPlayB();
void MusicSetupTimer1();
void SetOCR1A(int value);
#endif
