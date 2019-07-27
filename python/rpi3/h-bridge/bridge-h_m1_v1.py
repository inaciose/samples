import wiringpi
# using BCM GPIO number
wiringpi.wiringPiSetupGpio()

# en1 pwm
wiringpi.pinMode(13, 2)      	# pwm only works on GPIO port 18
wiringpi.pwmWrite(13, 0)    	# duty cycle between 0 and 1024. 0 = off, 1024 = fully on

# in1
wiringpi.pinMode(23, 1)         # sets GPIO to output
wiringpi.digitalWrite(23, 0)    # set GPIO output to LOW

# in2
wiringpi.pinMode(24, 1)     	# sets GPIO to output
wiringpi.digitalWrite(24, 0)	# set GPIO output to LOW

# en2 pwm
wiringpi.pinMode(12,2)          # pwm only works on GPIO port 13
wiringpi.pwmWrite(12, 0)        # duty cycle between 0 and 1024. 0 = off, 1024 = fully on

# in3
wiringpi.pinMode(17, 1)         # sets GPIO to output
wiringpi.digitalWrite(27, 0)    # set GPIO output to LOW

# in
wiringpi.pinMode(27, 1)         # sets GPIO to output
wiringpi.digitalWrite(27, 0)    # set GPIO output to LOW

print("setup done")

wiringpi.digitalWrite(23, 1)
wiringpi.pwmWrite(13, 300)

wiringpi.digitalWrite(17, 1)
wiringpi.pwmWrite(12, 300)
