from flask import Flask, render_template, url_for, redirect
import RPi.GPIO as GPIO
import time
import threading

GPIO.setmode(GPIO.BCM)

led_pin_dict = {'red': 14, 'green': 15, 'blue': 18}
GPIO.setup(led_pin_dict['red'], GPIO.OUT)
GPIO.setup(led_pin_dict['green'], GPIO.OUT)
GPIO.setup(led_pin_dict['blue'], GPIO.OUT)

blink_thread_state = {'red':0, 'green':0, 'blue':0}
time_thread_state = {'red':0, 'green':0, 'blue':0}
app = Flask(__name__)
def LED_on_3_sec_core(color):
    while True:
        past_time = int(time.time())
        while time_thread_state[color]:
            GPIO.output(led_pin_dict[color], GPIO.HIGH)
            current_time = int(time.time())
            if current_time - past_time > 2.9:
                GPIO.output(led_pin_dict[color], GPIO.LOW)
                time_thread_state[color] = False
                
def LED_blink_core():
    past_time = int(time.time())
    led_state_dict = {'red': 0, 'green': 0, 'blue': 0}
    while True:
        current_time = int(time.time())
        if current_time - past_time > 0.9:
            for color_idx in ['red', 'green', 'blue']:
                led_state_dict[color_idx] = not led_state_dict[color_idx]
                if blink_thread_state[color_idx]:
                    GPIO.output(led_pin_dict[color_idx], led_state_dict[color_idx])
            past_time = current_time

blink_thread = threading.Thread(target=LED_blink_core, args=())
time_thread_dict = {'red': threading.Thread(target=LED_on_3_sec_core, args=('red', )), 
                'green' : threading.Thread(target=LED_on_3_sec_core, args=('green', )), 
                'blue': threading.Thread(target=LED_on_3_sec_core, args=('blue', ))}

# 각 스레드들을 모두 실행
blink_thread.start()
for color_idx in ['red', 'green', 'blue']:    
    time_thread_dict[color_idx].start()
    
@app.route('/')
def home():
    return render_template('led3sec1sec.html')  

@app.route('/<color>/<int:state>')
def LED_control(color, state):
    time_thread_state[color] = False
    blink_thread_state[color] = False
    GPIO.output(led_pin_dict[color], state)
    return redirect(url_for('home'))

@app.route('/<color>/time')
def LED_on_3_sec(color):
    blink_thread_state[color] = False
    time_thread_state[color] = True
    return redirect(url_for('home'))
@app.route('/<color>/blink')
def LED_blink(color):
    time_thread_state[color] = False
    blink_thread_state[color] = True
    return redirect(url_for('home'))

@app.route('/all/<int:state>')
def whole_control(state):
    if state == 0 or state == 1:
        for color_idx in ['red', 'green', 'blue']:
            time_thread_state[color_idx] = False
            blink_thread_state[color_idx] = False
            GPIO.output(led_pin_dict[color_idx], state)
    elif state == 2:
        for color_idx in ['red', 'green', 'blue']:
            time_thread_state[color_idx] = False
            blink_thread_state[color_idx] = True
    elif state == 3:
        for color_idx in ['red', 'green', 'blue']:
            blink_thread_state[color_idx] = False
            time_thread_state[color_idx] = True
    return redirect(url_for('home'))

if __name__ == "__main__":
   app.run(host="192.168.0.124", port = "8080")
