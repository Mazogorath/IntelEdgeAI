import RPi.GPIO as GPIO
import time

ledr = 4
ledg = 5
ledb = 6

GPIO.setmode(GPIO.BCM)

GPIO.setup(4, GPIO.OUT)
GPIO.setup(5, GPIO.OUT)
GPIO.setup(6, GPIO.OUT)

for i in range(0, 10):
	print("red on")
	GPIO.output(ledr, True)
	time.sleep(0.1)
	print("red off\ngreen on")
	GPIO.output(ledr, False)
	GPIO.output(ledg, True)
	time.sleep(0.1)
	print("green off\nblue on")
	GPIO.output(ledg, False)
	GPIO.output(ledb, True)
	time.sleep(0.1)
	print("blue off")
	GPIO.output(ledb, False)

GPIO.cleanup()
