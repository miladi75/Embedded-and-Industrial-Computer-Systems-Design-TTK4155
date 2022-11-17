/*
 * ADC.c
 *
 * Created: 03.11.2022 14:18:59
 *  Author: danie
 */ 
#include "sam.h"
#include "adc.h"
#define TRUE 1
#define FALSE 0

#define F_CPU 84000000L
#define __SAM3X8E__


void busyWait(){
	for(long unsigned int i =0 ; i< 1000000000; i++){
		;
	}
}

void delay(void) {
    uint16_t t;
    for (t = 0; t < F_CPU/4; t++)
        __asm__ volatile("nop\n\t"); // busy wait
}

void ADC_init(void){
	
	ADC->ADC_MR = ADC_MR_FREERUN; //12-bit, no prescaler, freerun mode
	ADC->ADC_CHER = ADC_CHER_CH0; // AD0 peripheral, PIO pin PA2, pin A7 on shield
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_ADC << PMC_PCR_PID_Pos);
	PMC->PMC_PCER1 |= 1 << (ID_ADC - 32); //clk = mck, 
	ADC->ADC_CR = ADC_CR_START; // start
	
	
 }
 
 
 uint16_t ADC_read(){
	 uint16_t adc_value = ADC->ADC_CDR[0];
	 //printf("adc_valuec %d \n",adc_value);
	 if(adc_value<=1000){
		 //printf("-----------------> %d\n", ADC->ADC_CDR[0]);
		 //busyWait();
		 //delay();
		 return FALSE;
		 
	 }else{
		//printf("-----------------> %d\n", ADC->ADC_CDR[0]);	 
		 //busyWait();
		 //delay();
		 return TRUE;
	 }
	 
	 
	 
 }

	
