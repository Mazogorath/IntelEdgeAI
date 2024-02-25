import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(22, GPIO.IN)
GPIO.setup(23, GPIO.IN)
GPIO.setup(24, GPIO.IN)
GPIO.setup(25, GPIO.IN)
GPIO.setup(18, GPIO.OUT)

try:
	while True:
		if GPIO.input(22) == GPIO.LOW:
			GPIO.output(18, True)
		else:
			GPIO.output(18, False)

except KeyboardInterrupt:
	pass
GPIO.cleanup()

