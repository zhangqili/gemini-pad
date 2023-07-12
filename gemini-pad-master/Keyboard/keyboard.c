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
#include "usbd_hid.h"
#include "gpio.h"
#include "keyboard.h"

subKeyBoard keyBoardHIDsub = {0,0,0,0,0,0,0,0};
uint8_t Keyboard_EC11Flag=0;
uint8_t Keyboard_EC11FlagFilter=0;
uint8_t Keyboard_WheelFlag=0;
//K1, K2, K3, K4, SHIFT, ALPHA, KNOB, WHEEL
uint8_t Keyboard_Keys[10]={1};
uint8_t Keyboard_PreviousKeys[10]={1};
uint8_t Keyboard_KeySignalEdgeFlag=0;;

void Keyboard_Scan()
{
    //Keyboard_Keys[0]=KEY1;
    //Keyboard_Keys[1]=KEY2;
    //Keyboard_Keys[2]=KEY3;
    //Keyboard_Keys[3]=KEY4;
    Keyboard_Keys[4]=SHIFT;
    Keyboard_Keys[5]=ALPHA;
    Keyboard_Keys[6]=KNOB;
    Keyboard_Keys[8]=WHEEL;
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
    //keyBoardHIDsub.KEYCODE1=rand()%2?KEY1_BINDING:0;
    //keyBoardHIDsub.KEYCODE2=rand()%2?KEY2_BINDING:0;
    //keyBoardHIDsub.KEYCODE3=rand()%2?KEY3_BINDING:0;
    //keyBoardHIDsub.KEYCODE4=rand()%2?KEY4_BINDING:0;
    keyBoardHIDsub.KEYCODE1=advanced_keys[0].state?KEY1_BINDING:0;
    keyBoardHIDsub.KEYCODE2=advanced_keys[1].state?KEY2_BINDING:0;
    keyBoardHIDsub.KEYCODE3=advanced_keys[2].state?KEY3_BINDING:0;
    keyBoardHIDsub.KEYCODE4=advanced_keys[3].state?KEY4_BINDING:0;
    //keyBoardHIDsub.KEYCODE1=keys[0]?keys[4]?0:0x35:keyBoardHIDsub.KEYCODE1;//`
    //keyBoardHIDsub.MODIFIER=keys[0]?keys[4]?0:0x80:keyBoardHIDsub.MODIFIER;
    //keyBoardHIDsub.KEYCODE2=keys[1]?keys[5]?0:0x2b:keyBoardHIDsub.KEYCODE2;//Tab
    //keyBoardHIDsub.KEYCODE3=keys[2]?keys[6]?0:0x3b:keyBoardHIDsub.KEYCODE3;//F2
    //keyBoardHIDsub.KEYCODE4=keys[3]?keys[7]?0:0x3b:keyBoardHIDsub.KEYCODE4;//Shift+F2
    //keyBoardHIDsub.MODIFIER=keys[3]?keys[7]?0:0x02:keyBoardHIDsub.MODIFIER;
    keyBoardHIDsub.KEYCODE5=Keyboard_Keys[6]?keyBoardHIDsub.KEYCODE5:0x29;
    keyBoardHIDsub.KEYCODE5=Keyboard_Keys[8]?keyBoardHIDsub.KEYCODE5:0x28;
    keyBoardHIDsub.KEYCODE5=(Keyboard_Keys[8]==1&&Keyboard_Keys[6]==1)?0:keyBoardHIDsub.KEYCODE5;
    if(Keyboard_EC11Flag)
    {
        keyBoardHIDsub.KEYCODE6=Keyboard_Keys[7]?0x52:0x51;
    }
    if(Keyboard_WheelFlag)
    {
      keyBoardHIDsub.KEYCODE6=Keyboard_Keys[9]?0x4F:0x50;
    }
    if(!(Keyboard_EC11Flag||Keyboard_WheelFlag))
    {
      keyBoardHIDsub.KEYCODE6=0;
    }

    USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t*)&keyBoardHIDsub,sizeof(keyBoardHIDsub));
}

void Keyboard_CheckSignalEdge()
{
    for(uint8_t i=0;i<10;i++)
    {
        if(Keyboard_Keys[i]!=Keyboard_PreviousKeys[i])
            Keyboard_KeySignalEdgeFlag=1;
        Keyboard_PreviousKeys[i]=Keyboard_Keys[i];
    }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim == &htim2)
    {
        if(htim->Instance->CR1==0x01)
        {
          Keyboard_WheelFlag=10;
          Keyboard_Keys[9]=1;
        }
        if(htim->Instance->CR1==0x11)
        {
          Keyboard_WheelFlag=10;
          Keyboard_Keys[9]=0;
        }
    }

    if(htim == &htim3)
    {
        if(htim->Instance->CR1==0x01)
        {
          Keyboard_EC11Flag=10;
          Keyboard_Keys[7]=0;
        }
        if(htim->Instance->CR1==0x11)
        {
          Keyboard_EC11Flag=10;
          Keyboard_Keys[7]=1;
        }
    }

}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    Keyboard_EC11Flag=10;
    if(GPIO_Pin == GPIO_PIN_6)
    {
        Keyboard_Keys[7]=1;
    }
    if(GPIO_Pin == GPIO_PIN_7)
    {
        Keyboard_Keys[7]=0;
    }
}
