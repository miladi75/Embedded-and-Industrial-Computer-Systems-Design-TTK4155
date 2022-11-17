/*
 * CAN.c
 *
 * Created: 11.11.2022 15:11:56
 *  Author: danie
 */ 
#include "sam.h"
#include "Joystick.h"
#include "printf-stdarg.h"
#include "can_controller.h"
#include "Motor.h"
#include "DAC.h"
#include "Solenoid.h"
#include "PWM.h"
#include "Timer.h"
#include "Game.h"

//
//volatile char e = 'e';
//uint16_t UP = 2;
//uint16_t DOWN = 3;
//uint16_t LEFT = 0;
//uint16_t RIGHT = 1;
//uint16_t NEUTRAL = 4;

CAN_MESSAGE *msg_arr[];
int jitter_count = 0;
int sum_jitter = 0;
int avg_val_jitter = 0;
int total_jitter_val = 0;



uint8_t CAN_use(void){

CAN_MESSAGE message;

can_receive(&message,0);


if (message.id == 30){
	//left btn == 2 & right btn = 4
	
	//printf("btnL: %d  btnR: %d   slidel:%d    slideR: %d\n",message.data[0],message.data[1], message.data[2], message.data[3]);
	
	score_count(message.data[0]);//btn left
	
	if (score_count(message.data[0]) <= 0)
	{
		return 10;
		printf("test score %d\n",score_count(message.data[0]));
	}
	
	Solenoid_pulse(message.data[1]); //btn right
	
	set_servo_pos(message.data[2]); //left slider
	
	
	
	
	
	//  test filter servo
	
	//do{
		//can_receive(msg_arr[jitter_count], 0);
		//jitter_count++;
		//sum_jitter += msg_arr[jitter_count]->data[2];
		//
	//}
	//while (message.id == 30 && jitter_count < 50);
//
//
	//
	//for(int i = 0; i< 50; i++){
		//avg_val_jitter = (int) sum_jitter/50;
	//}	
	//
	//
	//
	//if(msg_arr[jitter_count]->id == 30){
		//
		//Solenoid_pulse(message.data[0]);
		////score_count(message.data[1]);
		//set_servo_pos(avg_val_jitter);
		//printf("servo: %d\n",avg_val_jitter);
		//
		//
	}



if (message.id == 50) // message used in testing
{
	printf("melding");
	//printf("new message mb_id 2%c\n",e);
	printf("id %d\n",message.id);
	printf("length %d\n",message.data_length);
	printf("data %c\n",message.data[0]);
	printf("data %c\n",message.data[1]);
	printf("data %c\n",message.data[2]);
	printf("data %c\n",message.data[3]);
	printf("data %c\n",message.data[4]);
}
//
//if (message.id == 10) // joystick dir
//{
	//
	////printf("new message%c\n",e);
	////printf("id %d\n",message.id);
	////printf("length %d\n",message.data_length);
	////
	//if (message.data[0] == UP)
	//{
		//printf("up %c\n",e);
		//printf("%c\n",message.data[0]);
	//}
	//else if (message.data[0] == DOWN)
	//{
		//printf("down %c\n",e);
		//printf("%c\n",message.data[0]);
	//}
	//else if (message.data[0] == LEFT)
	//{
		//printf("left %c\n",e);
		//printf("%c\n",message.data[0]);
	//}
	//else if (message.data[0] == RIGHT)
	//{
		//printf("right %c\n",e);
		//printf("%c\n",message.data[0]);
	//}
	//else if (message.data[0] == NEUTRAL)
	//{
		//printf("neutral %c\n",e);
		//printf("%c\n",message.data[0]);
	//}
//}


if (message.id == 20)// joystick X and Y value
{
	//set_servo_pos(message.data[0]);
	motor_run_joystick(message.data[0]);
	//motor_joystick_PID(message.data[0]);
	//joy_read_x(message.data[0]);
	//printf("x:%d ------------->xcan:%d\n", joy_read_x(message.data[0]),message.data[0]);
	
	//CAN_MESSAGE msg;
	//msg.id = message.id;
	//msg.data_length = message.data_length;
	//msg.data[0] = message.data[0];
	//
	//return msg;
	
	
	
}
//********************************************************************************************************************
//if (message.id == 30)//button
//{	
//
	////int arr_serv_values[50];
	////int counter_serv = 0;
	////Solenoid_pulse(message.data[0]);
	////score_count(message.data[1]);
	////int temp_serv_val = message.data[3]
	////printf("servo: %d\n",message.data[2]);
	////
	////do 
	////{
		////arr_serv_values[counter_serv] = temp_serv_val;
		////counter_serv += 1;
		//////set_servo_pos();
	////} while (counter_serv<50);
	//
	////printf("butten data: %d\n",message.data[0]);
	//
	//
//}

//********************************************************************************************************************
//if (message.id == 40)
//{
//}


}
	
	
