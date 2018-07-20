#include "can_device.h"
#include "uart_device.h"
#include "keyboard.h"
#include "pid.h"
#include "sys.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"





int arm_power;
int claw_power;
short block_number;


void arm_power_calculate(){
  int target;
  if(rc.kb.bit.Q) {arm_power=5000; target=moto_arm.total_angle;}
  if(rc.kb.bit.E) {arm_power=-5000; target=moto_arm.total_angle;}
  else{
    arm_power=pid_calc(&pid_arm_moto,moto_arm.total_angle,target);
  }
}


void claw_power_calculate(int current){
  int target;
  if(rc.mouse.l) {claw_power=5000; target=moto_claw.total_angle;}
  if(rc.mouse.r) {claw_power=-5000; target=moto_claw.total_angle;}
  else{
    arm_power=pid_calc(&pid_arm_moto,moto_claw.total_angle,target);
  }
}


void block_count(){

}



