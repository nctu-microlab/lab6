#include <REG_MPC82G516.h>

unsigned char now_second;
unsigned char alert_second;
unsigned char LED_flash;

bit display_mode; //0 for time, 1 for alert

void timerup() interrupt 1 {
	static unsigned char timer_count = 0;
	
	timer_count++;
	TH0 = (65536-50000) >> 8;
	TL0 = (65536-50000) & 0x00FF;
	
	if(LED_flash && timer_count % 5 == 0) {
		if(!P20)
			--LED_flash;
		
		P20 = ~P20;
	}
	
	if(timer_count == 20) {
		timer_count = 0;
		
		if(++now_second >= 60) {
			now_second = 0;
		}
		
		if(alert_second == now_second) {
			LED_flash = 5;
		}
	}
}

void add_ten() interrupt 0 {
	if(display_mode && (alert_second+=10) >= 60)
		alert_second -= 60;
}

void add_one() interrupt 2 {
	if(display_mode && ++alert_second >= 60)
		alert_second -= 60;
}

void delay() {
	unsigned char i;
	for(i=0; i<255; i++);
}

void main() {
	bit clicked = 0;
	
	IE = 0x87;
	IP = 2;
	TMOD = 1;
	
	now_second = 0;
	alert_second = 0;
	display_mode = 0;
	LED_flash = 0;
	
	TH0 = (65536-50000) >> 8;
	TL0 = (65536-50000) & 0x00FF;
	TR0 = 1;
	
	IT0 = 1;
	IT1 = 1;
	while(1) {
		unsigned char display_num = display_mode ? alert_second : now_second;
		
		P1 = display_num / 10;
		P17 = 0;
		delay();
		
		P1 = display_num % 10;
		P17 = 1;
		delay();
		
		if(!P30 && !clicked) {
			display_mode = ~display_mode;
			clicked = 1;
		}
		if(P30 && clicked) {
			clicked = 0;
		}
	}
}
