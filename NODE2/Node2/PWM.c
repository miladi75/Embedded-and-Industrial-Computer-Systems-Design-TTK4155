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
	int arr[50];
	//
	//if (mesurment == amaount)
	//{
		//int value = value1;
	//}
	//
	for(int i = 0; i<50;i++){
		arr[i] = 92 + value*96/255;
	}
	//value = 92 + value*96/255;
	
	//if (value> 126 && value< 129)
	//{
		//value = 127;
	//}
	
	
	//
	//int last_value = value;
	//
	//printf("value-last: %d\n",value-last_value);
	//if ((value-last_value)>2)
	//{
		////REG_PWM_CDTY5 =  value;
		//printf("value1: %d\n",value);
	//}
	//else 
	//{
		//REG_PWM_CDTY5 =  value;
		//printf("value2: %d\n",value);
	//}
	//
	
	
	//if(abs(value-next_value)<2){
		//REG_PWM_CDTY5 =  next_value;
		//printf("PWM value:%d\n",REG_PWM_CDTY5);//
	//}
	//
	
	//int new_value = value/2 + 123;
	//
	//if (new_value < 74)
	//{
		//new_value = 74;
	//}
	//if (new_value > 172)
	//{
		//new_value = 172;
	//}
	
	REG_PWM_CDTY5 = value; //92 + value*98/255;//74
	//int test = (92 + value*98/255);//bare for testing
	//printf("PWM value:%d\n",REG_PWM_CDTY5);//bare for testing
}