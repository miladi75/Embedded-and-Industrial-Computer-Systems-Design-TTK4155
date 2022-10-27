/*
 * MCP.c
 *
 * Created: 27.10.2022 10:47:09
 *  Author: trymkd
 */ 
#include <avr/io.h>
#include "MCP.h"
#include "SPI.h"
#include "MCP2515.h"
#include <stdio.h>

void mcp_init() {
	spi_master_init();
	mcp_reset();

	// Self-test.
	uint8_t value = mcp_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf("MCP!config %x \r\n", value);
	}
}

uint8_t mcp_read(uint8_t address) {
	spi_clear_ss();
	spi_write(MCP_READ);
	spi_write(address);
	uint8_t data = spi_read();
	spi_set_ss();

	return data;
}

void mcp_write(uint8_t address, uint8_t data) {
	spi_clear_ss();
	spi_write(MCP_WRITE);
	spi_write(address);
	spi_write(data);
	spi_set_ss();
}

void mcp_request_to_send(int buffer_number) {
	spi_clear_ss();
	buffer_number = buffer_number % 3; // Map buffer number to 0, 1, 2 in case of number > 2
	char data = MCP_RTS_TX0;
	if (buffer_number == 0) {
		data = MCP_RTS_TX0;
		} else if (buffer_number == 1) {
		data = MCP_RTS_TX1;
		} else if (buffer_number == 2) {
		data = MCP_RTS_TX2;
	}
	spi_write(data);
	spi_set_ss();
}

char mcp_read_status() {
	spi_clear_ss();
	spi_write(MCP_READ_STATUS);
	char data = spi_read();
	spi_set_ss();

	return data;
}

void mcp_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
	spi_clear_ss();
	spi_write(MCP_BITMOD);
	spi_write(address);
	spi_write(mask);
	spi_write(data);
	spi_set_ss();
}

void mcp_reset() {
	spi_clear_ss();
	spi_write(MCP_RESET);
	spi_set_ss();
}

void mcp_set_mode(uint8_t mode) {
	mcp_bit_modify(MCP_CANCTRL, 0b11100000, mode);
}