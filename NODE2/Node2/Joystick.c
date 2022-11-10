/*
 * Joystick.c
 *
 * Created: 30.10.2022 10:43:52
 *  Author: danie
 */ 




volatile int x_offset = 93;




//void joystick_dir_type(joystick_dir_t dir){
	//switch(dir);{
		//case UP:
			//printf("UP");
			//break
		//case DOWN:
			//printf("DOWN");
			//break
		//case RIGHT:
			//printf("RIGHT");
			//break
		//case LEFT:
			//printf("LEFT");
			//break
		//case NEUTRAL:
			//printf("NEUTRAL");
			//break
		//
	//}
	//
//}

int joy_read_x(int verdix) {
	
	int pos = ( verdix - x_offset) * 100 / 101;
	int offset = 101 - x_offset;
	if (pos > 0) {
		pos = (pos *  100) / (100 + offset);
		} else if (pos < 0) {
		pos = (pos * 100) / (100 - offset);
	}
	return pos;
}