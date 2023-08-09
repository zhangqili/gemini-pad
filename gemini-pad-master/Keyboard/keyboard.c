/*
 * keyboard.c
 *
 *  Created on: May 21, 2023
 *      Author: xq123
 */
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "analog.h"
#include "usbd_custom_hid_if.h"
#include "gpio.h"
#include "keyboard.h"

#define KEY1_BINDING            KEY_Z
#define KEY2_BINDING            KEY_X
#define KEY3_BINDING            KEY_C
#define KEY4_BINDING            KEY_V
#define KNOB_BINDING            KEY_ESC
#define WHEEL_BINDING           KEY_ENTER

uint8_t Keyboard_ReportBuffer[18];
lefl_bit_array_t Keyboard_KeyArray;

uint8_t Keyboard_EC11Flag=0;
uint8_t Keyboard_WheelFlag=0;
//SHIFT, ALPHA, KNOB, WHEEL, KNOB Rotation direction, WHEEL Rotation direction
lefl_key_t Keyboard_Keys[6];

void Keyboard_Scan()
{
    //Keyboard_Keys[0]=KEY1;
    //Keyboard_Keys[1]=KEY2;
    //Keyboard_Keys[2]=KEY3;
    //Keyboard_Keys[3]=KEY4;
    lefl_key_update(Keyboard_Keys+0,SHIFT);
    lefl_key_update(Keyboard_Keys+1,ALPHA);
    lefl_key_update(Keyboard_Keys+2,KNOB);
    lefl_key_update(Keyboard_Keys+3,WHEEL);
    if(Keyboard_EC11Flag)
    {
        Keyboard_EC11Flag--;
    }
    if(Keyboard_WheelFlag)
    {
        Keyboard_WheelFlag--;
    }
}

void Keyboard_SendReport()
{
    /*
    lefl_bit_array_set(&Keyboard_KeyArray, KEY1_BINDING, !(rand()%16));
    lefl_bit_array_set(&Keyboard_KeyArray, KEY2_BINDING, !(rand()%16));
    lefl_bit_array_set(&Keyboard_KeyArray, KEY3_BINDING, !(rand()%16));
    lefl_bit_array_set(&Keyboard_KeyArray, KEY4_BINDING, !(rand()%16));
    */
    lefl_bit_array_set(&Keyboard_KeyArray, KEY1_BINDING, Keyboard_AdvancedKeys[0].key.state);
    lefl_bit_array_set(&Keyboard_KeyArray, KEY2_BINDING, Keyboard_AdvancedKeys[1].key.state);
    lefl_bit_array_set(&Keyboard_KeyArray, KEY3_BINDING, Keyboard_AdvancedKeys[2].key.state);
    lefl_bit_array_set(&Keyboard_KeyArray, KEY4_BINDING, Keyboard_AdvancedKeys[3].key.state);
    lefl_bit_array_set(&Keyboard_KeyArray, KNOB_BINDING, Keyboard_Keys[2].state);
    lefl_bit_array_set(&Keyboard_KeyArray, WHEEL_BINDING, Keyboard_Keys[3].state);

    if(Keyboard_EC11Flag)
    {
        lefl_bit_array_set(&Keyboard_KeyArray, KEY_UP_ARROW, Keyboard_Keys[4].state);
        lefl_bit_array_set(&Keyboard_KeyArray, KEY_DOWN_ARROW, !Keyboard_Keys[4].state);
    }
    else
    {
        lefl_bit_array_set(&Keyboard_KeyArray, KEY_UP_ARROW, false);
        lefl_bit_array_set(&Keyboard_KeyArray, KEY_DOWN_ARROW, false);
    }
    if(Keyboard_WheelFlag)
    {
        lefl_bit_array_set(&Keyboard_KeyArray, KEY_LEFT_ARROW, Keyboard_Keys[5].state);
        lefl_bit_array_set(&Keyboard_KeyArray, KEY_RIGHT_ARROW, !Keyboard_Keys[5].state);
    }
    else
    {
        lefl_bit_array_set(&Keyboard_KeyArray, KEY_LEFT_ARROW, false);
        lefl_bit_array_set(&Keyboard_KeyArray, KEY_RIGHT_ARROW, false);
    }

    USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,Keyboard_ReportBuffer,USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim == &htim2)
    {
        Keyboard_WheelFlag=8;
        if(htim->Instance->CR1==0x01)
        {
            lefl_key_update(Keyboard_Keys+5, false);
        }
        if(htim->Instance->CR1==0x11)
        {
            lefl_key_update(Keyboard_Keys+5, true);
        }
    }

    if(htim == &htim3)
    {
        Keyboard_EC11Flag=8;
        if(htim->Instance->CR1==0x01)
        {
            lefl_key_update(Keyboard_Keys+4, true);
        }
        if(htim->Instance->CR1==0x11)
        {
            lefl_key_update(Keyboard_Keys+4, false);
        }
    }

}

