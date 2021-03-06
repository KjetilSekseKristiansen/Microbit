#include "gpiote.h"
#include "gpio.h"

#define GPIOTE ((NRF_GPIOTE_REG*)0x40006000)

typedef struct {
	// Tasks
	volatile uint32_t OUT[4];
	// Events
	volatile uint32_t RESERVED0[60];
	volatile uint32_t IN[4];
	volatile uint32_t RESERVED1[27];
	volatile uint32_t PORT;
	// Registers
	volatile uint32_t RESERVED2[96];
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RESERVED3[129];
	volatile uint32_t CONFIG[4];
} NRF_GPIOTE_REG;

int gpiote_surveil_A_button(){
    GPIOTE->CONFIG[0] = (17<<8)| 1 | (2<<16);
	GPIOTE->CONFIG[1] = (13<<8)| 3 | (1<<16);
	GPIOTE->CONFIG[2] = (14<<8)| 3 | (1<<16);
	GPIOTE->CONFIG[3] = (15<<8)| 3 | (1<<16);
}
