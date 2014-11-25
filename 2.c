#include <REG_MPC82G516.h>

unsigned char second;
unsigned char count;

void timeup() interrupt 1 {
	count++;
	TH0 = (65536-50000) >> 8;
	TL0 = (65536-50000) & 0x00FF;
	
	if(count == 20) {
		count = 0;
		
		if(++second >= 10) {
			second = 0;
		}
		
		P1 = second;
	}
}

void main() {
	IE = 0x82;
	TMOD = 1;
	
	count = 0;
	second = 0;
	
	P1 = second;
	TH0 = (65536-50000) >> 8;
	TL0 = (65536-50000) & 0x00FF;
	TR0 = 1;
	
	while(1);
}
