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
//#include "adc.h"
#include "JOYSTICK.h"
//#include "buttons.h"

void can_init() {
	mcp_init();
	_delay_ms(10);
	
	mcp_write(MCP_CNF3, 0x05);
	mcp_write(MCP_CNF2, 0xb1);
	mcp_write(MCP_CNF1, 0x03);
	
	mcp_set_mode(MODE_NORMAL);
	
	mcp_bit_modify(MCP_CANINTE, 0b11111111, 0b1); // Turn on interrupt for receive butter 0. Turn off all other interrupts.
}

void can_send(message_t* message) {
	// Only using buffer 0.

	// Id. TXBnSIDH og TXBnSIDL
	mcp_write(MCP_TXB0SIDH, message->id / 8); // 8 MSB bits in the ID
	mcp_write(MCP_TXB0SIDL, (message->id % 8) << 5); // 3 LSB bits in the ID
	

	// Data length. TXBnDLC
	mcp_write(MCP_TXB0DLC, message->length);

	// Data (optional). TXBnDm
	for (int i = 0; i < message->length; i++) {
		mcp_write(MCP_TXB0D0 + i, message->data[i]);
	}

	// Request to send
	mcp_request_to_send(0);
}

void can_receive(message_t *msg) {
	// Only using buffer 0.
	//message_t message;

	// Id. RXBnSIDH og RXBnSIDL
	uint8_t id_low = mcp_read(MCP_RXB0SIDL)/0b100000;
	uint8_t id_high = mcp_read(MCP_RXB0SIDH);
	msg->id = id_high * 0b1000 + id_low;

	// Data length. RXBnDLC
	msg->length = mcp_read(MCP_RXB0DLC);

	// Data (optional). RXBnDM
	for (int i = 0; i < msg->length; i++) {
		msg->data[i] = mcp_read(MCP_RXB0D0 + i);
	}
	


}

void can_receive_n2(message_t *msg) {
	// Only using buffer 1.
	//message_t message;

	// Id. RXBnSIDH og RXBnSIDL
	uint8_t id_low = mcp_read(MCP_RXB1SIDL)/0b100000;
	uint8_t id_high = mcp_read(MCP_RXB1SIDH);
	msg->id = id_high * 0b1000 + id_low;

	// Data length. RXBnDLC
	msg->length = mcp_read(MCP_RXB1DLC);

	// Data (optional). RXBnDM
	for (int i = 0; i < msg->length; i++) {
		msg->data[i] = mcp_read(MCP_RXB1D0 + i);
	}
	


}


//sending joysticck via CAN
message_t send_joystick_can(joystick_dir_t dir, uint8_t can_id){
	
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
message_t can_send_string(char* c, uint8_t size, uint8_t can_id){
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



message_t send_clicked_btn(){
	message_t msg;
	msg.length = 4;
	msg.id = 30;
	msg.data[0] = btn_right();
	msg.data[1] = btn_left();
	msg.data[2] = slide_read_r();
	msg.data[3] = slide_read_l();
	
	
	return msg;
}





message_t coord_via_CAN(){
	message_t message;
	message.id = 20;
	coord_t xy;
	xy.x = (joy_read_x() + 93);
	xy.y = (joy_read_y() + 94);
	
	message.length = 2;
	
	message.data[0] = xy.x;
	
	message.data[1] = xy.y;
	
	return message;
	
}
