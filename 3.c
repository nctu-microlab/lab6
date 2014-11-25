#include <REG_MPC82G516.h>

void delay() {
	unsigned short i;
	for(i=0; i<65535; i++);
}

void left_to_right() interrupt 0 {
	P1 = 0x7F;
	
	while(1) {
		if(P1 == 0xFE)
			P1 = 0x7F;
		else {
			P1 >>= 1;
			P17 = 1;
		}
		
		delay();
	}
}

void right_to_left() interrupt 2 {
	P1 = 0xFE;
	
	while(1) {
		if(P1 == 0x7F)
			P1 = 0xFE;
		else {
			P1 <<= 1;
			P10 = 1;
		}
		
		delay();
	}
}

void main() {
	IE = 0x85;
	TCON = 5;
	IP = 1;
	SP = 0x60;
	
	P1 = 0;
	while(1) {
		P1 = ~P1;
		delay();
	}
}
