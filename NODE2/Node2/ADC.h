/*
 * ADC.h
 *
 * Created: 03.11.2022 14:19:12
 *  Author: danie
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "sam.h"

void ADC_init(void); // ADC set-up


uint16_t ADC_read(); // for reading from ADC



#endif /* ADC_H_ */