/*
 * DAC.c
 *
 * Created: 09.11.2022 18:44:04
 *  Author: danie
 */ 
#include "sam.h"

void DAC_init() {
	
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_DACC << PMC_PCR_PID_Pos);// enable clock, clk = MCK, PID = 38 
	PMC->PMC_PCER1 |= 1 << (ID_DACC - 32);

	DACC->DACC_MR = DACC_MR_USER_SEL_CHANNEL1 | DACC_MR_WORD_HALF | DACC_MR_STARTUP_0;//channel 1, normal mode

	DACC->DACC_CHER = DACC_CHER_CH1;// enable channel 1

	DAC_write(0);
}

void DAC_write(uint16_t data) {
	DACC->DACC_CDR = data;

	while (!DACC->DACC_ISR & DACC_ISR_EOC);
}