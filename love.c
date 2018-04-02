#include "Libraries\init_port.h"
#include "Libraries\library\motor_led\advance_one_timer\e_motors.h"
#include "Libraries\prox.h"
#include "Libraries\led.h"
#include "Libraries\epuck_ports.h"

void love(void) {
	long i = 0;	
				
	int left = 0;					//left wheel speed
	int right = 0;					//right wheel speed
	long waitTime = 25000;		//how many steps to wait between each iteration of main loop
	int runLoop = 1;
	int selectorPos = selector0 + 2*selector1 + 4*selector2 + 8*selector3;
	

	e_init_motors();
	InitProx();
	LedClear();
	
	SetBodyLed(1); 
	e_set_steps_right(1);
	e_set_steps_left(1);	//body LED turned on and start moving forward
	e_set_speed_right(100);
	e_set_speed_left(100);
	
	while (runLoop) {
		if (selectorPos == 2) {
			runLoop = 1;
		} else {
			runLoop = 0;
		}
		left = left/1.1;
		right = right/1.1;
		left+=40;
		right+=40;
		
		/*adjusts wheel speed if proximity sensors detect something close*/
		for (i=0;i<7;i++) {
			if (GetProx(i)>=500) {	
				switch (i) {
					case 0:left+=300;right+=100;break;
					case 1:left+=100;right-=100;break;
					case 2:left+=300;right-=400;break;
					case 3:left+=400;right-=300;break;
					case 4:left+=400;right-=300;break;
					case 5:left-=400;right+=300;break;
					case 6:left-=100;right+=100;break;
					case 7:left+=300;right+=100;break;
				}
			}
		}
		
		//get mean average of both front sensors
		int frontProx = (GetProx(0) + GetProx(7)) / 2;

		
		if (frontProx < 1) {
			frontProx = 1;
		}


		if (GetProx(0)>1000 || GetProx(1)>1000) {
			if (GetProx(0)>GetProx(7)) {
				left  = 150;
				right = -150;
			}
			else if (GetProx(7)>1800) {
				left  = -150;
				right = 150;
			}
			for(i=0;i<50000;i++) {
				asm("nop");
			}
		}
		
		
		
		//maximum speed limited to 750

		if (left > 750) { left = 750; }
		if (right > 750) { right = 750; }
		if (left < -750) { left = -750; }
		if (right < -750) { right = -750; }
		
		for(i=0;i<waitTime;i++) {
			asm("nop");
		}

		e_set_speed_left(left);
		e_set_speed_right(right);
		selectorPos = selector0 + 2*selector1 + 4*selector2 + 8*selector3;
	}
	e_set_speed_right(0);
	e_set_speed_left(0);
}
