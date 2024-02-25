from flask import Flask, render_template, request
import RPi.GPIO as GPIO
import time


GPIO.setmode(GPIO.BCM)

servo_pin = 14

GPIO.setup(servo_pin, GPIO.OUT)
servo = GPIO.PWM(servo_pin, 50)
servo.start(0)

servo_min_duty = 3
servo_max_duty = 12
current_deg = 90
def set_servo_degree(degree):
    GPIO.setup(servo_pin, GPIO.OUT)
    past_time = time.time()
    if degree > 180:
        degree = 180
    elif degree < 0:
        degree = 0
    duty = servo_min_duty+(degree*(servo_max_duty-servo_min_duty)/180.0)
    servo.ChangeDutyCycle(duty)
    while True:
        current_time = time.time()
        if current_time - past_time > 0.5:
            break
    GPIO.setup(servo_pin, GPIO.IN)
    return degree
    
    
set_servo_degree(current_deg)
app = Flask(__name__)
@app.route('/')
def home():
    return render_template('servoMotor.html', deg=current_deg)  

@app.route('/servo_control')
def servo_control():
    deg = request.args.get('deg')
    deg = int(deg)
    if deg < 0: deg = 0
    elif deg > 180: deg = 180
    deg = set_servo_degree(deg)
    return render_template('servoMotor.html', deg=deg)

if __name__ == "__main__":
   app.run(host="192.168.0.124", port = "8080")