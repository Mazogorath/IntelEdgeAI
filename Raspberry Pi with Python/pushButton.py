import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)
GPIO.setup(22, GPIO.IN)
GPIO.setup(23, GPIO.IN)
GPIO.setup(24, GPIO.IN)
GPIO.setup(25, GPIO.IN)

scale = [523, 587, 659, 698, 784, 880, 988, 1047, 1175, 1319, 1397, 1568, 1976, 494]
airplane = [2, 1, 0, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 1, 0, 1, 2, 2, 2, 1, 1, 2, 1, 0]
corridor = [8, 3, 6, 7, 10, 3, 6, 7, 9, 3, 6, 7, 10, 3, 6, 7, 1, 3, 6, 7, 10, 3, 6, 7, 9, 3, 6, 7, 10, 3, 6, 7]
lavender = [7, 11, 12, 10, 7, 11, 12, 10, 7, 11, 12, 10, 7, 11, 12, 10, 4, 4, 2, 2, 4, 3, 2, 6, 3, 3, 3, 3]
dodol = [0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0]

def Airplane():
	pwm = GPIO.PWM(18, 10000)
	pwm.start(1)
	for i in range(0, 13):
		pwm.ChangeFrequency(scale[airplane[i]])
		if (GPIO.input(25) == GPIO.LOW):
			pwm.stop()
			return
		if i == 6 or i == 9 or i == 12 or i == 19 or i == 22:
			time.sleep(0.5)
		else:
			time.sleep(0.2)
	pwm.ChangeDutyCycle(0.0)
	pwm.stop()
def Corridor():
	pwm = GPIO.PWM(18, 10000)
	pwm.start(1)
	for i in range(0, 16):
		if (GPIO.input(25) == GPIO.LOW):
			pwm.stop()
			return
		pwm.ChangeFrequency(scale[corridor[i]])
		time.sleep(0.2)
	pwm.ChangeDutyCycle(0.0)
	pwm.stop()
def Lavender():
	pwm = GPIO.PWM(18, 10000)
	pwm.start(1)
	for i in range(0, 16):
		pwm.ChangeFrequency(scale[lavender[i]])
		if (GPIO.input(25) == GPIO.LOW):
			pwm.stop()
			return
		time.sleep(0.2)
	pwm.ChangeDutyCycle(0.0)
	pwm.stop()
def Dodol():
	pwm = GPIO.PWM(18, 10000)
	pwm.start(1)
	for i in range(0, 16):
		if (GPIO.input(25) == GPIO.LOW):
			pwm.stop()
			return
		pwm.ChangeFrequency(scale[dodol[i]])
		if i == 8:
			time.sleep(0.5)
		else:
			time.sleep(0.2)
	pwm.ChangeDutyCycle(0.0)
	pwm.stop()

print("SW1 : Doremi   SW2 : Corridos of Time   SW3 : Lavender Town   SW4 : Cancel")

try:
	while True:
		if GPIO.input(22) == GPIO.LOW:
			GPIO.setup(4, GPIO.OUT)
			GPIO.output(4, True)
			Dodol()
			GPIO.output(4, False)
			GPIO.setup(4, GPIO.IN)
		elif GPIO.input(23) == GPIO.LOW:
			GPIO.setup(5, GPIO.OUT)
			GPIO.output(5, True)
			Corridor()
			GPIO.output(5, False)
			GPIO.setup(5, GPIO.IN)
		elif GPIO.input(24) == GPIO.LOW:
			GPIO.setup(6, GPIO.OUT)
			GPIO.output(6, True)
			Lavender()
			GPIO.output(6, False)
			GPIO.setup(6, GPIO.IN)
		time.sleep(0.1)

except KeyboardInterrupt:
	pass
GPIO.cleanup()
