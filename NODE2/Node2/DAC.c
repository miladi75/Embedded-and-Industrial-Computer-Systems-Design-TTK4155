/*
 * DAC.c
 *
 * Created: 09.11.2022 18:44:04
 *  Author: danie
 */ 
#include "sam.h"

void dac_init() {
	
	// enable clock for DAC:    DIV = 0 (clk = MCK), CMD = 0 (read), PID = 38 (DAC)
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_DACC << PMC_PCR_PID_Pos);
	PMC->PMC_PCER1 |= 1 << (ID_DACC - 32);

	// select channel 1, 16-bit conversions, normal mode without refresh, startup time of 1024 clock cycles
	DACC->DACC_MR = DACC_MR_USER_SEL_CHANNEL1 | DACC_MR_WORD_HALF | DACC_MR_STARTUP_0;

	// enable channel 1
	DACC->DACC_CHER = DACC_CHER_CH1;

	dac_write(0);
}

void dac_write(uint16_t data) {
	DACC->DACC_CDR = data;

	while (!DACC->DACC_ISR & DACC_ISR_EOC);
}