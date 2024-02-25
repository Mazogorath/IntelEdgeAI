#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <time.h>
#define SW1 3
#define SW2 4
#define SW3 5
#define SW4 6

int main(void){
	int i, ret = 2;
	if(wiringPiSetup() == -1)
		return 1;
	pinMode(SW1, INPUT);
	pinMode(SW2, INPUT);
	pinMode(SW3, INPUT);
	pinMode(SW4, INPUT);

	for (int i = 0; i < 20; i++){
		ret = digitalRead(SW1);
		if (ret == 0)
			printf("SW1 Button pushed\n");
		ret = digitalRead(SW2);
		if (ret == 0)
			printf("SW2 Button pushed\n");
		ret = digitalRead(SW3);
		if (ret == 0)
			printf("SW3 Button pushed\n");
		ret = digitalRead(SW4);
		if (ret == 0)
			printf("SW4 Button pushed\n");
		sleep(1);
	}
	return 0;
}
