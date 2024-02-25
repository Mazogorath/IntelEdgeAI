#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <stdlib.h>
#define SW1 3
#define SW2 4
#define SW3 5
#define SW4 6
#define STEP_OUTA 27
#define STEP_OUTB 0
#define STEP_OUT2A 1
#define STEP_OUT2B 24

void rotate(int angle){
    for(int i=0;i<(angle * 1.15);i++){
                digitalWrite(STEP_OUTA,1);
                usleep(5000);
                digitalWrite(STEP_OUTA,0);
                usleep(5000);
                digitalWrite(STEP_OUTB,1);
                usleep(5000);
                digitalWrite(STEP_OUTB,0);
                digitalWrite(STEP_OUT2A,1);
                usleep(5000);
                digitalWrite(STEP_OUT2A,0);
                digitalWrite(STEP_OUT2B,1);
                usleep(5000);
                digitalWrite(STEP_OUT2B,0);
        }
}

void sw1Pressed(void) {
  rotate(55);
}

void sw2Pressed(void) {
  rotate(110);
}

void sw3Pressed(void) {
  rotate(220);
}

void sw4Pressed(void) {
  printf("Program terminated\n");
  exit(0);
}

int main(void){
        if(wiringPiSetup () == -1)
                return 1;

        pinMode(SW1,INPUT);
        pinMode(SW2,INPUT);
        pinMode(SW3,INPUT);
        pinMode(SW4,INPUT);
        pinMode(STEP_OUTA,OUTPUT);
        pinMode(STEP_OUTB,OUTPUT);
        pinMode(STEP_OUT2A,OUTPUT);
        pinMode(STEP_OUT2B,OUTPUT);
        digitalWrite(STEP_OUTA,0);
        digitalWrite(STEP_OUTB,0);
        digitalWrite(STEP_OUT2A,0);
        digitalWrite(STEP_OUT2B,0);
        wiringPiISR(SW1, INT_EDGE_FALLING, sw1Pressed);
        wiringPiISR(SW2, INT_EDGE_FALLING, sw2Pressed);
        wiringPiISR(SW3, INT_EDGE_FALLING, sw3Pressed);
        wiringPiISR(SW4, INT_EDGE_FALLING, sw4Pressed);

        while (1) {}

        return 0;
}