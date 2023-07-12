/*
 * rgb.h
 *
 *  Created on: May 21, 2023
 *      Author: xq123
 */

#ifndef RGB_H_
#define RGB_H_

#include "lefl.h"

#define LED_NUM                 (4)
#define ONE_PULSE               (61)
#define ZERO_PULSE              (29)
#define NONE_PULSE              (90)
#define RGB_BUFFER_LENGTH       (424)

#define RGB_Start() HAL_TIM_PWM_Start_DMA(&htim8,TIM_CHANNEL_3,RGB_Buffer,RGB_BUFFER_LENGTH);
//#define RGB_Start() HAL_TIMEx_PWMN_Start_DMA(&htim8,TIM_CHANNEL_3,RGB_buffer,RGB_BUFFER_LENGTH);

typedef struct
{
	uint16_t H;
	uint16_t S;
	uint16_t V;
}HSV_Color;

extern uint32_t RGB_Buffer[RGB_BUFFER_LENGTH];
extern lefl_color_rgb_t RGB_Colors[4];

void RGB_Set(uint8_t r,uint8_t g,uint8_t b,uint16_t index);
void RGB_Flash();
void RGB_TurnOff();

#endif /* RGB_H_ */
