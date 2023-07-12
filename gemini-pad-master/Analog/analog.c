/*
 * analog.c
 *
 *  Created on: 2023年5月21日
 *      Author: xq123
 */
#include "main.h"
#include "usart.h"
#include "stdlib.h"
#include "stdio.h"
#include "adc.h"
#include "dma.h"
#include "gpio.h"
#include "analog.h"
#include "rgb.h"
#include "flash_address.h"
#include "communication.h"
#include "MB85RC16.h"
#include "lefl.h"

uint8_t ADC_Conversion_Count=0;
int16_t ADC1_Values[64]={0};
int16_t ADC2_Values[64]={0};
int16_t ADC3_Values[64]={0};
int16_t ADC4_Values[64]={0};

int16_t ADC_Value_List[KEY_NUM]={0};
uint8_t ADC_Conversion_Flag=0;

float ADC_Sums[KEY_NUM]={0.0};
float ADC_Averages[KEY_NUM]={0.0};

float Analog_Values[KEY_NUM]={0.0};

lefl_advanced_key_t advanced_keys[KEY_NUM]=
        {
                {
                        .mode=LEFL_KEY_ANALOG_RAPID_MODE,
                        .trigger_distance=0.02,
                        .release_distance=0.02,
                        .schmitt_parameter=0.01,
                        .key_cb=NULL,
                },
                {
                        .mode=LEFL_KEY_ANALOG_RAPID_MODE,
                        .trigger_distance=0.02,
                        .release_distance=0.02,
                        .schmitt_parameter=0.01,
                        .key_cb=NULL,
                },
                {
                        .mode=LEFL_KEY_ANALOG_RAPID_MODE,
                        .trigger_distance=0.02,
                        .release_distance=0.02,
                        .schmitt_parameter=0.01,
                        .key_cb=NULL,
                },
                {
                        .mode=LEFL_KEY_ANALOG_RAPID_MODE,
                        .trigger_distance=0.02,
                        .release_distance=0.02,
                        .schmitt_parameter=0.01,
                        .key_cb=NULL,
                }
        };

void Analog_Init()
{
    RGB_Flash();
    for (uint16_t i = 0; i < ANALOG_INIT_SCAN_COUNT; i++)
    {
        for (uint8_t j = 0; j < KEY_NUM; j++)
        {
            HAL_ADC_Start(&hadc1);
            HAL_ADC_PollForConversion(&hadc1,1);
            ADC_Sums[j]+=HAL_ADC_GetValue(&hadc1);
        }
    }

    for (uint8_t i = 0; i < KEY_NUM; i++)
    {
        advanced_keys[i].upper_bound=ADC_Sums[i]/(float)ANALOG_INIT_SCAN_COUNT;
        ADC_Sums[i]=0.0;
    }

    Communication_Add8(PROTOCOL_CMD,CMD_CALIBRATION_DOWN);
    Communication_Transmit();
    RGB_Colors[0].g=127;
    RGB_Colors[1].b=127;
    RGB_Colors[2].r=127;
    RGB_Colors[3].r=127;
    RGB_Colors[3].g=127;
    RGB_Set(RGB_Colors[0].r,RGB_Colors[0].g,RGB_Colors[0].b,0);
    RGB_Set(RGB_Colors[1].r,RGB_Colors[1].g,RGB_Colors[1].b,1);
    RGB_Set(RGB_Colors[2].r,RGB_Colors[2].g,RGB_Colors[2].b,2);
    RGB_Set(RGB_Colors[3].r,RGB_Colors[3].g,RGB_Colors[3].b,3);
    HAL_Delay(1000);
    for (uint16_t i = 0; i < ANALOG_INIT_SCAN_COUNT; i++)
    {
        for (uint8_t j = 0; j < KEY_NUM; j++)
        {
            HAL_ADC_Start(&hadc1);
            HAL_ADC_PollForConversion(&hadc1,1);
            ADC_Sums[j]+=HAL_ADC_GetValue(&hadc1);
        }
    }
    for (uint8_t i = 0; i < KEY_NUM; i++)
    {
        advanced_keys[i].lower_bound=ADC_Sums[i]/(float)ANALOG_INIT_SCAN_COUNT;
        ADC_Sums[i]=0.0;
    }

    RGB_Colors[0].g=0;
    RGB_Colors[1].b=0;
    RGB_Colors[2].r=0;
    RGB_Colors[3].r=0;
    RGB_Colors[3].g=0;
    RGB_Set(RGB_Colors[0].r,RGB_Colors[0].g,RGB_Colors[0].b,0);
    RGB_Set(RGB_Colors[1].r,RGB_Colors[1].g,RGB_Colors[1].b,1);
    RGB_Set(RGB_Colors[2].r,RGB_Colors[2].g,RGB_Colors[2].b,2);
    RGB_Set(RGB_Colors[3].r,RGB_Colors[3].g,RGB_Colors[3].b,3);
    for (uint8_t i = 0; i < KEY_NUM; i++)
    {
        lefl_advanced_key_set_range(advanced_keys+i,advanced_keys[i].upper_bound,advanced_keys[i].lower_bound);
    }

    for (uint8_t i = 0; i < KEY_NUM; i++)
    {
        lefl_advanced_key_set_deadzone(advanced_keys+i,0.01,0.1);
    }
    Analog_Save();

    Communication_Add8(PROTOCOL_CMD,CMD_CALIBRATION_END);
    Communication_Transmit();
    /*
    for(uint8_t i =0;i<4;i++)
    {
        sprintf(buf,"UP%d=%f\n",i,Upper_Bound_List[i]);
        HAL_UART_Transmit(&huart1,buf,30,10);
        sprintf(buf,"LOW%d=%f\n",i,Lower_Bound_List[i]);
        HAL_UART_Transmit(&huart1,buf,30,10);
        sprintf(buf,"RANGE%d=%f\n",i,Range_List[i]);
        HAL_UART_Transmit(&huart1,buf,30,10);
    }
    */
}

void Analog_Scan()
{
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1,1);
    ADC1_Values[ADC_Conversion_Count]=HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1,1);
    ADC2_Values[ADC_Conversion_Count]=HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1,1);
    ADC3_Values[ADC_Conversion_Count]=HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1,1);
    ADC4_Values[ADC_Conversion_Count]=HAL_ADC_GetValue(&hadc1);
    ADC_Conversion_Count++;
}

void Analog_Average()
{
    ADC_Sums[0]=0;
    ADC_Sums[1]=0;
    ADC_Sums[2]=0;
    ADC_Sums[3]=0;
    for (uint8_t i = 1; i < ADC_Conversion_Count; i++)
    {
        ADC_Sums[0]+=ADC1_Values[i];
        ADC_Sums[1]+=ADC2_Values[i];
        ADC_Sums[2]+=ADC3_Values[i];
        ADC_Sums[3]+=ADC4_Values[i];
    }
    ADC_Value_List[0]=ADC_Sums[0]/(ADC_Conversion_Count-1);
    ADC_Value_List[1]=ADC_Sums[1]/(ADC_Conversion_Count-1);
    ADC_Value_List[2]=ADC_Sums[2]/(ADC_Conversion_Count-1);
    ADC_Value_List[3]=ADC_Sums[3]/(ADC_Conversion_Count-1);
}

void Analog_Check()
{
    for (uint8_t i = 0; i < KEY_NUM; i++)
    {
        lefl_advanced_key_update_raw(advanced_keys+i, ADC_Value_List[i]);
    }
}


void Analog_Recovery()
{
    for (uint16_t i = 0; i < KEY_NUM; i++)
    {
        MB85RC16_ReadByte (i*64+KEY1_CONFIG_ADDRESS,       &(advanced_keys[i].mode));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1,     &(advanced_keys[i].trigger_distance));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*1, &(advanced_keys[i].release_distance));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*2, &(advanced_keys[i].schmitt_parameter));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*3, &(advanced_keys[i].trigger_speed));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*4, &(advanced_keys[i].release_speed));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*5, &(advanced_keys[i].upper_deadzone));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*6, &(advanced_keys[i].lower_deadzone));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*7, &(advanced_keys[i].range));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*8, &(advanced_keys[i].upper_bound));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*9, &(advanced_keys[i].lower_bound));
    }
}

void Analog_Save()
{
    for (uint16_t i = 0; i < KEY_NUM; i++)
    {
        advanced_keys[i].mode=LEFL_KEY_ANALOG_RAPID_MODE;
        advanced_keys[i].trigger_distance=0.03,
        advanced_keys[i].release_distance=0.03,
        advanced_keys[i].schmitt_parameter=0.01,
        advanced_keys[i].trigger_speed=0.01,
        advanced_keys[i].release_speed=-0.01,
        MB85RC16_WriteByte (i*64+KEY1_CONFIG_ADDRESS,       advanced_keys[i].mode);
        MB85RC16_WriteFloat(i*64+KEY1_CONFIG_ADDRESS+1,     advanced_keys[i].trigger_distance);
        MB85RC16_WriteFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*1, advanced_keys[i].release_distance);
        MB85RC16_WriteFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*2, advanced_keys[i].schmitt_parameter);
        MB85RC16_WriteFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*3, advanced_keys[i].trigger_speed);
        MB85RC16_WriteFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*4, advanced_keys[i].release_speed);
        MB85RC16_WriteFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*5, advanced_keys[i].upper_deadzone);
        MB85RC16_WriteFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*6, advanced_keys[i].lower_deadzone);
        MB85RC16_WriteFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*7, advanced_keys[i].range);
        MB85RC16_WriteFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*8, advanced_keys[i].upper_bound);
        MB85RC16_WriteFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*9, advanced_keys[i].lower_bound);
    }
}

