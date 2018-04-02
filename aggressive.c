#include "Libraries\init_port.h"
#include "Libraries\library\motor_led\advance_one_timer\e_motors.h"
#include "Libraries\prox.h"
#include "Libraries\led.h"
#include "Libraries\epuck_ports.h"

void aggressive(void) {
	long i = 0;			//loop int mainly for waiting
	int waitlonger = 0;	//if set to 1, waits longer inbetween each loop

	int left = 0;		//left wheel speed
	int right = 0;		//right wheel speed
	
	int runLoop = 1;	//breaks loop if selector position is changed
	int selectorPos = selector0 + 2*selector1 + 4*selector2 + 8*selector3;

	e_init_port();
	e_init_motors();
	
	InitProx();
	LedClear();
	
	e_set_speed_right(150);
	e_set_speed_left(150);

	e_set_steps_right(1);
	e_set_steps_left(1);
	
	while (runLoop) {
		if (selectorPos == 0) {
			runLoop = 1;
		} else {
			runLoop = 0;
		}
		//used to slowly increase speed with a maximum

		left = left/1.1;
		right = right/1.1;

		left+=40;
		right+=40;

		
	
		for (i=0;i<7;i++) {
			if (GetAmbientLight(i)<4000 || GetProx(i)>=550) {	
				switch (i) {
							//lights up led if sufficient stimulus detected
					case 0:left+=150;right+=100;SetLed(0,1);break;
					case 1:left+=100;right-=100;SetLed(1,1);break;
					case 2:left+=300;right-=400;SetLed(2,1);break;						
					case 3:left+=400;right-=300;SetLed(3,1);break;
					case 4:left+=400;right-=300;SetLed(5,1);break;
					case 5:left-=400;right+=300;SetLed(6,1);break;
					case 6:left-=100;right+=100;SetLed(7,1);break;
					case 7:left+=150;right+=100;SetLed(0,1);break;
							//will adjust wheel speeds depending on location of stimulus
				}
			}
			else {
				switch (i) {
					case 0:
					case 1: 
					case 2: 
					case 3:SetLed(i,0);break;
					case 4:SetLed(5,0);break;
					case 5:SetLed(6,0);break;
					case 6:SetLed(7,0);break;
					case 7:SetLed(0,0);break;
				}
			}
		}

		
		if (GetProx(0)>800 || GetProx(7)>800) {
			for (i=0;i<8;i++) {
				SetLed(i,1);	//turns on LEDs
			}
			SetFrontLed(1);
			
			e_set_speed_right(1000);
			e_set_speed_left(1000); 	//push against stimulus for a short while

			for(i=0;i<800000;i++) {
				asm("nop");
			}
			
			LedClear();
			SetFrontLed(0);		//switch LEDs back off when stimulus no longer detected

			//reverses a little
			left = -800;
			right = -800;
			waitlonger = 1;
		}
		
		//set a max speed of 900
		if (left > 900) {
			left = 900;
		}
		if (right > 900) {
			right = 900;
		}
		if (left < -900) {
			left = -900;
		}
		if (right < -900) {
			right = -900;
		}
		
		for(i=0;i<40000;i++) {
			asm("nop");
		}				 //wait, and apply the speed change
		
		e_set_speed_right(right);
		e_set_speed_left(left);
		
		if (waitlonger == 1) {
			for(i=0;i<100000;i++) {
				asm("nop");
			} 
			waitlonger = 0;
		}
		selectorPos = selector0 + 2*selector1 + 4*selector2 + 8*selector3;
	}
	LedClear();
	e_set_speed_right(0);
	e_set_speed_left(0);
}
