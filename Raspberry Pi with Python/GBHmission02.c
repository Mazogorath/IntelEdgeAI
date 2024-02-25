#include <stdio.h>
#include <wiringPi.h>
#define BUZZER 1

int scale[] = {523, 587, 659, 698, 784, 880, 988, 1047, 1175, 1319, 1397};
int corridor[] = {8, 3, 6, 7, 10, 3, 6, 7, 9, 3, 6, 7, 10, 3, 6, 7};


int main(void)
{
    if (wiringPiSetup() == -1)
        return 1;
    
    pinMode(BUZZER, PWM_OUTPUT);
    pwmSetClock(10);
    pwmSetMode(PWM_MODE_MS);
    
    for (int i = 0; i < 16; i++)
    {
        pwmSetRange(1000000/scale[corridor[i]]);
        pwmWrite(BUZZER, 1000000/scale[corridor[i]]/10);
        delay(500);
    }

    pwmWrite(BUZZER, 0);
    return 0;
}