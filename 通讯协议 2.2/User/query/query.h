#ifndef __QUERY_H
#define __QUERY_H
#include "stm32f10x.h"

void electricity_agreement(void);
void curtain_agreement(void);
void experiment_agreement(void);
void door_agreement(void);
void window_agreement(void);
void window2_agreement(void);
void response_OK(void);

void Key_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);









#endif 

