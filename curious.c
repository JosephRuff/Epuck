#include "Libraries\init_port.h"
#include "Libraries\library\motor_led\advance_one_timer\e_motors.h"
#include "Libraries\prox.h"
#include "Libraries\led.h"
#include "Libraries\epuck_ports.h"

void curious(void) {
    long i;
    int ft = 0;
    long ran = 0;
    long rantime = 0;
    e_init_motors();
    InitProx();
    LedClear();
    SetBodyLed(1);
    e_set_steps_right(1);
    e_set_steps_left(1);
    int left = 0;
    int right = 0;
    int waitlonger = 0;
    int curious = 0;
	int runLoop = 1;
	int selectorPos = selector0 + 2*selector1 + 4*selector2 + 8*selector3;

    while(runLoop){
		if (selectorPos == 3) {
			runLoop = 1;
		} else {
			runLoop = 0;
		}
        while (curious == 0 && runLoop) {//finds object and turns toward it
	        if (selectorPos == 3) {
				runLoop = 1;
			} else {
				runLoop = 0;
			}
            int j;
            for(i=0;i<100000;i++) {asm("nop");}

            left+=38;
            right+=38;
            left = left * 0.9;
            right = right * 0.9;


            for (j=0;j<7;j++) {		//adjusts wheel speeds based on sensor readings
                if (GetProx(j)>=500) {    
                    switch (j) {
                        case 0:left+=150;right+=100;SetLed(0,1);break;
						case 1:left+=100;right-=100;SetLed(1,1);break;
						case 2:left+=300;right-=400;SetLed(2,1);break;						
						case 3:left+=400;right-=300;SetLed(3,1);break;
						case 4:left+=400;right-=300;SetLed(5,1);break;
						case 5:left-=400;right+=300;SetLed(6,1);break;
						case 6:left-=100;right+=100;SetLed(7,1);break;
						case 7:left+=150;right+=100;SetLed(0,1);break;
                    }
                }
                else {
					switch (j) {
						case 0:
						case 1: 
						case 2: 
						case 3:SetLed(j,0);break;
						case 4:SetLed(5,0);break;
						case 5:SetLed(6,0);break;
						case 6:SetLed(7,0);break;
						case 7:SetLed(0,0);break;
					}
				}
            }

            if (GetProx(3)>800 || GetProx(4)>800) {//if something is behinds robot, turn around
                left = 700;
                right = -800;
                for(i=0;i<100000;i++) {asm("nop");}
                 
            }
            
            if (GetProx(0)>500 && GetProx(7)>500)  { //if something is in front of robot go to curious == 2
               curious = 1;
               ran=1000;
                left =0;
                right =0;
            }    
            
            //set a max speed of 900
			if (left > 1000) {
				left = 1000;
			}
			if (right > 1000) {
				right = 1000;
			}
			if (left < -1000) {
				left = -1000;
			}
			if (right < -1000) {
				right = -1000;
			}
            
            
            /*wait*/for(i=0;i<40000;i++) {asm("nop");}
            e_set_speed_right(right);
            e_set_speed_left(left);

            selectorPos = selector0 + 2*selector1 + 4*selector2 + 8*selector3;
        }

    while(curious==1 && runLoop){	//orbits around an object until it loses interest
			if (selectorPos == 3) {
				runLoop = 1;
			} else {
				runLoop = 0;
			}


            if(GetProx(2) < 400){	//if too far from wall, turn into the wall
				//turn right, towards wall
                left = 300;
                right = 50;
                e_set_speed_right(right);
                e_set_speed_left(left);
                /*wait*/for(i=0;i<40000;i++) {asm("nop");}
                ran--;
            }

            while ( GetProx(0) >= 500 || GetProx(7) >= 600 || GetProx(1) >= 350){	//if something in front of robot turn left
                left = -300;
                right = 300;
                e_set_speed_right(right);
                e_set_speed_left(left);
                /*wait*/for(i=0;i<40000;i++) {asm("nop");}
                ran--;
            }

            if (GetProx(2) > 600){	//if too close to wall, turn away from wall
				//turn left
                left = 250;
                right = 300;
                e_set_speed_right(right);
                e_set_speed_left(left);        
                 /*wait*/for(i=0;i<40000;i++) {asm("nop");}    
                             
            }


			//if space infront go forwards
            if ( GetProx(2) >= 400 && GetProx(0) < 500 && GetProx(7) < 600 && GetProx(1) < 350 && GetProx(6) <= 800 && GetProx(2) <= 600){
                left =350;
                right = 350;
                e_set_speed_right(right);
                e_set_speed_left(left);
                /*wait*/for(i=0;i<40000;i++) {asm("nop");}
            }

            if (GetProx(5) > 600 || GetProx(6) > 600 ){//if something to the left turn away
                left = 300;
                right = 250;
                e_set_speed_right(right);
                e_set_speed_left(left);        
            	/*wait*/for(i=0;i<40000;i++) {asm("nop");}    
            }
            ran--;
            if(ran<0){//if time is up, go to curious == 2
				curious=2;
			}
			selectorPos = selector0 + 2*selector1 + 4*selector2 + 8*selector3;
        }

	if(curious==2){		//when interest is lost, turn around and search for something else
	    int k;
	    for (k=0;k<7;k++) {//turn all leds on
	        SetLed(k,1);
	    }
	    ran=0;
	    curious=0; //go to curious == 0 (after if statement is complete)
	    left=-400;	//spin around
	    right=400;
	    e_set_speed_right(right);
	    e_set_speed_left(left);    
	    for(i=0;i<480000;i++) {asm("nop");}
	    for (k=0;k<7;k++) {//turn all leds off
	        SetLed(k,0);
	    }
	    left=300;//go forwards
	    right=300;
	    e_set_speed_right(right);
	    e_set_speed_left(left);    
	    for(i=0;i<240000;i++) {asm("nop");}
        }
		selectorPos = selector0 + 2*selector1 + 4*selector2 + 8*selector3;
    }
	e_set_speed_right(0);
	e_set_speed_left(0);
}
