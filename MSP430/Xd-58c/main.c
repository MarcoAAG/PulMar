#include <msp430g2553.h>
#include <stdint.h>
#include "uart.h"
#include "clock.h"
#include "timer.h"


int flag_timer = 0;
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

	P1DIR |= BIT6;
	P1SEL =0;
	P1SEL2 = 0;
	P1OUT &= ~BIT6;

	/* Create uart config struct */
	uart_reg my_port;
	my_port.clk_source = SMCLK;
	my_port.parity_enable = PARITY_DISABLE;
	my_port.msb_or_lsb = LSB_FIRST;
	my_port.length_data = DATA_8_BIT;
	my_port.stop_bit = ONE_STOP_BIT;

	clockInit(set_1Mhz);
	timerAInit((uint32_t)250000);
	uartInit(&my_port);

	/* enable interrupts */
	_BIS_SR(GIE);
	while (1);
	
	// while (1)
	// {
	// 	/* code */
	// 	if (flag_timer)
	// 	{
	// 		sendS(send_data);
	// 		flag_timer = 0;
	// 	}
	// }

	return 0;
}

/* Interrupt service */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
	flag_timer++;
	if (flag_timer == 2)
	{
		P1OUT ^= BIT6;
		flag_timer = 0;
	}
}


// void configIO(void)
// {
// 	P1OUT = 0;
// 	P1SEL = 0;
// 	P1SEL2 = 0;
// 	P1DIR = LED;
// 	/* Setting the UART ports */
// 	P1SEL |= RX | TX;
// 	P1SEL2 |= RX | TX;
// }

// void sendC(unsigned char c)
// {
// 	while (!(IFG2 & UCA0TXIFG))
// 		;
// 	UCA0TXBUF = c;
// }

// void sendS(unsigned char *str)
// {
// 	while (*str)
// 	{
// 		sendC(*str);
// 		str++;
// 	}
// }
