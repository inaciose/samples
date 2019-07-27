# define GPIO pin signals to use
pinin1=23
pinin2=24
pinen1=13

pinin3=17
pinin4=27
pinen2=12

# define other vars
sleeptime=1

# import required libraries
import sys
import time
import RPi.GPIO as GPIO

# setup GPIO pin address mode
GPIO.setmode(GPIO.BCM)
#GPIO.setmode(GPIO.BOARD)
mode=GPIO.getmode()
print " mode: "+str(mode)
GPIO.cleanup()

# set GPIO pins mode (int,out)
GPIO.setup(pinin1, GPIO.OUT)
GPIO.setup(pinin2, GPIO.OUT)
GPIO.setup(pinen1, GPIO.OUT)
GPIO.setup(pinin3, GPIO.OUT)
GPIO.setup(pinin4, GPIO.OUT)
GPIO.setup(pinen2, GPIO.OUT)

# set GPIO pins initial value
GPIO.output(pinin1, GPIO.LOW)
GPIO.output(pinin2, GPIO.LOW)
GPIO.output(pinin3, GPIO.LOW)
GPIO.output(pinin4, GPIO.LOW)

pwm1 = GPIO.PWM(pinen1, 60)
pwm1.start(0)

pwm2 = GPIO.PWM(pinen2, 60)
pwm2.start(0)

def forward(x):
    GPIO.output(pinin1, GPIO.HIGH)
    GPIO.output(pinin3, GPIO.HIGH)
    print "forwarding running motors "
    time.sleep(x)
    GPIO.output(pinin1, GPIO.LOW)
    GPIO.output(pinin3, GPIO.LOW)

def reverse(x):
    GPIO.output(pinin2, GPIO.HIGH)
    GPIO.output(pinin4, GPIO.HIGH)
    print "backwarding running motor"
    time.sleep(x)
    GPIO.output(pinin2, GPIO.LOW)
    GPIO.output(pinin4, GPIO.LOW)

print "Run slow"
#pwm1.start(30)
#pwm2.start(30)
pwm1.ChangeDutyCycle(10)
pwm2.ChangeDutyCycle(10)
forward(5)
reverse(5)
print "Run fast"
#pwm1.start(60)
#pwm2.start(60)
pwm1.ChangeDutyCycle(60)
pwm2.ChangeDutyCycle(60)
forward(5)
reverse(5)
print "Stopping motor"

GPIO.cleanup()
