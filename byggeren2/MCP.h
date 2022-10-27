/*
 * MCP.h
 *
 * Created: 27.10.2022 10:47:22
 *  Author: trymkd
 */ 


#ifndef MCP_H_
#define MCP_H_


void mcp_init();


uint8_t mcp_read(uint8_t address);


void mcp_write(uint8_t address, char *data);


void mcp_request_to_send(int buffer_number);


char mcp_read_status();


void mcp_bit_modify(uint8_t address, uint8_t mask, uint8_t data);


void mcp_reset();

void mcp_set_mode(uint8_t mode);


 char mcp_get_mode();



#endif /* MCP_H_ */