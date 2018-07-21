#include "can_device.h"
#include "uart_device.h"
#include "keyboard.h"
#include "pid.h"
#include "sys.h"

#include "stdlib.h"
#include "can.h"
#include "cmsis_os.h"
#include "string.h"
#include "arm_task.h"






int16_t all_current[4]={0,0,0,0};
int arm_power;
int claw_power;
int trans_power;

void claw_param_init(void);
void trans_param_init(void);
void arm_param_init(void);

void arm_task(const void* argu){
	
	//initialize all motor&device
	arm_param_init();
	claw_param_init();
	trans_param_init();
	camera_servo_init();
	
   //¿ªÆô¿ØÖÆ¶Ë¿Ú
   
  while(1){
		arm_power=arm_power_calculate();
		claw_power=claw_power_calculate();
		trans_power=trans_power_calculate();
		all_current[0]=arm_power;
    all_current[1]=-arm_power;
    all_current[2]=claw_power;
		all_current[3]=trans_power;
    send_other_moto_current(all_current);
		camera_servo_ctrl(); 
  }  

}




