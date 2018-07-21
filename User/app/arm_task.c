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
void arm_task(const void* argu){
  arm_param_init();
  
  while(1){
    arm_power=arm_power_calculate();
    claw_power=claw_power_calculate();
    all_current[0]=arm_power;
    all_current[1]=arm_power;
    all_current[2]=claw_power;
    send_other_moto_current(all_current);
  }  

}

void arm_param_init(void)
{
  pid_init(&pid_arm_moto, 5000, 50, 2.0f, 0.0f, 50.0f);
}


void claw_param_init(void)
{
  pid_init(&pid_arm_moto, 5000, 50, 2.0f, 0.0f, 50.0f);
}
