#include "reg51.h"

unsigned char code LED_7_code[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                                   0x6D, 0x7D, 0x07, 0x7F, 0x67};

unsigned char num = 0;

void delay(unsigned int ms) {
    unsigned int i;
    unsigned char j;
    for (i = 0; i < ms; ++i) {
        for (j = 0; j < 200; ++j)
            ;
        for (j = 0; j < 102; ++j)
            ;
    }
}

void display() {
    unsigned char label_1, label_2, label_3, label_4;
    unsigned char i;
    P2 = 0xFF;
    while (1) {
        label_1 = num / 1000 % 10;
        label_2 = num / 100 % 10;
        label_3 = num / 10 % 10;
        label_4 = num / 1 % 10;

        for (i = 0; i < 0xD1; ++i) {
            P2 = 0xFF;
            P0 = LED_7_code[label_1];
            P20 = 0;
            delay(1);

            P2 = 0xFF;
            P0 = LED_7_code[label_2];
            P21 = 0;
            delay(1);

            P2 = 0xFF;
            P0 = LED_7_code[label_3];
            P22 = 0;
            delay(1);

            P2 = 0xFF;
            P0 = LED_7_code[label_4];
            P23 = 0;
            delay(1);
        }

        // delay(500);
        // ++num;
    }
}

void int_0() interrupt 0 using 0 { num = num + 1 ? num + 1 : 255; }

void int_1() interrupt 2 using 1 { num = ~(num - 1) ? num - 1 : 0; }

int main() {
    EA = 1; // 全局中断
    EX0 = 1;
    EX1 = 1;
    IT0 = 1; // 边沿触发，一按一动，电平触发会在按下的时间内触发多次
    IT1 = 1;
    display();

    return 0;
}