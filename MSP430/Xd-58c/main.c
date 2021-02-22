#include <msp430g2553.h>
#include <stdint.h>
#include "uart.h"
#include "clock.h"
#include "timer.h"
#include "adc.h"


int flag_timer = 0;
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

	P1OUT = 0;
	P1SEL = 0;
	P1SEL2 = 0;

	P1DIR |= BIT6;
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
	uartPorts(BIT2, BIT1);

	/* enable interrupts */
	_BIS_SR(GIE);
	while (1)
	{
		if(flag_timer)
		{
			sendString("A\n");
			flag_timer = 0;
		}
	}

	return 0;
}

/* Interrupt service */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
	flag_timer = 1;
}
