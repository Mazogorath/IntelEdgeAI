import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)

scale = [523, 587, 659, 698, 784, 880, 988, 1047]
dodol = [0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0]

pwm = GPIO.PWM(18, 2000)
pwm.start(1)
for i in range(0, 42):
	pwm.ChangeFrequency(scale[dodol[i]])
	if i == 8:
		time.sleep(1.0)
	else:
		time.sleep(0.5)

pwm.ChangeDutyCycle(0.0)

pwm.stop()
GPIO.cleanup()
