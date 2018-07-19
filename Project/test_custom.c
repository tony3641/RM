#include "execute_task.h"
#include "can_device.h"
#include "uart_device.h"
#include "pid.h"
#include "sys.h"
#include "rm_hal_lib.h"

#define NIXIE_NUM_0 0xFC
#define NIXIE_NUM_1 0x60
#define NIXIE_NUM_2 0xDA
#define NIXIE_NUM_3 0xF2
#define NIXIE_NUM_4 0x66
#define NIXIE_NUM_5 0xB6
#define NIXIE_NUM_6 0xBE
#define NIXIE_NUM_7 0xE0
#define NIXIE_NUM_8 0xFE
#define NIXIE_NUM_9 0xE6
#define NIXIE_NUM_P 0x01

int16_t test_moto_speed = 0;
int16_t test_moto_degree = 0;
int16_t test_moto_current[1];
uint8_t test_servo;
uint8_t key1;

double l;
double imu_z;
double f_r=0.15;
imu_t imu_data;
double time;
double output;

double sum;

void test_nixie_light_init(void){
		digital_tube_init();
	refresh_digital_tube();
}

void test_nixie_light(){ 
	switch_display_num(1, NIXIE_NUM_0);	
		refresh_digital_tube();
	switch_display_num(2, NIXIE_NUM_1);
		refresh_digital_tube();
	switch_display_num(3, NIXIE_NUM_2);
		refresh_digital_tube();
	switch_display_num(4, NIXIE_NUM_3);
		refresh_digital_tube();
	switch_display_num(5, NIXIE_NUM_4);
		refresh_digital_tube();
	switch_display_num(6, NIXIE_NUM_5);
//		refresh_digital_tube();
	switch_display_num(7, NIXIE_NUM_6);
	//	refresh_digital_tube();
	switch_display_num(0, NIXIE_NUM_7);
//	refresh_digital_tube();
}

double low_pass_filter(double *last,double forget_rate,double input){
	return (*last)*(1-forget_rate)+input*forget_rate;
}

void test_moto_control(void)
{
   //LED控制函数
	 write_led_io(LED_IO1,LED_ON );	
	
   //电机的速度给定
   test_moto_speed = rc.ch2 / RC_MAX_VALUE * MAX_WHEEL_RPM;
   switch(rc.sw2){
     case 1:
       test_moto_speed = 6000;
       break;
     case 3:
      test_moto_speed = 10000;
       break;
     case 2:
      test_moto_speed= 15000;
       break;
     default:
       break;
   
   } 
	 
	 get_imu_data(&imu_data);
	 
	 imu_z=imu_data.angle_z;
	 
	 
	 output=time*low_pass_filter(&l,f_r,imu_z);
	 sum+=imu_data.gyro_z;
	 
	 
   //闭环计算电机电流
   test_moto_current[0] = pid_calc(&pid_test_moto, moto_test.speed_rpm, test_moto_speed);
   
   //发送电机的电流
   set_test_motor_current(test_moto_current);
	
   //舵机控制函数周期设定
   set_pwm_group_param(PWM_GROUP1,20000);
	
   //开启控制端口
   start_pwm_output(PWM_IO1);
    
	//舵机控制命令
		if(test_servo == 0 )
		  {
			set_pwm_param(PWM_IO1,2200);
		  }
		else
		  {
		  set_pwm_param(PWM_IO1,1500);
		  }
   

//  扩展板的按键控制电机
//      read_key_io(KEY_IO1,&key1);  
//			if(key1 ==1)
//		{
//			 set_test_motor_current(test_moto_current);
//			}
			
			
}

	
	
   //电机初始化参数设定
   void test_moto_init(void)
   {
   //PID参数初始化		 
	     pid_init(&pid_test_moto, 7000, 0, 1, 0, 0);

   }
