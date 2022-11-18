/*
 * MCP.h
 *
 * Created: 27.10.2022 10:47:22
 *  Author: trymkd
 */ 


#ifndef MCP_H_
#define MCP_H_


void MCP_setup();


uint8_t MCP_read_addr(uint8_t this_addr);


void MCP_write_data_SPI(uint8_t this_addr, char data);


void MCP_reg_data_wr(int buffer_number);


char MCP_rd_wr_instr();


void MCP_modify_wr_instr(uint8_t this_addr, uint8_t mask, uint8_t data);


void MCP_reset_SPI();

void MCP_set_mode(uint8_t mode);






#endif /* MCP_H_ */