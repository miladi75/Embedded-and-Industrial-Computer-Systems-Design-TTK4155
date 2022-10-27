/*
 * SPI.h
 *
 * Created: 27.10.2022 10:10:03
 *  Author: trymkd
 */ 


#ifndef SPI_H_
#define SPI_H_


void spi_master_init();


void spi_slave_init();


void spi_write(char cData);


uint8_t spi_read();

void spi_set_ss();


void spi_clear_ss();



#endif /* SPI_H_ */