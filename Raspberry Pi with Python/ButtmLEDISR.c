#include <stdio.h>
#include <wiringPi.h>

volatile int led_state = LOW;
volatile int led_state_changed = 0;
void buttonPressed(void){
	led_state = (led_state == LOW) ? HIGH : LOW;
	led_state_changed = 1;
}

int main(void){
	const int button_pin = 3;
	const int led_pin = 1;
	wiringPiSetup();
	pinMode(led_pin, OUTPUT);
	wiringPiISR(button_pin, INT_EDGE_RISING, buttonPressed);
	while(1){
		if (led_state_changed == 1){
			led_state_changed = 0;
			digitalWrite(led_pin, led_state);
		}
	}
}
