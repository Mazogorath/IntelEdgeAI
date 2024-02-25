import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)

scale = [523, 587, 659, 698, 784, 880, 988, 1047, 1397, 1568, 1976, 494]
corridor = [7, 9, 10, 8, 7, 9, 10, 8, 7, 9, 10, 8, 7, 9, 10, 8, 4, 4, 2, 2, 4, 3, 2, 6, 3, 3, 3, 3]

pwm = GPIO.PWM(18, 10000)
pwm.start(10)
for i in range(0, 16):
	pwm.ChangeFrequency(scale[corridor[i]])
	time.sleep(0.5)
for i in range(16, 20):
	pwm.ChangeFrequency(scale[corridor[i]])
	time.sleep(1)
for i in range(20, 32):
	pwm.ChangeFrequency(scale[corridor[i]])
	time.sleep(0.5)

pwm.ChangeDutyCycle(0.0)

pwm.stop()
GPIO.cleanup()
