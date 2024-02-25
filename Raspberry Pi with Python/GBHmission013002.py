import RPi.GPIO as GPIO
import time
import math
ledr = 4

GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.OUT)

try:
	while True:
		print("1 LEDOn   2 LEDOff   3 LEDLighter   4 LEDDarker   5 LEDLD   6 LEDLDforseconds   0 exit")
		menu  = input()
		menu = int(menu)
		if menu == 1:
			GPIO.output(4, True)
		elif menu == 2:
			GPIO.output(4, False)
		elif menu == 3:
			for i in range(1, 55):
				GPIO.output(4, True)
				time.sleep(0.001 * i)
				GPIO.output(4, False)
				time.sleep(0.055 - 0.001 * i)
		elif menu == 4:
			for i in range(1, 55):
				GPIO.output(4, True)
				time.sleep(0.055 - 0.001 * i)
				GPIO.output(4, False)
				time.sleep(0.001 * i)
		elif menu == 5:
			for i in range(1, 39):
				GPIO.output(4, True)
				time.sleep(0.001 * i)
				GPIO.output(4, False)
				time.sleep(0.039 - 0.001 * i)
			for j in range(1, 39):
				GPIO.output(4, True)
				time.sleep(0.039 - 0.001 * j)
				GPIO.output(4, False)
				time.sleep(0.001 * j)
		elif menu == 6:
			print("몇 초?")
			whatsec = input()
			whatsec = int(whatsec)
			second = math.sqrt(menu * 1000)
			second = int(second)
			for i in range(1, second):
				GPIO.output(4, True)
				time.sleep(0.001 * i)
				GPIO.output(4, False)
				time.sleep(0.001 * second - 0.001 * i)
			for j in range(1, second):
				GPIO.output(4, True)
				time.sleep(0.001 * second - 0.001 * j)
				GPIO.output(4, False)
				time.sleep(0.001 * j)
		elif menu == 0:
			print("장비를 정지합니다")
			GPIO.cleanup()
			break
except KeyboardInterrupt:
	pass
GPIO.cleanup()
