import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)

scale = [523, 587, 659, 698, 784, 880, 988, 1047]
airplane = [2, 1, 0, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 1, 0, 1, 2, 2, 2, 1, 1, 2, 1, 0]

pwm = GPIO.PWM(18, 2000)
pwm.start(1)
for i in range(0, 42):
	pwm.ChangeFrequency(scale[airplane[i]])
	if i == 6 or i == 9 or i == 12 or i == 19 or i == 22:
		time.sleep(1.0)
	else:
		time.sleep(0.5)

pwm.ChangeDutyCycle(0.0)

pwm.stop()
GPIO.cleanup()
