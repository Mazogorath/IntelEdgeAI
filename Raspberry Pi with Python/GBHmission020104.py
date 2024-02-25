import RPi.GPIO as GPIO
import time
import random

GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.OUT)
GPIO.setup(5, GPIO.OUT)
GPIO.setup(6, GPIO.OUT)
GPIO.setup(18, GPIO.OUT)
GPIO.setup(22, GPIO.IN)
GPIO.setup(23, GPIO.IN)
GPIO.setup(24, GPIO.IN)
GPIO.setup(25, GPIO.IN)
ledr = 4
ledg = 5
ledb = 6
scale = [523, 587, 659]
arrLED = [ledr, ledg, ledb]
order = []
pwm = GPIO.PWM(18, 10000)

def buzzzz(cincolor):
    if cincolor == ledr:
        pwm.ChangeFrequency(scale[0])
    elif cincolor == ledg:
        pwm.ChangeFrequency(scale[1])
    elif cincolor == ledb:
        pwm.ChangeFrequency(scale[2])
    pwm.start(1)
    time.sleep(0.5)
    pwm.stop()

def LEDOn(order):
    for cincolor in order:
        GPIO.setup(cincolor, GPIO.OUT)
        GPIO.output(cincolor, GPIO.HIGH)
        buzzzz(cincolor)
        GPIO.output(cincolor, GPIO.LOW)
        time.sleep(0.3)

def userInput():
    while True:
        if GPIO.input(4) == GPIO.LOW:
            return ledr
        if GPIO.input(5) == GPIO.LOW:
            return ledg
        if GPIO.input(6) == GPIO.LOW:
            return ledb

def main():
    try:
        while True:
            order.append(random.choice(arrLED))
            LEDOn(order)

            user_input = []
            for _ in range(len(order)):
                button_pressed = userInput()
                user_input.append(button_pressed)
                buzzzz(0.1)

            if user_input != order:
                print("Game Over! Your score:", len(order) - 1)
                break
            
            if GPIO.input(25) == GPIO.LOW:
                print("강제 종료! Your score:", len(order) - 1)

            time.sleep(1)

    except KeyboardInterrupt:
        pass
    finally:
        GPIO.cleanup()

if __name__ == "__main__":
    main()