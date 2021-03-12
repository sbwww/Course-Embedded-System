#include "reg51.h"

void delay(unsigned char i){
	unsigned char j, k;
	for (j = 0; j < i; ++j)
		for (k = 0; k < 100; ++k);
}

int main(){
	while(1){
		P07 = 1;
		P27 = 1;
		delay(250);
		delay(250);
		P07 = 0;
		P27 = 0;
		delay(250);
		delay(250);
	}
	return 0;
}