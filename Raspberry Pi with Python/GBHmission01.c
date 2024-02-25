#include <stdio.h>
#include <wiringPi.h>

#define LEDRED 7
#define LEDGREEN 21
#define LEDBLUE 22

int main(void)
{
    if (wiringPiSetup() == -1)
		return 1;

    pinMode(LEDRED, OUTPUT);
    pinMode(LEDGREEN, OUTPUT);
    pinMode(LEDBLUE, OUTPUT);
    digitalWrite(LEDRED, 0);
    digitalWrite(LEDGREEN, 0);
    digitalWrite(LEDBLUE, 0);

    for (int i = 0; i < 10; i++)
    {
        digitalWrite(LEDRED, 1);
        delay(200);
        digitalWrite(LEDRED, 0);
        digitalWrite(LEDGREEN, 1);
        delay(200);
        digitalWrite(LEDGREEN, 0);
        digitalWrite(LEDBLUE, 1);
        delay(200);
        digitalWrite(LEDBLUE, 0);
    }

    return 0;
}