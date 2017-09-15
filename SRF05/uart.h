#pragma once



void enableUART1(short int stopBit, short int parityData, short int autoBaud, short int transfer ,short int baudrate) {	
	U1MODEbits.STSEL = stopBit;
	U1MODEbits.PDSEL = parityData;
	U1MODEbits.ABAUD = autoBaud;
	U1STAbits.UTXEN = transfer;
	U1BRG = baudrate;
	U1MODEbits.UARTEN = 1;
}

void enableUART2(short int stopBit, short int parityData, short int autoBaud, short int transfer, short int baudrate) {
	U2MODEbits.UARTEN = 1;
	U2MODEbits.STSEL = stopBit;
	U2MODEbits.PDSEL = parityData;
	U2MODEbits.ABAUD = autoBaud;
	U2STAbits.UTXEN = transfer;
	U2BRG = baudrate;
}