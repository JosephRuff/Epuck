#include "Libraries\init_port.h"
#include "Libraries\library\motor_led\advance_one_timer\e_motors.h"
#include "Libraries\prox.h"
#include "Libraries\led.h"
#include "Libraries\epuck_ports.h"

void matador(void) {
	long i;
	e_init_motors();
	InitProx();

	e_set_speed_right(1);
	e_set_speed_left(1);

	SetFrontLed(1);
	for(i=0;i<8;i++){
		SetLed(i,1);
	}

	int left = 0;
	int right = 0;
	int runLoop = 1;
	int selectorPos = selector0 + 2*selector1 + 4*selector2 + 8*selector3;

	e_set_speed_right(right);
	e_set_speed_left(left);

	while (runLoop) {
		if (selectorPos == 5) {
			runLoop = 1;
		} else {
			runLoop = 0;
		}
		
		if (GetProx(0)>800) {

			SetFrontLed(0);
			for(i=0;i<8;i++){
				SetLed(i,0);
			}
			
			left=-1000; 
			right=-1000;	

			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<160000;i++) {
				asm("nop");}
			
		
			left=-1000;right=-500;
			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<1200000;i++) {
				asm("nop");
			}

			
			left=-1000;right=-1000;
			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<120000;i++) {
				asm("nop");
			}
			
			
			left=0;
			right=0;

			e_set_speed_right(right);
			e_set_speed_left(left); 

			SetFrontLed(1);
			for(i=0;i<8;i++){
				SetLed(i,1);
			}
		}

		else if(GetProx(7)>800) {

			SetFrontLed(0);
			for(i=0;i<8;i++){
				SetLed(i,0);
			}
			
			left=-1000; 
			right=-1000;	

			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<160000;i++) {
				asm("nop");}
			
		
			left=-500;right=-1000;
			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<1200000;i++) {
				asm("nop");
			}

			
			left=-1000;right=-1000;
			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<120000;i++) {
				asm("nop");
			}
			
			
			left=0;
			right=0;

			e_set_speed_right(right);
			e_set_speed_left(left); 

			SetFrontLed(1);
			for(i=0;i<8;i++){
				SetLed(i,1);
			}
		}

		else if (GetProx(1)>800) {

			SetFrontLed(0);
			for(i=0;i<8;i++){
				SetLed(i,0);
			}
			
			left=-1000; 
			right=-1000;	

			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<160000;i++) {
				asm("nop");}
			
		
			left=-1000;right=-500;
			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<800000;i++) {
				asm("nop");
			}

			
			left=-1000;right=-1000;
			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<160000;i++) {
				asm("nop");
			}
			
			
			left=0;
			right=0;

			e_set_speed_right(right);
			e_set_speed_left(left); 

			SetFrontLed(1);
			for(i=0;i<8;i++){
				SetLed(i,1);
			}
		}

		else if(GetProx(6)>800) {

			SetFrontLed(0);
			for(i=0;i<8;i++){
				SetLed(i,0);
			}
			
			left=-1000; 
			right=-1000;	

			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<160000;i++) {
				asm("nop");}
			
		
			left=-500;right=-1000;
			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<800000;i++) {
				asm("nop");
			}

			
			left=-1000;right=-1000;
			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<160000;i++) {
				asm("nop");
			}
			
			
			left=0;
			right=0;


			e_set_speed_right(right);
			e_set_speed_left(left); 

			SetFrontLed(1);
			for(i=0;i<8;i++){
				SetLed(i,1);
			}
		}

		else if(GetProx(2)>800) {

			SetFrontLed(0);
			for(i=0;i<8;i++){
				SetLed(i,0);
			}
			
			if(((GetProx(0)+GetProx(1)+GetProx(6)+GetProx(7))/4)>((GetProx(3)+GetProx(4))/2)) {
				left=-1000; 
				right=-1000;
			}
			else {
				left=1000; 
				right=1000;
			}

			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<1000000;i++) {
				asm("nop");}
			
			left=0;
			right=0;


			e_set_speed_right(right);
			e_set_speed_left(left); 

			SetFrontLed(1);
			for(i=0;i<8;i++){
				SetLed(i,1);
			}
		}

		else if(GetProx(5)>800) {

			SetFrontLed(0);
			for(i=0;i<8;i++){
				SetLed(i,0);
			}
			
			if(((GetProx(0)+GetProx(1)+GetProx(6)+GetProx(7))/4)>((GetProx(3)+GetProx(4))/2)) {
				left=-1000; 
				right=-1000;
			}
			else {
				left=1000; 
				right=1000;
			}	

			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<1000000;i++) {
				asm("nop");}
			
			left=0;
			right=0;


			e_set_speed_right(right);
			e_set_speed_left(left); 

			SetFrontLed(1);
			for(i=0;i<8;i++){
				SetLed(i,1);
			}

		}

		else if (GetProx(3)>800) {

			SetFrontLed(0);
			for(i=0;i<8;i++){
				SetLed(i,0);
			}
			
			left=1000; 
			right=1000;	

			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<160000;i++) {
				asm("nop");}
			
		
			left=1000;right=500;
			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<1200000;i++) {
				asm("nop");
			}

			
			left=1000;right=1000;
			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<120000;i++) {
				asm("nop");
			}
			
			
			left=0;
			right=0;

			e_set_speed_right(right);
			e_set_speed_left(left); 

			SetFrontLed(1);
			for(i=0;i<8;i++){
				SetLed(i,1);
			}
		}

		else if(GetProx(4)>800) {

			SetFrontLed(0);
			for(i=0;i<8;i++){
				SetLed(i,0);
			}
			
			left=1000; 
			right=1000;	

			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<160000;i++) {
				asm("nop");}
			
		
			left=500;right=1000;
			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<1200000;i++) {
				asm("nop");
			}

			
			left=1000;right=1000;
			e_set_speed_right(right);
			e_set_speed_left(left);

			for(i=0;i<120000;i++) {
				asm("nop");
			}
			
			
			left=0;
			right=0;

			e_set_speed_right(right);
			e_set_speed_left(left); 

			SetFrontLed(1);
			for(i=0;i<8;i++){
				SetLed(i,1);
			}
		}

		else {
			
		}
		selectorPos = selector0 + 2*selector1 + 4*selector2 + 8*selector3;
	}

	e_set_speed_right(0);
	e_set_speed_left(0);
}