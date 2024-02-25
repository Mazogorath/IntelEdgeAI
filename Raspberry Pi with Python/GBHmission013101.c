#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <wiringPi.h>
#define ledr 7
#define ledg 21
#define ledb 22

int main(void) {
    wiringPiSetup();
    pinMode(7, OUTPUT);
    pinMode(21, OUTPUT);
    pinMode(22, OUTPUT);
    printf("        빛의 삼원색 게임        \n");
    printf("색을 합치고 어떤 색이 될 지 알아보자\n");
    int color[3] = { 1, 2, 3 };
    char colors[4] = { 'n', 'r', 'g', 'b' };
    while (1) {
        int x = rand() % 4;
        if (x < 2) x = 2;
        int a = 4, b = 4, c = 4;
        while (1) {
            if (x == 2)
                a = rand() % 4, b = rand() % 4;
            else if (x == 3)
                a = rand() % 4, b = rand() % 4, c = rand() % 4;
            if (a != 0 && b != 0 & c != 0 && a != b && b != c && a != c) break;
        }
        if (x == 2) {
            int mix = a + b;
            printf("%c와 %c를 혼합하면 무슨 색?\n", colors[a], colors[b]);
            printf("1 Yellow   2 Magenta   3 Cyan\n");
            int answer = 0;
            scanf("%d", &answer);
            if (answer == mix - 2) {
                printf("정답입니다\n");
                digitalWrite(ledr, 1);
                delay(100);
                digitalWrite(ledg, 1);
                digitalWrite(ledr, 0);
                delay(100);
                digitalWrite(ledg, 0);
                digitalWrite(ledb, 1);
                delay(100);
                digitalWrite(ledb, 0);
            }
            else {
                printf("오답입니다\n");
                digitalWrite(ledr, 1);
                delay(150);
                digitalWrite(ledr, 0);
                delay(150);
            }
            if (x == 3) {
                printf("%c와 %c, %c를 혼합하면 무슨 색?\n", colors[a], colors[b], colors[c]);
                printf("1 Yellow   2 Magenta   3 Cyan   4 White\n");
                int answer = 0;
                scanf("%d", &answer);
                if (answer == 4) {
                    printf("정답입니다\n");
                    printf("정답입니다\n");
                    digitalWrite(ledr, 1);
                    delay(100);
                    digitalWrite(ledg, 1);
                    digitalWrite(ledr, 0);
                    delay(100);
                    digitalWrite(ledg, 0);
                    digitalWrite(ledb, 1);
                    delay(100);
                    digitalWrite(ledb, 0);
                }
                else {
                    printf("오답입니다\n");
                    digitalWrite(ledr, 1);
                    delay(50);
                    digitalWrite(ledr, 0);
                    delay(50);
                }
            }
        }
    }
    return 0;
}

