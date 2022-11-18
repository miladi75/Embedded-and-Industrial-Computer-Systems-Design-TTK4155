/*
 * SPI.c
 *
 * Created: 27.10.2022 10:09:43
 *  Author: trymkd
 */ 
#include <avr/io.h>
#include "SPI.h"
#include "UART.h"
#include <avr/interrupt.h>
#include "MCP2515.h"
#include <stdio.h>

#define DATA_DIR_SPI DDRB
#define DATA_DIR_SS PB4
#define DATA_DIR_MOSI PB5
#define DATA_DIR_MISO PB6
#define DATA_DIR_SCK PB7

void SPI_master_setup() {
	//setup SPI master
	DATA_DIR_SPI = (1 << DATA_DIR_MOSI) | ( 1<< DATA_DIR_SCK) | ( 1 << DATA_DIR_SS);
	SPCR = (1 << SPE) | ( 1<< MSTR) | (1<< SPR0) | (1<<SPIE);
	SPI_set_ss();
}

void SPI_slave_setup() {
	// Enable SPI Control register and set bit 6 on spi control register
	
	DATA_DIR_SPI = (1<<DATA_DIR_MISO);
	
	SPCR = (1<<SPE);
}

void SPI_write_reg(char cData) {
	
	//write data to spi_register and wait for it to finish
	SPDR = cData;
	while(!(SPSR & (1<<SPIF))) {
	}
}

uint8_t SPI_read_status() {
	SPDR = 0xFF; 
	while(!(SPSR & (1<<SPIF))) {
	}
	return SPDR;
	

}

void SPI_set_ss() {
	//Set slave select on spi data register
	PORTB |= (1 << DATA_DIR_SS);
	
}

void SPI_clear_ss() {
	//clear slave select on spi data register
	PORTB &= ~(1 << DATA_DIR_SS);
	
}