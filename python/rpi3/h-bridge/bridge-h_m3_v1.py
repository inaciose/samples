# Define GPIO pin signals to use
StepPinForward=17
StepPinBackward=27
StepPinPWM=12

# define other variables
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
GPIO.setup(StepPinForward, GPIO.OUT)
GPIO.setup(StepPinBackward, GPIO.OUT)
GPIO.setup(StepPinPWM, GPIO.OUT)

# set GPIO pins initial value
GPIO.output(StepPinForward, GPIO.LOW)
GPIO.output(StepPinBackward, GPIO.LOW)

pwm1 = GPIO.PWM(StepPinPWM, 60)
pwm1.start(0)

def forward(x):
    GPIO.output(StepPinForward, GPIO.HIGH)
    print "forwarding running motor "
    time.sleep(x)
    GPIO.output(StepPinForward, GPIO.LOW)

def reverse(x):
    GPIO.output(StepPinBackward, GPIO.HIGH)
    print "backwarding running motor"
    time.sleep(x)
    GPIO.output(StepPinBackward, GPIO.LOW)

print "Run slow"
pwm1.start(30)
forward(5)
reverse(5)

print "Run fast"
pwm1.start(60)
forward(5)
reverse(5)
print "Stopping motor"

GPIO.cleanup()
