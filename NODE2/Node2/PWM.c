/*
 * PWM.c
 *
 * Created: 30.10.2022 11:03:52
 *  Author: danie
 */ 
#include "sam.h"
#include "PWM.h"

void PWM_init(void){
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;
	
	PIOC->PIO_OER |= PIO_PC19;
	PIOC->PIO_PDR |= PIO_PC19;
	PIOC->PIO_ABSR |= PIO_ABSR_P19;
	
	PWM->PWM_WPCR &= ~PIO_WPMR_WPEN;
	REG_PWM_CMR5 = PWM_CMR_CPRE_MCK_DIV_1024 | PWM_CMR_CPOL;
	REG_PWM_CPRD5 = 1640;
	REG_PWM_CDTY5 = 123;
	REG_PWM_ENA = PWM_ENA_CHID5;
	
	
}

void set_servo_pos(int value){
	//value = value - 64; //offset comp from joystick
	//if (value < 64)
	//{
		//value = 64;
	//}
	REG_PWM_CDTY5 = 92 + value*98/255;//74
	//int test = (92 + value*98/255);//bare for testing
	printf("%d\n",REG_PWM_CDTY5);//bare for testing
}