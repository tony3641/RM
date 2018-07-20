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

void arm_task(const void* argu){
  arm_param_init();
  
  while(1){
    arm_power_calculate();
    claw_power_calculate();
  }  

}

void arm_param_init(void)
{
  pid_init(&pid_arm_moto, 5000, 50, 12.0f, 0.0f, 0.0f);
}


void claw_param_init(void)
{
  pid_init(&pid_arm_moto, 5000, 50, 12.0f, 0.0f, 0.0f);
}

