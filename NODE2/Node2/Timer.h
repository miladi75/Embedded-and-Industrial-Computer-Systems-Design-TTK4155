/*
 * Timer.h
 *
 * Created: 10.11.2022 11:13:16
 *  Author: danie
 */ 


#ifndef TIMER_H_
#define TIMER_H_




static void SysTick_init_us(int period);

void SysTick_Handler(void);

void delay_us(uint16_t us);

void delay_ms(uint16_t ms);

#endif /* TIMER_H_ */