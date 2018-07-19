#ifndef __EXECUTE_TASK_H__
#define __EXECUTE_TASK_H__

#include "stm32f4xx_hal.h"

void execute_task(const void* argu);

void test_moto_init(void);
void test_moto_control(void);
void test_nixie_light(void);
void test_nixie_light_init(void);
#endif

