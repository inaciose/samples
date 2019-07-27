#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main (void)
{
  int ch ;

  if (wiringPiSetup () == -1)
    exit (1) ;

  pinMode (23, PWM_OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (5, OUTPUT);

  pinMode (26, PWM_OUTPUT);
  pinMode (0, OUTPUT);
  pinMode (2, OUTPUT);

  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);

  digitalWrite(0, HIGH);
  digitalWrite(2, LOW);

  for (;;) {
    for (ch = 0 ; ch < 1024 ; ++ch) {
      //printf("%d\n", ch);
      pwmWrite (23, ch);
      pwmWrite (26, ch);
      delay (1);
    }

    for (ch = 1023 ; ch >= 0 ; --ch) {
      //printf("%d\n", ch);
      pwmWrite (23, ch);
      pwmWrite (26, ch);
      delay (1);
    }
  }

  return 0 ;
}
