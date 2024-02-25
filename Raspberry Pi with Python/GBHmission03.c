#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <time.h>
#define BUZZER 1
#define SW1 3
#define SW2 4
#define SW3 5
#define SW4 6

int scale[] = {523, 587, 659, 698, 784, 880, 988, 1047, 1175, 1319, 1397, 1568, 1976, 494};
int corridor[] = {8, 3, 6, 7, 10, 3, 6, 7, 9, 3, 6, 7, 10, 3, 6, 7, 1, 3, 6, 7, 10, 3, 6, 7, 9, 3, 6, 7, 10, 3, 6, 7};
int lavender[] = {7, 11, 12, 10, 7, 11, 12, 10, 7, 11, 12, 10, 7, 11, 12, 10, 4, 4, 2, 2, 4, 3, 2, 6, 3, 3, 3, 3};
int doremi[] = {0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0};

void Corridor()
{
    for (int i = 0; i < 16; i++)
    {
        pwmSetRange(1000000/scale[corridor[i]]);
        pwmWrite(BUZZER, 1000000/scale[corridor[i]]/10);
        if (digitalRead(SW4) == 0)
        {
            pwmSetClock(0);
            return;
        }
        delay(500);
    }
    pwmSetClock(0);
}
void Doremi()
{
    for (int i = 0; i < 16; i++)
    {
        pwmSetRange(1000000/scale[doremi[i]]);
        pwmWrite(BUZZER, 1000000/scale[doremi[i]]/10);
        if (digitalRead(SW4) == 0)
        {
            pwmSetClock(0);
            return;
        }
        delay(500);
    }
    pwmSetClock(0);
}
void Lavender()
{
    for (int i = 0; i < 16; i++)
    {
        pwmSetRange(1000000/scale[lavender[i]]);
        pwmWrite(BUZZER, 1000000/scale[lavender[i]]/10);
        if (digitalRead(SW4) == 0)
        {
            pwmSetClock(0);
            return;
        }
        delay(500);
    }
    pwmSetClock(0);
}

int main(void)
{
    if (wiringPiSetup() == -1)
        return 1;
   	pinMode(SW1, INPUT);
	pinMode(SW2, INPUT);
	pinMode(SW3, INPUT);
	pinMode(SW4, INPUT);
    pinMode(BUZZER, PWM_OUTPUT);
    pwmSetClock(19);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(0);
    printf("1 : Doremi   2 : Corridors of Time   3 : Lavender Town   4 : Cancel\n");
    while(1)
    {
        if (digitalRead(SW1) == 0)
        {
            pwmSetClock(10);
            Doremi();
            pwmSetClock(0);
        }

        if (digitalRead(SW2) == 0)
        {
            pwmSetClock(10);
            Corridor();
            pwmSetClock(0);
        }

        if (digitalRead(SW3) == 0)
        {
            pwmSetClock(10);
            Lavender();
            pwmSetClock(0);
        }
    }
    pwmWrite(BUZZER, 0);
    return 0;
}