from flask import Flask, render_template, url_for, redirect
import RPi.GPIO as GPIO
import time
import threading

GPIO.setmode(GPIO.BCM)
led_pin_dict = {'red': 14, 'green':15, 'blue':18}
GPIO.setup(led_pin_dict['red'], GPIO.OUT)
GPIO.setup(led_pin_dict['green'], GPIO.OUT)
GPIO.setup(led_pin_dict['blue'], GPIO.OUT)
thread_state = {'red':0, 'green':0, 'blue':0}

app = Flask(__name__)

def LED_on_3_sec_core(color):
    while True:
        past_time = int(time.time())
        while thread_state[color]:
            GPIO.output(led_pin_dict[color], GPIO.HIGH)
            current_time = int(time.time())
            if current_time - past_time > 3:
                GPIO.output(led_pin_dict[color], GPIO.LOW)
                thread_state[color] = False

thread_dict = {'red':threading.Thread(target=LED_on_3_sec_core, args=('red',)),
               'green':threading.Thread(target=LED_on_3_sec_core, args=('green',)),
               'blue':threading.Thread(target=LED_on_3_sec_core, args=('blue',))}

for color_idx in ['red', 'green', 'blue']:
    thread_dict[color_idx].start()

@app.route('/')
def home():
    return render_template('led3sec.html')

@app.route('/<color>/<int:state>')
def LED_control(color, state):
    thread_state[color] = False
    GPIO.output(led_pin_dict[color], state)
    return redirect(url_for("home"))

@app.route('/<color>')
def LED_on_3_sec(color):
    thread_state[color] = True
    return redirect(url_for("home"))

@app.route('/all/<int:state>')
def whole_control(state):
    if state == 0 or state == 1:
        for color_idx in ['red', 'green', 'blue']:
            thread_state[color_idx] = False
            GPIO.output(led_pin_dict[color_idx], state)
    elif state == 2:
        for color_idx in ['red', 'green', 'blue']:
            thread_state[color_idx] = True
    return redirect(url_for("home"))
    
if __name__ == '__main__':
    app.run(host = "192.168.0.124", port = "8080")