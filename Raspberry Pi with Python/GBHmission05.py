import RPi.GPIO as GPIO
import time
import threading
from flask import Flask, render_template, url_for, redirect

GPIO.setmode(GPIO.BCM)

led_dict = {'red': 14, 'green': 15, 'blue': 18}
GPIO.setup(led_dict['red'], GPIO.OUT)
GPIO.setup(led_dict['green'], GPIO.OUT)
GPIO.setup(led_dict['blue'], GPIO.OUT)

thread_state = {'red':0, 'green':0, 'blue':0}
app = Flask(__name__)

def LED_blink_core():
    past_time = int(time.time())
    led_state_dict = {'red': 0, 'green': 0, 'blue': 0}
    while True:
        current_time = int(time.time())
        if current_time - past_time > 0.9:
            for color_idx in ['red', 'green', 'blue']:
                led_state_dict[color_idx] = not led_state_dict[color_idx]
                if thread_state[color_idx]:
                    GPIO.output(led_dict[color_idx], led_state_dict[color_idx])
            past_time = current_time

thread = threading.Thread(target = LED_blink_core, args = ())

thread.start()

@app.route('/')
def home():
    return render_template('led1sec.html')

@app.route('/<color>/<int:state>')
def LED_control(color, state):
    thread_state[color] = False
    GPIO.output(led_dict[color], state)
    return redirect(url_for('home'))

@app.route('/<color>')
def LED_blink(color):
    thread_state[color] = True
    return redirect(url_for('home'))

@app.route('/all/<int:state>')
def whole_control(state):
    if state == 0 or state == 1:
        for color_idx in ['red', 'green', 'blue']:
            thread_state[color_idx] = False
            GPIO.output(led_dict[color_idx], state)
    elif state == 2:
        for color_idx in ['red', 'green', 'blue']:
            thread_state[color_idx] = True
    return redirect(url_for('home'))

if __name__ == '__main__':
    app.run(host = "192.168.0.124", port = "8080")
