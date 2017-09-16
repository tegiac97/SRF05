// DSPIC30F6010A Configuration Bit Settings
// 'C' source line config statements
// FOSC
#pragma config FOSFPR = HS              // Oscillator (HS)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disable)

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
#define trig LATDbits.LATD9
#define echo PORTDbits.RD8

#include"lcd.h"
#include"uart.h"
#include"srf05.h"


int main() {
	enableUART1(1, 0, 0, 1, 12);
	TRISD = 0x00;
	Lcd_Init();
	float time;
	double distance;
	char temp[30];
	while (1) {
		initsrf05();
		time = pulseIn();
		distance = time * 340 * 100 / 62500;
		Lcd_Clear();
		Lcd_Set_Cursor(1, 1);
		Lcd_Write_String("Distance: ");
		Lcd_Set_Cursor(2, 1);
		sprintf(temp, "%.1f", distance);
		Lcd_Write_String(temp);
		printf("Distance: %.1f cm\n\r", distance);
		__delay_ms(100);
	}
}






//
//unsigned int time1=0,time2=0;
//double dis;
//char led[30];
//
//
//void initTimer() {
//	T3CON = 0;
//	T3CONbits.TCKPS = 10;
//	PR3 = 20000;
//	IEC0bits.T3IE = 1;
//	T3CONbits.TON = 1;
//}
//int main() {
//	unsigned int a;
//	TRISD = 0x00;
//	Lcd_Init();
//	initTimer();
//	TRISDbits.TRISD8 = 1;
//    TRISDbits.TRISD9=0;
//    trig=0;
//    echo=0;
//	enableUART1(1, 0, 0, 1, 12);
//	while (1)
//	{
//        trig=0;
//        __delay_ms(100);
//        T1CONbits.TON = 1;
//        trig=1;
//        __delay_us(5);
//        trig=0;
//        while(echo==0) TMR3 = 0;
//        while(echo==1) ;
//        time2 = TMR3;
//        __delay_ms(100);
//		T1CONbits.TON = 0;
//		dis = ((double)time2*340*100/62500);
//        time2=0;
//        printf("Distance: %.1f cm\n\r", dis);
//		Lcd_Clear();
//		Lcd_Set_Cursor(1, 1);
//		Lcd_Write_String(led);
//		sprintf(led, "Distance: %.1f cm", dis);
//		__delay_ms(200);
//	}
//}
