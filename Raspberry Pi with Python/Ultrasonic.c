#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>

#define trigPin 28
#define echoPin 29

int main(void)
{
    wiringPiSetup();

    int distance = 0;
    long startime, endtime;

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    for (int i = 0; i < 200; i++)
    {
        digitalWrite(trigPin, LOW);
        usleep(2);
        digitalWrite(trigPin, HIGH);
        usleep(20);
        digitalWrite(trigPin, LOW);
        while(digitalRead(echoPin) == LOW);
        startime = micros();
        while(digitalRead(echoPin) == HIGH);
        endtime = micros() - startime;
        distance = endtime / 58;
        printf("%d\n", distance);
        sleep(1);
    }
    return 0;
}