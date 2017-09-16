#pragma once
#define FCY 2000000UL
#define trig LATDbits.LATD1
#define echo PORTDbits.RD0

#include<stdio.h>
#include<libpic30.h>
#include<p30F6010A.h>

void initsrf05() {
	T1CON = 0;
	T1CONbits.TCKPS = 10;
	PR1 = 20000;
	IEC0bits.T1IE = 1;						//Bat ngat timer 1
	T1CONbits.TON = 1;						//bat timer1;
	TRISDbits.TRISD0 = 1;					//quy dinh chan echo doc tin hieu
	TRISDbits.TRISD1 = 0;					//chan trig xuat tin hieu
	trig = 0;
	echo = 0;
}

double pulseIn() {							//ham tra ve thoi gian song bat dau phat di va nhan lai
	unsigned int time;
	trig = 0;
	__delay_ms(100);
	T1CONbits.TON = 1;						//trig=0, timer bat dau chay
	trig = 1;
	__delay_us(5);							//trig phat xung trong 5uS
	trig = 0;
	while (echo == 0) TMR1 = 0;
	while (echo == 1);
	time = TMR1;
	return time;
}
