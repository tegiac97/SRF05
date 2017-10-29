//DO NOT EDIT THIS SOURCE CODE


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
#define trig1 _LATD9
#define echo1 _RD8
#define trig2 _LATD11
#define echo2 _RD10
#define trig3 _LATD13
#define echo3 _RD12
#define echo4 _RD14
#define trig4 _LATD15
#define echo5 _RC1
#define trig5 _LATC3


#include<stdio.h>
#include<xc.h>
#include<p30f6010a.h>
#include<libpic30.h>

unsigned int time = 0;
float dis;

void initTimer() {
	T3CON = 0;								//reset timer 3 ve 0
	T3CONbits.TCKPS = 10;					//Timer Input Clock Prescale Select		11 = 1:256 prescale value	10 = 1:64 prescale value		01 = 1 : 8 prescale value		00 = 1 : 1 prescale value
	PR3 = 20000;							//Timer3 Period Register
	//IEC0bits.T3IE = 1;
	T3CONbits.TON = 1;						//Bat timer 3
}

void UART_Init() {
	U1BRG = 12;
	U1MODEbits.UARTEN = 1;
}

int main() {
	initTimer();
	UART_Init();
	_TRISD8 = 1;
	_TRISD9 = 0;
	_TRISD10 = 1;
	_TRISD11 = 0;
	_TRISD12 = 1;
	_TRISD13 = 0;
	_TRISD14 = 1;
	_TRISD15 = 0;
	_TRISC1 = 1;
	_TRISC3 = 0;
	trig1 = 0;
	echo1 = 0;
	trig2 = 0;
	echo2 = 0;
	trig3 = 0;
	echo3 = 0;
	trig4 = 0;
	echo4 = 0;
	trig5 = 0;
	echo5 = 0;
	
	while (1)
	{
		trig1 = 0;
		__delay_ms(100);
		T3CONbits.TON = 1;							//Enable timer
		trig1 = 1;									//Bat dau phat song
		__delay_us(5);								//Phat trong 5us
		trig1 = 0;
		while (echo1 == 0) TMR3 = 0;				//set thanh ghi timer 3 =0
		while (echo1 == 1);
		time = TMR3;								//Doc gia tri tren thanh ghi TMR3
		__delay_ms(100);
		T3CONbits.TON = 0;							//Tat timer
		dis = ((float)time * 340 * 100 / 62500);
		time = 0;
		printf("Dis1: %.0f cm\t", dis);
		//__delay_ms(200);





		trig2 = 0;
		__delay_ms(100);
		T3CONbits.TON = 1;
		trig2 = 1;
		__delay_us(5);
		trig2 = 0;
		while (echo2 == 0) TMR3 = 0;
		while (echo2 == 1);
		time = TMR3;
		__delay_ms(100);
		T3CONbits.TON = 0;
		dis = ((float)time * 340 * 100 / 62500);
		time = 0;
		printf("Dis2: %.0f cm\t", dis);
		//__delay_ms(200);





		trig3 = 0;
		__delay_ms(100);
		T3CONbits.TON = 1;
		trig3 = 1;
		__delay_us(5);
		trig3 = 0;
		while (echo3 == 0) TMR3 = 0;
		while (echo3 == 1);
		time = TMR3;
		__delay_ms(100);
		T3CONbits.TON = 0;
		dis = ((float)time * 340 * 100 / 62500);
		time = 0;
		printf("Dis3: %.0f cm\t", dis);
		__delay_ms(100);



		trig4 = 0;
		__delay_ms(100);
		T3CONbits.TON = 1;
		trig4 = 1;
		__delay_us(5);
		trig4 = 0;
		while (echo4 == 0) TMR3 = 0;
		while (echo4 == 1);
		time = TMR3;
		__delay_ms(100);
		T3CONbits.TON = 0;
		dis = ((float)time * 340 * 100 / 62500);
		time = 0;
		printf("Dis4: %.0f cm\t", dis);




		trig5 = 0;
		__delay_ms(100);
		T3CONbits.TON = 1;
		trig5 = 1;
		__delay_us(5);
		trig5 = 0;
		while (echo5 == 0) TMR3 = 0;
		while (echo5 == 1);
		time = TMR3;
		__delay_ms(100);
		T3CONbits.TON = 0;
		dis = ((float)time * 340 * 100 / 62500);
		time = 0;
		printf("Dis5: %.0f cm", dis);
		printf("\n\r");
	}
}
