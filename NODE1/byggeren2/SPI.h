/*
 * SPI.h
 *
 * Created: 27.10.2022 10:10:03
 *  Author: trymkd
 */ 


#ifndef SPI_H_
#define SPI_H_


void SPI_master_setup();


void SPI_slave_setup();


void SPI_write_reg(char cData);


uint8_t SPI_read_status();

void SPI_set_ss();


void SPI_clear_ss();



#endif /* SPI_H_ */