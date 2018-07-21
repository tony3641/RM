#include "can_device.h"
#include "uart_device.h"
#include "keyboard.h"
#include "pid.h"
#include "sys.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "arm.h"

short block_num;
int target_claw;
int target_arm;
short block_bool;
short arm_position_bool;
short sensor_bool;

short block_num_test(void){
	if(block_num<3&&block_num>0) return 1;
	else {return 0;}
}//no more than 3 and no less than 0






int arm_power_calculate(void){
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


int claw_power_calculate(void){
  //right click->close
  //left click->open
  int16_t claw_power;
  /*if(rc.kb.mouse.l){ //read mouse left 'n' right click button.
    claw_power=5000; 
    target_claw=moto_claw.total_angle;
}*/
  /*else{if(rc.kb.mouse.r){ //
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
	int degree=rc.mouse.y;//read mouse up 'n' down.
	if(abs(degree)<100) degree=0;
	degree+=1500;
	set_pwm_param(PWM_IO1,degree);
}


void camera_servo_init(void){
	set_pwm_group_param(PWM_GROUP1,20000);
  start_pwm_output(PWM_IO1);
}


void trans_param_init(void){
	pid_init(&pid_trans_moto, 5000, 50, 2.0f, 0.0f, 50.0f);
}

void arm_param_init(void)
{
  pid_init(&pid_arm_moto, 5000, 50, 2.0f, 0.0f, 50.0f);
}


void claw_param_init(void)
{
  pid_init(&pid_arm_moto, 5000, 50, 2.0f, 0.0f, 50.0f);
}

int trans_power_calculate(void){
	block_bool=block_num_test();
	arm_position_bool=arm_position_test();
	sensor_bool=sensor_test();
	return 1;
}

short arm_position_test(void){
	short result=0;
	return result;
}


short sensor_test(void){
	short result;
	return result;
}



