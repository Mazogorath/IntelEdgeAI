import RPi.GPIO as GPIO
import time
import random
import numpy as np

GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.OUT)
GPIO.setup(5, GPIO.OUT)
GPIO.setup(6, GPIO.OUT)
GPIO.setup(22, GPIO.IN)
GPIO.setup(23, GPIO.IN)
GPIO.setup(24, GPIO.IN)
GPIO.setup(25, GPIO.IN)

print("RGB에 대해 각각 1, 2, 3번 스위치 누르기")
count = 0
for i in range(0, 10):
    color = np.random.randint(1, 4)
    waittime = np.random.uniform(0.5, 1.0)
    precount = count
    start = time.time()
    if color == 1:
        GPIO.output(4, True)
        while time.time() - start <= waittime:
            if GPIO.input(22) == GPIO.LOW:
                print("정답")
                count += 1
                break
            elif GPIO.input(23) == GPIO.LOW or GPIO.input(24) == GPIO.LOW:
                print("오답")
                precount = 0
                break
    elif color == 2:
        GPIO.output(5, True)
        while time.time() - start <= waittime:
            if GPIO.input(23) == GPIO.LOW:
                print("정답")
                count += 1
                break
            elif GPIO.input(22) == GPIO.LOW or GPIO.input(24) == GPIO.LOW:
                print("오답")
                precount = 0
                break
    elif color == 3:
        GPIO.output(6, True)
        while time.time() - start <= waittime:
            if GPIO.input(24) == GPIO.LOW:
                print("정답")
                count += 1
                break
            elif GPIO.input(22) == GPIO.LOW or GPIO.input(23) == GPIO.LOW:
                print("오답")
                precount = 0
                break
    GPIO.output(4, False)
    GPIO.output(5, False)
    GPIO.output(6, False)
    if count == precount:
        print("miss")
    time.sleep(0.3)

print("최종점수는 ", count)
GPIO.cleanup()