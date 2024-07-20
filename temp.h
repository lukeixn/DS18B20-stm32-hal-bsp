#ifndef _TEMP_H
#define _TEMP_H

#include "main.h"
#define io_port  DQ_GPIO_Port
#define io_pin  DQ_Pin
#define DQ(x)  HAL_GPIO_WritePin(io_port,io_pin,(GPIO_PinState) x)
#define R_DQ   HAL_GPIO_ReadPin(io_port,io_pin)
extern void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void gpio_uodate_init(void);
void test_pin(void);

// 例如，假设GPIO_PIN_1是一个宏定义，指定了第一个GPIO引脚

// 后续可以继续设置 struct1 的 Mode、Pull 和 Speed 成员





uint32_t ReadTemp(void); 

#endif
