#include "Libraries\init_port.h"
#include "Libraries\library\motor_led\advance_one_timer\e_motors.h"
#include "Libraries\prox.h"
#include "Libraries\led.h"
#include "Libraries\epuck_ports.h"

void fear(void) {
	long i;
	e_init_motors();
	InitProx();

	e_set_speed_right(1);
	e_set_speed_left(1);

	SetBodyLed(1);
	LedClear();

	int left = 200;
	int right = 200;
	int runLoop = 1;
	int selectorPos = selector0 + 2*selector1 + 4*selector2 + 8*selector3;

	e_set_speed_right(right);
	e_set_speed_left(left);

	while (runLoop) {
		if (selectorPos == 1) {
			runLoop = 1;
		} else {
			runLoop = 0;
		}
		
		if (GetProx(0)>800 || GetProx(1)>800 || GetProx(6)>800 || GetProx(7)>800) {		//check 4 front sensors for anything within close proximity
			
			left=-900; 
			right=-900;			//move backwards rapidly

			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<160000;i++) {
				asm("nop");}
			
		
			left=-900;right=900;
			e_set_speed_right(right);	//do a 180 away from stimulation
			e_set_speed_left(left);

			for(i=0;i<600000;i++) {
				asm("nop");
			}
			
			
			left=200;
			right=200;		//return to original speed

			e_set_speed_right(right);
			e_set_speed_left(left); 
		}

		else if((GetProx(2)>800 || GetProx(3)>800 || GetProx(4)>800 || GetProx(5)>800)) {		//if back sensors detect something within close proximity
		
			left=800;
			right=800;		//move forward rapidly

			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<160000;i++) {
				asm("nop");
			}
			
			left=200;
			right=200;	//return to original speed

			e_set_speed_right(right);
			e_set_speed_left(left);
		}

		else {
			LedClear();
		}
		selectorPos = selector0 + 2*selector1 + 4*selector2 + 8*selector3;
	}

	e_set_speed_right(0);
	e_set_speed_left(0);
}
