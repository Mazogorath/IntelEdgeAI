import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
switches = [22, 23, 24, 25]
smotor = [16, 17, 18, 19]

for i in range(0, 4):
    GPIO.setup(smotor[i], GPIO.OUT)
    GPIO.setup(switches[i], GPIO.IN)

def Rotate(angle):
    steps = int(angle / 0.95)

    for i in range(steps):
        for pin in smotor:
            GPIO.output(pin, True)
            time.sleep(0.002)
            GPIO.output(pin, False)

try:
    while True:
        if GPIO.input(switches[0]) == GPIO.LOW:
            Rotate(120)
            print("45도 회전")
            time.sleep(0.1)
        elif GPIO.input(switches[1]) == GPIO.LOW:
            Rotate(240)
            print("90도 회전")
            time.sleep(0.1)
        elif GPIO.input(switches[2]) == GPIO.LOW:
            Rotate(480)
            print("180도 회전")
            time.sleep(0.1)

except KeyboardInterrupt:
    GPIO.cleanup()