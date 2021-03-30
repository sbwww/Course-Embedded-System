#include "reg51.h"

unsigned char code LED_7_code[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                                   0x6D, 0x7D, 0x07, 0x7F, 0x67};

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

int main() {
    unsigned int num = 0;
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
        ++num;
    }
    return 0;
}