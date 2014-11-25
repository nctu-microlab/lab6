#include <REG_MPC82G516.h>

void delay() {
	unsigned short i;
	for(i=0; i<65535; i++);
}

void left_to_right() interrupt 0 {
	unsigned char original = P1;
	P1 = 0x7F;
	
	while(1) {
		delay();
		
		if(P1 == 0xFE)
			break;
		else {
			P1 >>= 1;
			P17 = 1;
		}
	}
	
	P1 = original;
}

void right_to_left() interrupt 2 {
	unsigned char original = P1;
	P1 = 0xFE;
	
	while(1) {
		delay();
		
		if(P1 == 0x7F)
			break;
		else {
			P1 <<= 1;
			P10 = 1;
		}
	}
	
	P1 = original;
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
