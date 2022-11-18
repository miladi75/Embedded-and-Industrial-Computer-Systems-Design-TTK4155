/*
 * CAN.h
 *
 * Created: 27.10.2022 11:05:27
 *  Author: trymkd
 */ 


#ifndef CAN_H_
#define CAN_H_


#include <avr/io.h>
#include "JOYSTICK.h"

typedef struct Message {
	uint8_t id; 
	uint8_t length;  
	int8_t  data[8];    

} message_t;

//Coordinate type to store an integer pair
typedef struct {
	uint16_t x;
	uint16_t y;
}coord_t;





void CAN_init();


void CAN_receive_msg(message_t *msg);


void CAN_send_msg(message_t *message);

//send joystick via can
message_t CAN_send_joystick(joystick_dir_t dir, uint8_t can_id);

//send string message over can
message_t CAN_send_string(char* c, uint8_t size, uint8_t can_id);


message_t CAN_send_clicked_btn();


message_t CAN_send_coord();

void CAN_receive_n2(message_t *msg);




#endif /* CAN_H_ */