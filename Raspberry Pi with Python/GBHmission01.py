import RPi.GPIO as GPIO
import time

LEDRED = 4
LEDGREEN = 5
LEDBLUE = 6

GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.OUT)
GPIO.setup(5, GPIO.OUT)
GPIO.setup(6, GPIO.OUT)

for i in range(0, 10):
    GPIO.output(4, True)
    time.sleep(0.2)
    GPIO.output(4, False)
    GPIO.output(5, True)
    time.sleep(0.2)
    GPIO.output(5, False)
    GPIO.output(6, True)
    time.sleep(0.2)
    GPIO.output(6, False)

GPIO.cleanup()