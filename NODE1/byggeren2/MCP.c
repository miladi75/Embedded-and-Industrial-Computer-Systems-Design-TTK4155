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
#include <util/delay.h>


void MCP_setup() {
	SPI_master_setup();
	MCP_reset_SPI();
	_delay_ms(1); 
	
	uint8_t reg_val = MCP_read_addr(MCP_CANSTAT);
	
	//mcp mode check
	if ((reg_val & MODE_MASK) != MODE_CONFIG) {
		printf("MCP mode test %x \r\n", reg_val);
	}
}

uint8_t MCP_read_addr(uint8_t this_addr) {
	SPI_clear_ss();
	SPI_write_reg(MCP_READ);
	SPI_write_reg(this_addr);
	uint8_t data = SPI_read_status();
	SPI_set_ss();

	return data;
}

void MCP_write_data_SPI(uint8_t this_addr, char data) {
	SPI_clear_ss();
	SPI_write_reg(MCP_WRITE);
	SPI_write_reg(this_addr);
	SPI_write_reg(data);
	SPI_set_ss();
}

void MCP_reg_data_wr(int val) {
	SPI_clear_ss();
	val %= 3;
	
	char reg_buf = MCP_RTS_TX0;
	if (val == 0) {
		reg_buf = MCP_RTS_TX0;
		} else if (val == 1) {
		reg_buf = MCP_RTS_TX1;
		} else if (val == 2) {
		reg_buf = MCP_RTS_TX2;
	}
	SPI_write_reg(reg_buf);
	SPI_set_ss();
}

void MCP_set_mode(uint8_t curr_mode) {
	MCP_modify_wr_instr(MCP_CANCTRL, 0b11100000, curr_mode);
}


void MCP_modify_wr_instr(uint8_t this_addr, uint8_t data_mask, uint8_t curr_data) {
	SPI_clear_ss();
	SPI_write_reg(MCP_BITMOD);
	SPI_write_reg(this_addr);
	SPI_write_reg(data_mask);
	SPI_write_reg(curr_data);
	SPI_set_ss();
}

char MCP_rd_wr_instr() {
	SPI_clear_ss();
	SPI_write_reg(MCP_READ_STATUS);
	char reg_data = SPI_read_status();
	SPI_set_ss();

	return reg_data;
}


void MCP_reset_SPI() {
	SPI_clear_ss();
	SPI_write_reg(MCP_RESET);
	SPI_set_ss();
}

