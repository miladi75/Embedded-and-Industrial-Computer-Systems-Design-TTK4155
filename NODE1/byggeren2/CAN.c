/*
 * CAN.c
 *
 * Created: 27.10.2022 11:05:09
 *  Author: trymkd
 */ 
#include <avr/io.h>
#include "CAN.h"
#include "MCP.h"
#include "MCP2515.h"
#include <stdio.h>
#include <avr/interrupt.h>

#include "JOYSTICK.h"


void CAN_init() {
	MCP_setup();
	_delay_ms(10);
	
	MCP_write_data_SPI(MCP_CNF3, 0x05);
	MCP_write_data_SPI(MCP_CNF2, 0xb1);
	MCP_write_data_SPI(MCP_CNF1, 0x03);
	
	MCP_set_mode(MODE_NORMAL);
	
	MCP_modify_wr_instr(MCP_CANINTE, 0b11111111, 0b1); 
}



void CAN_receive_msg(message_t *msg) {
	
	uint8_t ID_CAN_LOW = MCP_read_addr(MCP_RXB0SIDL)/0b100000;
	uint8_t ID_CAN_HIGH = MCP_read_addr(MCP_RXB0SIDH);
	msg->id = ID_CAN_HIGH * 0b1000 + ID_CAN_LOW;
	
	msg->length = MCP_read_addr(MCP_RXB0DLC);

	for (int i = 0; i < msg->length; i++) {
		msg->data[i] = MCP_read_addr(MCP_RXB0D0 + i);
	}
	


}

void CAN_send_msg(message_t* message) {
	
	MCP_write_data_SPI(MCP_TXB0SIDH, message->id / 8); // Set ID
	MCP_write_data_SPI(MCP_TXB0SIDL, (message->id % 8) << 5);
	
	MCP_write_data_SPI(MCP_TXB0DLC, message->length);

	
	for (int i = 0; i < message->length; i++) {
		MCP_write_data_SPI(MCP_TXB0D0 + i, message->data[i]);
	}

	MCP_reg_data_wr(0);
}

//Using buffer 1 mainly
void CAN_receive_n2(message_t *msg) {
	
	
	uint8_t ID_CAN_LOW = MCP_read_addr(MCP_RXB1SIDL)/0b100000;
	uint8_t ID_CAN_HIGH = MCP_read_addr(MCP_RXB1SIDH);
	msg->id = ID_CAN_HIGH * 0b1000 + ID_CAN_LOW;

	// Data length. RXBnDLC
	msg->length = MCP_read_addr(MCP_RXB1DLC);

	// Data (optional). RXBnDM
	for (int i = 0; i < msg->length; i++) {
		msg->data[i] = MCP_read_addr(MCP_RXB1D0 + i);
	}
	


}

//sending joystick values via CAN
message_t CAN_send_joystick(joystick_dir_t dir, uint8_t can_id){
	
	message_t message;
	message.id	= can_id;
	
	switch(dir){
		case UP:
			message.data[0] = (uint8_t)UP;
			break;
		case DOWN:
			message.data[0] = (uint8_t)DOWN;
			break;
		case RIGHT:
			message.data[0] = (uint8_t)RIGHT;
			break;
		case LEFT:
			message.data[0] = (uint8_t)LEFT;
			break;
		case NEUTRAL:
			message.data[0] = (uint8_t)NEUTRAL;
			break;
		default:
			printf("\nDEFAULT CASE in send_joystick_can(...) RUNNING\n");
		
	}
	message.length = 1;
	
	return message;
}


//Send a text string over CAN
message_t CAN_send_string(char* c, uint8_t size, uint8_t can_id){
	message_t message;
	message.id	= can_id;
	message.length = size;
	for(uint8_t i = 0 ; i< size; i++){
		message.data[i] = c[i];
		if(message.data[i]=='\0'){
			return message;
			break;
		}
	}
	return message;
}



message_t CAN_send_clicked_btn(){
	message_t msg;
	msg.length = 4;
	msg.id = 30;
	msg.data[0] = button_right();
	msg.data[1] = button_left();
	msg.data[2] = joystick_slider_readRight();
	msg.data[3] = joystick_slider_readLeft();
	
	
	return msg;
}





message_t CAN_send_coord(){
	message_t message;
	message.id = 20;
	coord_t xy;
	xy.x = (joystick_read_xVal() + 93);
	xy.y = (joystick_read_yVal() + 94);
	
	message.length = 2;
	
	message.data[0] = xy.x;
	
	message.data[1] = xy.y;
	
	return message;
	
}
