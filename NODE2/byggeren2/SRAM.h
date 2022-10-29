/*
 * SRAM.h
 *
 * Created: 10/20/2022 11:28:47 AM
 *  Author: seyed
 */ 


#ifndef SRAM_H_
#define SRAM_H_

void SRAM_init(void);

void SRAM_test(void);

void xmem_write ( uint8_t data , uint16_t addr );
uint8_t xmem_read ( uint16_t addr );



#endif /* SRAM_H_ */