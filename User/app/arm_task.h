#ifndef __ARM_TASK_H__
#define __ARM_TASK_H__

#include "stm32f4xx_hal.h"

void arm_param_init(void);
void claw_param_init(void);
void arm_power_calculate(void);
void claw_power_calculate(void);
void claw_param_init(void);
void arm_task(const void* argu);
#endif
