import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.OUT)
GPIO.setup(5, GPIO.OUT)
GPIO.setup(6, GPIO.OUT)

def makePattern(p1, t1, p2, t2, p3, t3, p4, t4, p5, t5, p6, t6):
	GPIO.output(p1, True)
	time.sleep(t1)
	GPIO.output(p1, False)
	GPIO.output(p2, True)
	time.sleep(t2)
	GPIO.output(p2, False)
	GPIO.output(p3, True)
	time.sleep(t3)
	GPIO.output(p3, False)
	GPIO.output(p4, True)
	time.sleep(t4)
	GPIO.output(p4, False)
	GPIO.output(p5, True)
	time.sleep(t5)
	GPIO.output(p5, False)
	GPIO.output(p6, True)
	time.sleep(t6)
	GPIO.output(p6, False)
	GPIO.cleanup()

print("LED 패턴 암기")
presskey = input()
print("Red = 4, Green = 5, Blue = 6\n")
print("키려는 색의 LED와 시간 순서로 총 6개 입력해주세요.")
colors = []
for i in range(0, 12):
	x = int(input())
	colors.append(x)

makePattern(colors[0], colors[1], colors[2], colors[3], colors[4], colors[5], colors[6],
		 colors[7], colors[8], colors[9], colors[10], colors[11])
