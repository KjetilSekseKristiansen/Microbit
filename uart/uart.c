#include <stdint.h>
#include <stdio.h>
#include "gpio.h"
#include "uart.h"


#define UART ((NRF_UART_REG*)0x40002000)
typedef struct {
	volatile uint32_t STARTRX;
	 volatile uint32_t STOPRX;
	 volatile uint32_t STARTTX;
	 volatile uint32_t STOPTX;
	 volatile uint32_t RESERVED0[3];
	 volatile uint32_t SUSPEND;

	 // Events
	 volatile uint32_t RESERVED1[56];
	 volatile uint32_t CTS;
	 volatile uint32_t NCTS;
	 volatile uint32_t RXDRDY;
	 volatile uint32_t RESERVED2[4];
	 volatile uint32_t TXDRDY;
	 volatile uint32_t RESERVED3[1];
	 volatile uint32_t ERROR;
	 volatile uint32_t RESERVED4[7];
	 volatile uint32_t RXTO;

	 // Registers
	 volatile uint32_t RESERVED5[110];
	 volatile uint32_t INTEN;
	 volatile uint32_t INTENSET;
	 volatile uint32_t INTENCLR;
	 volatile uint32_t RESERVED6[93];
	 volatile uint32_t ERRORSRC;
	 volatile uint32_t RESERVED7[31];
	 volatile uint32_t ENABLE;
	 volatile uint32_t RESERVED8[1];
	 volatile uint32_t PSELRTS;
	 volatile uint32_t PSELTXD;
	 volatile uint32_t PSELCTS;
	 volatile uint32_t PSELRXD;
	 volatile uint32_t RXD;
	 volatile uint32_t TXD;
	 volatile uint32_t RESERVED9[1];
	 volatile uint32_t BAUDRATE;
	 volatile uint32_t RESERVED10[17];
   volatile uint32_t CONFIG;
	 } NRF_UART_REG;

void uart_init(){
	/* setting relevant registers **/
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

	UART->PSELTXD = 24;
  UART->PSELRXD = 25;
	UART->PSELRTS = 0xFFFFFFFF;
	UART->PSELCTS = 0xFFFFFFFF;
	UART->BAUDRATE = 0x00275000;
	UART->STARTRX = 1;
	UART->ENABLE = 4;
}

void uart_send(char letter){
	UART->TXDRDY = 0;
	UART->STARTTX = 0xFFFFFFFF;
	UART->TXD = letter;
	if(UART->TXDRDY != 0){
		UART->STOPTX = 0xFFFFFFFF;
	}
}

char uart_read(){
UART->STARTRX = 0xFFFFFFFF;
UART->RXDRDY = 0;
char letter = UART->RXD;
if(letter==0)
		return '\0';

return letter;
}

int micro_transfer(){
	int sleep = 0;
	uart_init();
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}
	while(1){
			printf("%c\n",uart_read());
		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */
		if(!(GPIO->IN & (1<<26))){
			uart_send('B');
			GPIO->OUTSET=(111<<13);
		}

		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */
		if(!(GPIO->IN & (1<<17))){
			uart_send('A');
			GPIO->OUTCLR=(111<<13);
		}
		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
