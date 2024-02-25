import RPi.GPIO as GPIO
import threading
import time
flag_exit = False

def t1():
    while True:
        print("\tt1")
        time.sleep(0.5)
        if flag_exit:
            break

thread = threading.Thread(target = t1)
thread.start()

try:
    while True:
        print("main\n")
        time.sleep(1)

except KeyboardInterrupt:
    pass
    thread.join()
#flag_exit = True
