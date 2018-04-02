#include "p30f6014A.h"
#include "Libraries/init_port.h"
#include "Libraries/prox.h"
#include "Libraries/led.h"
#include "Libraries/epuck_ports.h"
#include "stdio.h"
#include "string.h"

#include "uart/e_uart_char.h"
#include "motor_led/e_init_port.h"
#include "motor_led/e_epuck_ports.h"
#include "motor_led/advance_one_timer/e_motors.h"
#include "motor_led/advance_one_timer/e_agenda.h"


#include "aggressive.h"
#include "fear.h"
#include "love.h"
#include "curious.h"
#include "bull.h"

int main(void) {
	int selector;
	e_init_port();
	e_init_motors();
	e_start_agendas_processing();
	while (1) {
		selector = selector0 + 2*selector1 + 4*selector2 + 8*selector3;
		int no = 0;
		
		switch (selector) {
			case 0:aggressive();break;
			case 1:fear();break;
			case 2:love();break;
			case 3:curious();break;
			case 4:maze();break;
			case 5:matador();break;
			case 6:no = 25;bull(no);break;
			case 7:no = 75;bull(no);break;
		}
	}
}
