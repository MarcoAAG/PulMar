#include <msp430g2553.h>
#include <stdint.h>

#define SENSOR BIT0
#define RX BIT1
#define TX BIT2
#define LED BIT6

/* ********** FUNCTION'S PROTOTYPE ********** */

/*
	* Input = void
	* Output = void
*/
void uartInit(void);

/*
	* Input = void
	* Output = void
*/
void clockInit(void);

/*
	* Input = int 16bits
	* Output = void
*/
void timerAInit(uint32_t delay);

void configIO(void);

void sendC(unsigned char c);

int flag = 0;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
	clockInit();
	timerAInit(30000);
	uartInit();
	configIO();

	/* enable interrupts */
	_BIS_SR(GIE);
	while (1)
	{
		/* code */
	}

	return 0;
}

/* Interrupt service */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
	flag++;
	if (flag == 2)
	{
		P1OUT ^= LED;
		flag = 0;
	}
}

/* ********** FUNCTION'S BODY ********** */
void uartInit(void)
{
	/* 1. Set UCSWRST (BIS.B #UCSWRST,&UCAxCTL1) */
	/* 2. Initialize all USCI registers with UCSWRST = 1 (including UCAxCTL1) */
	/* 3. Configure ports.*/
	/* 4. Clear UCSWRST via software (BIC.B #UCSWRST,&UCAxCTL1) */
	/* 5. Enable interrupts (optional) via UCAxRXIE and/or UCAxTXIE */

	/* #1 */
	UCA0CTL1 = UCSWRST;

	/* #2 */
	UCA0CTL1 |= UCSSEL_2; /* Set SMCLK */
	UCA0CTL0 = 0;		  /* Parity Disable */
						  /* Odd parity */
						  /* LSB first */
						  /* 8bits */
						  /* One Stop bit */
						  /* USCI Mode (UART) */
						  /* Asynchronous Mode */
	UCA0BR0 = 104;		  /* Baud Rate (Getting from Family User's Guide) */

	/* #4 */
	UCA0CTL1 &= ~UCSWRST;

	/* #5 */
	IE2 |= UCA0RXIE; /* Receive interrup enable */
}
void clockInit(void)
{
	BCSCTL1 = CALBC1_1MHZ; /* Basic clock system control 1 */
	DCOCTL = CALDCO_1MHZ;  /* control register */
}
void timerAInit(uint32_t delay)
{
	double period = 7.27; /* period in us*/
	uint16_t timer_ratio = (uint16_t)(delay / period);

	TA0CTL = TASSEL_2 | ID_3 | MC_1 | TACLR; /* TASSEL_2 -> SMCLK */
											 /* ID_3 -> Source clock divided by 8 */
											 /* MC_1 -> Up mode */
											 /* TACLR -> timer clear */
	TACCR0 = timer_ratio - 1;				 /* count of Timer_A */
	CCTL0 = CCIE;							 /* Capture/compare interrupt enable. */
}

void configIO(void)
{
	P1OUT = 0;
	P1SEL = 0;
	P1SEL2 = 0;
	P1DIR = LED;
	/* Setting the UART ports */
	P1SEL |= RX | TX;
	P1SEL2 |= RX | TX;
}

void sendC(unsigned char c)
{
	while (!(IFG2 & UCA0TXIFG))
		;
	UCA0TXBUF = c;
}