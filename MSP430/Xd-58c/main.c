#include <msp430g2553.h>

//* ********** FUNCTION'S PROTOTYPE **********

/*
	* Input = void
	* Output = void
*/
void uartInit(void);

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

	return 0;
}

//* ********** FUNCTION'S BODY **********
void uartInit(void)
{
	//! 1. Set UCSWRST (BIS.B #UCSWRST,&UCAxCTL1)
	//! 2. Initialize all USCI registers with UCSWRST = 1 (including UCAxCTL1)
	//! 3. Configure ports.
	//! 4. Clear UCSWRST via software (BIC.B #UCSWRST,&UCAxCTL1)
	//! 5. Enable interrupts (optional) via UCAxRXIE and/or UCAxTXIE

	//* #1
	UCA0CTL1 = UCSWRST;

	//* #2
	UCA0CTL1 |= UCSSEL_2; //* Set SMCLK
	UCA0CTL0 = 0;		  //* Parity Disable
						  //* Odd parity
						  //* LSB first
						  //* 8bits
						  //* One Stop bit
						  //* USCI Mode (UART)
						  //* Asynchronous Mode
	UCA0BR0 = 104;		  //* Baud Rate (Getting from Family User's Guide)

	//* #4
	UCA0CTL1 &= ~UCSWRST;

	//* #5
	IE2 |= UCA0RXIE; //* Receive interrup enable
}
