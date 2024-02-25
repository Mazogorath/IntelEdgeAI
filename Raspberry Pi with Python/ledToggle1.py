from flask import Flask
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)

red = 14
green = 15
blue = 18
GPIO.setup(red, GPIO.OUT)
GPIO.setup(green, GPIO.OUT)
GPIO.setup(blue, GPIO.OUT)

app = Flask(__name__)

@app.route('/')
def hello():
    return "LED 제어를 위해 주소 변경하세요"

@app.route('/red_on')
def red_on():
    GPIO.output(red, True)
    return 'LED Red On'

@app.route('/green_on')
def green_on():
    GPIO.output(green, True)
    return "LED Green On"

@app.route('/blue_on')
def blue_on():
    GPIO.output(blue, True)
    return "LED Blue On"

@app.route('/LED off')
def LED_off():
    GPIO.output(red, False)
    GPIO.output(green, False)
    GPIO.output(blue, False)
    return "LED OFF"

@app.route('/clean up')
def cleanUp():
    GPIO.cleanup()
    return "clean up"

if __name__ == '__main__':
    app.run(host = '192.168.0.124', port = 8080)