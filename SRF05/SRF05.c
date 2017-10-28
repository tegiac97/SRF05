// DSPIC30F6010A Configuration Bit Settings
// 'C' source line config statements
// FOSC
#pragma config FOSFPR = HS              // Oscillator (HS)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF             // Watchdog Timer (Enabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV20          // Brown Out Voltage (Reserved)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config LPOL = PWMxL_ACT_HI      // Low-side PWM Output Polarity (Active High)
#pragma config HPOL = PWMxH_ACT_HI      // High-side PWM Output Polarity (Active High)
#pragma config PWMPIN = RST_IOPIN       // PWM Output Pin Reset (Control with PORT/TRIS regs)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FBS
#pragma config BWRP = WR_PROTECT_BOOT_OFF// Boot Segment Program Memory Write Protect (Boot Segment Program Memory may be written)
#pragma config BSS = NO_BOOT_CODE       // Boot Segment Program Flash Memory Code Protection (No Boot Segment)
#pragma config EBS = NO_BOOT_EEPROM     // Boot Segment Data EEPROM Protection (No Boot EEPROM)
#pragma config RBS = NO_BOOT_RAM        // Boot Segment Data RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WR_PROT_SEC_OFF   // Secure Segment Program Write Protect (Disabled)
#pragma config SSS = NO_SEC_CODE        // Secure Segment Program Flash Memory Code Protection (No Secure Segment)
#pragma config ESS = NO_SEC_EEPROM      // Secure Segment Data EEPROM Protection (No Segment Data EEPROM)
#pragma config RSS = NO_SEC_RAM         // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = GSS_OFF            // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define FCY 2000000UL
#define trig1 _LATD1
#define echo1 _RD0
#define trig2 _LATD3
#define echo2 _RD2
#define trig3 _LATD5
#define echo3 _RD4

#include<stdio.h>
#include <xc.h>
#include<p30f6010a.h>
#include<libpic30.h>
#include"uart.h"

unsigned int time = 0;
float dis;

//float distance(unsigned trig, unsigned echo) {
//	printf("Start function\n");
//	float dis;
//	int time = 0;
//	trig = 0; printf("trig=0");
//	__delay_ms(100);
//	T1CONbits.TON = 1; 
//	trig = 1; printf("trig=1");
//	__delay_us(5);
//	trig = 0;
//	while (echo == 0) TMR3 = 0;
//	while (echo == 1);
//	time = TMR3;
//	__delay_ms(100);
//	T1CONbits.TON = 0;
//	dis = ((float)time * 340 * 100 / 62500);
//	time = 0;
//	return dis;
//}

void initTimer() {
	T3CON = 0;
	T3CONbits.TCKPS = 10;
	PR3 = 20000;
	IEC0bits.T3IE = 1;
	T3CONbits.TON = 1;
}
int main() {
	initTimer();
	_TRISD0 = 1;
	_TRISD1 = 0;
	_TRISD2 = 1;
	_TRISD3 = 0;
	_TRISD4 = 1;
	_TRISD5 = 0;
	trig1 = 0;
	echo1 = 0;
	trig2 = 0;
	echo2 = 0;
	trig3 = 0;
	echo3 = 0;
	enableUART1(1, 0, 0, 1, 12);
	while (1)
	{
		trig1 = 0;
		__delay_ms(100);
		T1CONbits.TON = 1;							//Enable timer
		trig1 = 1;									//Bat dau phat song
		__delay_us(5);								//Phat trong 5us
		trig1 = 0;
		while (echo1 == 0) TMR3 = 0;				//set thanh ghi timer 3 =0
		while (echo1 == 1);
		time = TMR3;								//Doc gia tri tren thanh ghi TMR3
		__delay_ms(100);
		T1CONbits.TON = 0;							//Tat timer
		dis = ((float)time * 340 * 100 / 62500);
		time = 0;
		printf("Dis1: %.0f cm\t\t", dis);
		//__delay_ms(200);





		trig2 = 0;
		__delay_ms(100);
		T1CONbits.TON = 1;
		trig2 = 1;
		__delay_us(5);
		trig2 = 0;
		while (echo2 == 0) TMR3 = 0;
		while (echo2 == 1);
		time = TMR3;
		__delay_ms(100);
		T1CONbits.TON = 0;
		dis = ((float)time * 340 * 100 / 62500);
		time = 0;
		printf("Dis2: %.0f cm\t\t", dis);
		//__delay_ms(200);





		trig3 = 0;
		__delay_ms(100);
		T1CONbits.TON = 1;
		trig3 = 1;
		__delay_us(5);
		trig3 = 0;
		while (echo3 == 0) TMR3 = 0;
		while (echo3 == 1);
		time = TMR3;
		__delay_ms(100);
		T1CONbits.TON = 0;
		dis = ((float)time * 340 * 100 / 62500);
		time = 0;
		printf("Dis3: %.0f cm\n\r", dis);
		__delay_ms(100);
	}
	while (1) {
		float dis;
		dis = distance(trig1, echo1);
		printf("Dis= %.0f cm\t\t", dis);
		__delay32(100);
	}
}
