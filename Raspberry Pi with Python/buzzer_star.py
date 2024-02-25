import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)

scale = [523, 587, 659, 698, 784, 880, 988, 1047]
twinkle = [1, 1, 5, 5, 6, 6, 5, 4, 4, 3, 3, 2, 2 ,1,
	5, 5, 4, 4, 3, 3, 2, 5, 5, 4, 4, 3, 3, 2,
	1, 1, 5, 5, 6, 6, 5, 4, 4, 3, 3, 2, 2, 1]

pwm = GPIO.PWM(18, 2000)
pwm.start(1)
for i in range(0, 42):
	pwm.ChangeFrequency(scale[twinkle[i]])
	if i == 6 or i == 13 or i == 20 or i == 27 or i == 34 or i == 41:
		time.sleep(1.0)
	else:
		time.sleep(0.5)

pwm.ChangeDutyCycle(0.0)

pwm.stop()
GPIO.cleanup()
