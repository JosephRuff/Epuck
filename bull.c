#include "Libraries/init_port.h"
#include "Libraries/prox.h"
#include "Libraries/led.h"
#include "Libraries/epuck_ports.h"
#include "Libraries/library/motor_led/e_init_port.h"
#include "Libraries/library/motor_led/e_epuck_ports.h"
#include "Libraries/library/motor_led/advance_one_timer/e_motors.h"
#include "Libraries/library/motor_led/advance_one_timer/e_agenda.h"
#include "Libraries/library/uart/e_uart_char.h"
#include "Libraries/library/camera/fast_2_timer/e_poxxxx.h"
#include "Libraries/library/motor_led/advance_one_timer/e_led.h"

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

//#include "findRed.h"

char fbwbuffer[160];
int numbuffer[80];
long isRedVisable;


//custom cam picture load
void getImage(){
	e_poxxxx_launch_capture((char *)fbwbuffer);
    while(!e_poxxxx_is_img_ready()){};
}
// Image processing removes useless information
void Image(int no){	
	long i;
	int green, red, vis;
	for(i=0; i<80; i++){
		//RGB turned into an integer value for comparison
		red = (fbwbuffer[2*i] & 0xF8);
		green = (((fbwbuffer[2*i] & 0x07) << 5) | ((fbwbuffer[2*i+1] & 0xE0) >> 3));
		//blue = ((fbwbuffer[2*i+1] & 0x1F) << 3); we don't need blue for looking for red.
		if(red > green + no){ // green will be less then red when red is strong.
			numbuffer[i] = 1;
			vis++;
		}else{
			numbuffer[i] = 0;
		}
		//If red is visable then isRedVisable turns to true
		if(vis>0){
			isRedVisable = 1;
		}else{
			isRedVisable = 0;
		}
	}	
}

//Decide which way to turn.
int turnDirection(){
	int sumL = 0;
	int sumR = 0;
	int i;
	for(i=0;i<40;i++){
		sumL += numbuffer[i];
		sumR += numbuffer[i+40];
	}
	if(sumL<sumR){ 
		return 1;
	}else{
		return 0;
	}
}
//Function to deal with turning.
void turn(void) {
	if(turnDirection()){
		e_set_speed_left (300);
		e_set_speed_right(-300);
	}else{
		e_set_speed_left (-300);
		e_set_speed_right(300);
	}
}
void charge(void) {
	e_set_speed_left (800);
	e_set_speed_right(800);
	long i;
	for(i=0;i<3000000;i++) {
		asm("nop");
	}
	
}
//Main function of follower
void bull(int no){
	//basic set up for camera
	e_init_port();
	e_init_motors();
	InitProx();
	e_poxxxx_init_cam();
	e_poxxxx_config_cam(0,(ARRAY_HEIGHT - 4)/2,640,4,8,4,RGB_565_MODE);
	e_poxxxx_write_cam_registers(); 

	e_start_agendas_processing();
	int centreValue;
	int runLoop = 1;	//breaks loop if selector position is changed
	int selectorPos = selector0 + 2*selector1 + 4*selector2 + 8*selector3;


	while(runLoop){
		if (selectorPos == 6) {
			runLoop = 1;
		} else {
			runLoop = 0;
		}
		getImage();
		Image(no);
		LedClear();

		//Take a section of the center, this means if there is an error with one it won't effect it as a whole.
		centreValue = numbuffer[38] + numbuffer[39] + numbuffer[40] + numbuffer[41] + numbuffer[42] + numbuffer[43]; // removes stray 
		if(centreValue > 3){ //If red is in the middle then stay still			
			e_destroy_agenda(turn);
			e_set_speed_left (0);
			e_set_speed_right(0);
			charge();
		}else if(isRedVisable){//If red isn't in the center but is visable then picks a direction to turn to face it
			e_activate_agenda(turn, 650);
		}else{// if red isn't visible and no true values it will turn left
			e_destroy_agenda(turn);
			e_set_speed_left (0);
			e_set_speed_right(0);
		}
		selectorPos = selector0 + 2*selector1 + 4*selector2 + 8*selector3;
	}
	LedClear();
	e_set_speed_right(0);
	e_set_speed_left (0);
}
