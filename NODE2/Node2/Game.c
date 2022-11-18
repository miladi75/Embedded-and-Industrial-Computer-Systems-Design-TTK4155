/*
 * Game.c
 *
 * Created: 03.11.2022 14:57:54
 *  Author: danie
 */ 
#include "ADC.h"
#include "can_controller.h"


volatile int counter = 0;
volatile int lives = 3;
volatile int pause = 1;
	

uint8_t Game_score_count(int button){
	
	//reading IR level form ADC
	int IR_level = ADC_read();
	
	//printf("ir %d pause\n",IR_level);
	
	//printf("ir_level: %d\n",IR_level);
	if (IR_level == 0 && pause == 0)
	{ 
		
		//
		counter = counter + 1;
		delay_us(20);
		pause = 1;
		
		printf("counter %d   pause %d\n",counter,pause);
		
// 		CAN_MESSAGE msg;
// 		msg.id = 5;
// 		msg.data_length = 4;
// 		msg.data[0] = 's';
// 		msg.data[1] = 't';
// 		msg.data[2] = 't';
// 		msg.data[3] = 't';
// 		
// 		
// 		
// 		can_send(&msg,0);
		
		//disabling motor until reset from player
		Motor_disable();
		
		//printf("msg data %c\n",msg.data[0]);
		return 1;
		
	}
	
	if (button == 2)
	{
		pause = 0;
		
		//CAN_MESSAGE msg;
		//msg.id = 5;
		//msg.data_length = 1;
		//msg.data[0] = counter;
		//
		//
		//
		//can_send(&msg,0);
// 		printf("msg data %d\n",msg.data[0]);

		// enable motor from player input
		Motor_enable();
	}
	
	if (counter == lives)
	{
		printf("Game over");
		
		
		
		
// 		CAN_MESSAGE msg_1;
// 		msg_1.id = 2;
// 		msg_1.data_length = 4;
// 		msg_1.data[0] = 't';
// 		msg_1.data[1] = 't';
// 		msg_1.data[2] = 't';
// 		msg_1.data[3] = 't';
		
// 		
// 		return msg;
		
		
		//can_send(&msg_1,0);
		//printf("------------->msg_1 %c\n",msg_1.data[0]);
		
		counter = 0;
		Motor_disable();
		
		return 0;
		
	}

return 2;

}

uint8_t game_state(){ //unused 
	
	return 0;
}