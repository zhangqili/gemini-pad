/*
 * analog.h
 *
 *  Created on: 2023年5月21日
 *      Author: xq123
 */
#include "keyboard.h"
#include "lefl.h"

#ifndef ANALOG_H_
#define ANALOG_H_

#define Analog_Clean() (ADC_Conversion_Count=0)

#define ANALOG_INIT_SCAN_COUNT 32768

extern uint8_t ADC_Conversion_Count;
extern int16_t ADC1_Values[64];
extern int16_t ADC2_Values[64];
extern int16_t ADC3_Values[64];
extern int16_t ADC4_Values[64];
extern int16_t ADC_Value_List[KEY_NUM];

extern float ADC_Sums[KEY_NUM];
extern float ADC_Averages[KEY_NUM];

extern float Analog_Values[KEY_NUM];

extern lefl_advanced_key_t advanced_keys[KEY_NUM];

void Analog_Scan();
void Analog_Init();
void Analog_Average();
void Analog_Check();
float Analog_Normalize(float x, uint8_t n);
void Analog_Recovery();
void Analog_Save();

#endif /* ANALOG_H_ */
