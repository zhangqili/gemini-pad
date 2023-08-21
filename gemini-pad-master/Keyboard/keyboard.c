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
lefl_key_t Keyboard_Keys[8];
void Keyboard_Scan()
{
    //Keyboard_Keys[0]=KEY1;
    //Keyboard_Keys[1]=KEY2;
    //Keyboard_Keys[2]=KEY3;
    //Keyboard_Keys[3]=KEY4;
    lefl_key_update(&KEY_SHIFT,SHIFT);
    lefl_key_update(&KEY_ALPHA,ALPHA);
    lefl_key_update(&KEY_KNOB,KNOB);
    lefl_key_update(&KEY_WHEEL,WHEEL);
    if(Keyboard_EC11Flag)
    {
        Keyboard_EC11Flag--;
    }
    if(Keyboard_WheelFlag)
    {
        Keyboard_WheelFlag--;
    }
    if(!Keyboard_EC11Flag)
    {
        lefl_key_update(&KEY_KNOB_CLOCKWISE, false);
        lefl_key_update(&KEY_KNOB_ANTICLOCKWISE, false);
    }
    if(!Keyboard_WheelFlag)
    {

        lefl_key_update(&KEY_WHEEL_CLOCKWISE, false);
        lefl_key_update(&KEY_WHEEL_ANTICLOCKWISE, false);
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
    Keyboard_ReportBuffer[0]=0;
    for (uint8_t i = 0; i < KEY_NUM; i++)
    {
        Keyboard_ReportBuffer[0]|= Keyboard_AdvancedKeys[i].key.state?((Keyboard_AdvancedKeys[i].key.id>>8) & 0xFF):0;
        lefl_bit_array_set(&Keyboard_KeyArray, Keyboard_AdvancedKeys[i].key.id & 0xFF, Keyboard_AdvancedKeys[i].key.state);
    }
    /*
    lefl_bit_array_set(&Keyboard_KeyArray, KEY1_BINDING, Keyboard_AdvancedKeys[0].key.state);
    lefl_bit_array_set(&Keyboard_KeyArray, KEY2_BINDING, Keyboard_AdvancedKeys[1].key.state);
    lefl_bit_array_set(&Keyboard_KeyArray, KEY3_BINDING, Keyboard_AdvancedKeys[2].key.state);
    lefl_bit_array_set(&Keyboard_KeyArray, KEY4_BINDING, Keyboard_AdvancedKeys[3].key.state);
    */
    Keyboard_ReportBuffer[0]|=((KEY_KNOB.id>>8) & 0xFF);
    Keyboard_ReportBuffer[0]|=((KEY_WHEEL.id>>8) & 0xFF);
    lefl_bit_array_set(&Keyboard_KeyArray, KNOB_BINDING, KEY_KNOB.state);
    lefl_bit_array_set(&Keyboard_KeyArray, WHEEL_BINDING, KEY_WHEEL.state);

    lefl_bit_array_set(&Keyboard_KeyArray, KEY_UP_ARROW, KEY_KNOB_CLOCKWISE.state);
    lefl_bit_array_set(&Keyboard_KeyArray, KEY_DOWN_ARROW, KEY_KNOB_ANTICLOCKWISE.state);
    lefl_bit_array_set(&Keyboard_KeyArray, KEY_LEFT_ARROW, KEY_WHEEL_CLOCKWISE.state);
    lefl_bit_array_set(&Keyboard_KeyArray, KEY_RIGHT_ARROW, KEY_WHEEL_ANTICLOCKWISE.state);

    USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,Keyboard_ReportBuffer,USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim == &htim2)
    {
        Keyboard_WheelFlag=8;
        if(htim->Instance->CR1==0x01)
        {
            lefl_key_update(&KEY_WHEEL_CLOCKWISE, true);
            lefl_key_update(&KEY_WHEEL_ANTICLOCKWISE, false);
        }
        if(htim->Instance->CR1==0x11)
        {
            lefl_key_update(&KEY_WHEEL_CLOCKWISE, false);
            lefl_key_update(&KEY_WHEEL_ANTICLOCKWISE, true);
        }
    }

    if(htim == &htim3)
    {
        Keyboard_EC11Flag=8;
        if(htim->Instance->CR1==0x01)
        {
            lefl_key_update(&KEY_KNOB_CLOCKWISE, false);
            lefl_key_update(&KEY_KNOB_ANTICLOCKWISE, true);
        }
        if(htim->Instance->CR1==0x11)
        {
            lefl_key_update(&KEY_KNOB_CLOCKWISE, true);
            lefl_key_update(&KEY_KNOB_ANTICLOCKWISE, false);
        }
    }
}

