from flask import Flask, render_template, url_for, redirect
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)

led_pin_dict = {'red': 14, 'green': 15, 'blue': 18}
GPIO.setup(led_pin_dict['red'], GPIO.OUT)
GPIO.setup(led_pin_dict['green'], GPIO.OUT)
GPIO.setup(led_pin_dict['blue'], GPIO.OUT)
led_state_dict = {'red':0, 'green':0, 'blue':0}

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('ledcontrol.html', led_state_dict = led_state_dict)

@app.route('/<color>/<int:state>')
def LED_control(color, state):
    led_state_dict[color] = state
    GPIO.output(led_pin_dict['red'], led_state_dict['red'])
    GPIO.output(led_pin_dict['green'], led_state_dict['green'])
    GPIO.output(led_pin_dict['blue'], led_state_dict['blue'])
    return redirect(url_for('home'))

@app.route('/all/<int:state>')
def whole_control(state):
    if state == 0:
        led_state_dict['red'] = 0
        led_state_dict['green'] = 0
        led_state_dict['blue'] = 0
    elif state == 1:
        led_state_dict['red'] = 1
        led_state_dict['green'] = 1
        led_state_dict['blue'] = 1

    GPIO.output(led_pin_dict['red'], led_state_dict['red'])
    GPIO.output(led_pin_dict['green'], led_state_dict['green'])
    GPIO.output(led_pin_dict['blue'], led_state_dict['blue'])
    return redirect(url_for('home'))

if __name__ == '__main__':
    app.run(host = "192.168.0.124", port = "8080")