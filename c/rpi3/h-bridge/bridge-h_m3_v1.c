#include <wiringPi.h>
#include <softPwm.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main (void)
{
  int ch ;

  if (wiringPiSetup () == -1)
    exit (1) ;

  //pinMode (1, PWM_OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (5, OUTPUT);

  //pinMode (23, PWM_OUTPUT);
  pinMode (0, OUTPUT);
  pinMode (2, OUTPUT);

  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);

  digitalWrite(0, HIGH);
  digitalWrite(2, LOW);

  if(softPwmCreate(23, 0, 100)) {
    printf("error l");
  }

  if(softPwmCreate(26, 0, 100)) {
    printf("error r");
  }

  while(1) {
    softPwmWrite (23, 10);
    softPwmWrite (26, 10);
  }

  return 0 ;
}
