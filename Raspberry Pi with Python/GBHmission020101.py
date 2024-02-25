import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.OUT)
GPIO.setup(18, GPIO.OUT)
GPIO.setup(27, GPIO.IN)

try:
    while 1:
        pir_state = GPIO.input(27)
        if pir_state == True:
            print("Motion Detected")
            GPIO.output(18, True)
            time.sleep(0.5)
            GPIO.output(18, False)
        else:
            GPIO.output(4, False)
            time.sleep(1)

except KeyboardInterrupt:
    pass

GPIO.cleanup()