#include "Libraries\init_port.h"
#include "Libraries\library\motor_led\advance_one_timer\e_motors.h"
#include "Libraries\prox.h"
#include "Libraries\led.h"
#include "Libraries\epuck_ports.h"

void maze(void)
{
	long i = 0;			//loop int mainly for waiting
	int left = 0;		//left wheel speed
	int right = 0;		//right wheel soeed
	int behaviourMode = 0;
	//setup
	e_init_motors();
	InitProx();
	LedClear();
	
	//swi
	SetBodyLed(1);
	e_set_steps_right(1);
	e_set_steps_left(1);
	e_set_speed_right(100);
	e_set_speed_left(100);
	
	while (1) {
		//used to increase speed up to the maximum
		left+=100;
		right+=100;


		//adjust wheel speed to turn towards the light
		for (i=0;i<7;i++) {
			if (GetAmbientLight(i)<4000) {	
				switch (i) {
					//left side sensors
					case 0:left+=150;right+=100;break;
					case 1:left+=100;right-=100;break;
					case 2:left+=300;right-=400;break;
					//back sensors
					case 3:left+=400;right-=300;break;
					case 4:left+=400;right-=300;break;
					//right side sensors
					case 5:left-=400;right+=300;break;
					case 6:left-=100;right+=100;break;
					case 7:left+=150;right+=100;break;
				}
				SetLed(i,1);
			}
			else SetLed(i,0);
		}


		//enter behaviourMode = 1, if something is in fornt of robot
		if (GetProx(0) >= 550 || GetProx(7) >= 550 || GetProx(1) >= 550 || GetProx(6) >= 550){	
				
				left= -300;
				right= 300;
				e_set_speed_right(right);
				e_set_speed_left(left);
				
				behaviourMode = 1;
				
				
			//while in behaviourMode = 1 circle object
			while(behaviourMode==1){//move around wall
				if (GetAmbientLight(0)<4000||GetAmbientLight(1)<4000||GetAmbientLight(2)<4000||GetAmbientLight(3)<4000||GetAmbientLight(4)<4000||GetAmbientLight(5)<4000||GetAmbientLight(6)<4000||GetAmbientLight(7)<4000) {
					behaviourMode = 0;
				}
				//too far from wall
				if(GetProx(5) < 400){
					left = 300;
	                right = 50;
	                e_set_speed_right(right);
	                e_set_speed_left(left);
					
	                for(i=0;i<40000;i++) {
						asm("nop");
					}
				}
				//wall in front and on the left
				while (GetProx(7) >= 500 || GetProx(0) >= 600 || GetProx(6) >= 350){
					//sharp turn right
					left = 300; 					right = -300; 
					e_set_speed_right(right); 
					e_set_speed_left(left); 
					for(i=0;i<40000;i++) {asm("nop");} //wait
				} 
				//too close to wall
				if (GetProx(5) > 600){ 
					//turn left
					left = 0; 
					right = 300; 
					e_set_speed_right(right); 
					e_set_speed_left(left); 	
					for(i=0;i<40000;i++) {asm("nop");} 	//wait
				} 	
				//is there enough space for it go just go forwards?
				if ( GetProx(5) >= 400 && GetProx(7) < 500 && GetProx(0) < 600 && GetProx(6) < 350 && GetProx(1) <= 800 && GetProx(5) <= 600){ 
					//go forwards
					
					left = 300; 
					right = 300; 
					
					e_set_speed_right(right); 
					e_set_speed_left(left); 
					for(i=0;i<80000;i++) {asm("nop");} //wait 
				} 
				//wall to the left
				if (GetProx(5) > 600 || GetProx(6) > 600 ){ 
					left = 300; 
					right = 0; 
	
					e_set_speed_right(right); 
					e_set_speed_left(left); 
					for(i=0;i<40000;i++) {asm("nop");} //wait 
				}
				
			}
		}

		//set a max speed if it goes over
		if (left>800) {
			left = 800;
		}
		if (right>800) {
			right = 800;
		}
		if (left<-800) {
			left = -800;
		}
		if (right<-800) {
			right = -800;
		}
		
		//apply the changes to the speed
		for(i=0;i<40000;i++) {asm("nop");} 
		e_set_speed_right(right);
		e_set_speed_left(left);
		
		//when strong source of light is detected, goal is reached
		while (GetAmbientLight(0)<2000 || GetAmbientLight(1)<2000 || GetAmbientLight(2)<2000 || GetAmbientLight(3)<2000 || GetAmbientLight(4)<2000 || GetAmbientLight(5)<2000 || GetAmbientLight(6)<2000 || GetAmbientLight(7)<2000){
			//stop
			e_set_speed_right(0);
			e_set_speed_left(0);
			//turn on all leds
			for(i=0;i<8;i++){
				SetLed(i,1);
			}
			
			while (1);
		}
	}
}
