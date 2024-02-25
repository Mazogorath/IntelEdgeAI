import RPi.GPIO as GPIO
import time
import threading
flag_exit = False

led_pin = 4

GPIO.setmode(GPIO.BCM)


def t1():
    GPIO.setup(4, GPIO.OUT)
    pwm = GPIO.PWM(4, 10000)
    pwm.start(10)


    while True:
        for t_high in range(1, 101, 1):
            pwm.ChangeDutyCycle(t_high)
            time.sleep(0.01)
        for t_high in range(100, 1, -1):
            pwm.ChangeDutyCycle(t_high)
            time.sleep(0.01)
        if flag_exit:
            pwm.stop()
            break

thread = threading.Thread(target = t1)
thread.start()

try:
    while True:
        print("main")
        time.sleep(1)

except KeyboardInterrupt:
    pass
flag_exit = True
thread.join()
GPIO.cleanup()
