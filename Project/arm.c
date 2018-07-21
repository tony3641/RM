#include "can_device.h"
#include "uart_device.h"
#include "keyboard.h"
#include "pid.h"
#include "sys.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"

short block_number;
int target_claw;
int target_arm;

int arm_power_calculate(){
  //Q->Arm up
  //E->Arm down
  int16_t arm_power;
  /*if(rc.kb.bit.Q){
    arm_power=5000; 
    target_arm=moto_arm.total_angle;
}*/
  /*else{if(rc.kb.bit.E){
    arm_power=-5000; 
    target=moto_arm.total_angle;}*/
  if(rc.sw1==2){
    arm_power=200; 
    target_arm=moto_arm.total_angle;
  }
  else{
    if(rc.sw1==1){
      arm_power=-200; 
      target_arm=moto_arm.total_angle;
    }
    else{
      arm_power=pid_calc(&pid_arm_moto,moto_arm.total_angle,target_arm);
    }
  }
  return arm_power;
}


int claw_power_calculate(int current){
  //right click->close
  //left click->open
  int16_t claw_power;
  /*if(rc.kb.bit.Q){
    claw_power=5000; 
    target_claw=moto_claw.total_angle;
}*/
  /*else{if(rc.kb.bit.E){
    claw_power=-5000; 
    target=moto_claw.total_angle;}*/
  if(rc.sw2==2){
  claw_power=500; 
  target_claw=moto_claw.total_angle;
  }
  else{
    if(rc.sw2==1) {claw_power=-500; target_claw=moto_claw.total_angle;}
      else{
    claw_power=pid_calc(&pid_arm_moto,moto_claw.total_angle,target_claw);
      }
  }
  return claw_power;
}



void camera_servo_ctrl(){
	int degree=rc.mouse.x;
	if(abs(degree)<100) degree=0;
	degree+=1500;
	set_pwm_param(PWM_IO1,degree);
}


void camera_servo_init(void){
	set_pwm_group_param(PWM_GROUP1,20000);
  start_pwm_output(PWM_IO1);
}


