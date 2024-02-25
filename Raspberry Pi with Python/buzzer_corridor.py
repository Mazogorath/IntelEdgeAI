import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)

scale = [523, 587, 659, 698, 784, 880, 988, 1047, 1175, 1319, 1397]
corridor = [8, 3, 6, 7, 10, 3, 6, 7, 9, 3, 6, 7, 10, 3, 6, 7, 1, 3, 6, 7, 10, 3, 6, 7, 9, 3, 6, 7, 10, 3, 6, 7]

pwm = GPIO.PWM(18, 10000)
pwm.stop()
time.sleep(0.05)
pwm.start(30)
for i in range(0, 32):
	pwm.ChangeFrequency(scale[corridor[i]])
	time.sleep(0.2)

pwm.ChangeDutyCycle(0.0)

pwm.stop()
GPIO.cleanup()
