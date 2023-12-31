/*
 * communication.c
 *
 *  Created on: Jun 11, 2023
 *      Author: xq123
 */
#include "main.h"
#include "communication.h"
#include "keyboard.h"
#include "analog.h"
#include "string.h"
#include "lefl.h"

COM_CREATE(USART1)

uint16_t USART1_TX_Count=0;
uint16_t USART1_RX_Count=0;

extern uint8_t cmd_buffer;

extern DMA_HandleTypeDef hdma_usart1_rx;

void Communication_Pack()
{
    USART1_TX_Length=0;
    //Communication_Add(1,2);
    Communication_Add8(USART1, PROTOCOL_KEYS0,Keyboard_AdvancedKeys[0].key.state<<3|Keyboard_AdvancedKeys[1].key.state<<2|Keyboard_AdvancedKeys[2].key.state<<1|Keyboard_AdvancedKeys[3].key.state|Keyboard_Keys[0].state<<7|Keyboard_Keys[1].state<<6|Keyboard_Keys[2].state<<5|Keyboard_Keys[3].state<<4);

    //Communication_Add(PROTOCOL_KEYS0,Keyboard_Keys[0]<<3|Keyboard_Keys[1]<<2|Keyboard_Keys[2]<<1|Keyboard_Keys[3]|Keyboard_Keys[4]<<7|Keyboard_Keys[5]<<6|Keyboard_Keys[6]<<5|Keyboard_Keys[8]<<4);
    Communication_Add8(USART1, PROTOCOL_KEYS1,(Keyboard_EC11Flag?(Keyboard_Keys[4].state?BIT(2):BIT(3)):0)|
                                      (Keyboard_WheelFlag?(Keyboard_Keys[5].state?BIT(0):BIT(1)):0));
    //Communication_Add(PROTOCOL_KEYS1,(Keyboard_EC11Flag?(Keyboard_Keys[7]?BIT(3):BIT(2)):0));

    //Communication_Add(PROTOCOL_ANALOG1,(uint8_t)(analog_keys[0].upper_bound/16.0));
    //Communication_Add(PROTOCOL_ANALOG2,(uint8_t)(analog_keys[0].lower_bound/16.0));
    //Communication_Add(PROTOCOL_ANALOG3,(uint8_t)(Analog_Values[2]*256.0));
    //Communication_Add(PROTOCOL_ANALOG4,(uint8_t)(Analog_Values[3]*256.0));

    /*
    Communication_Add8(PROTOCOL_ANALOG1,(uint8_t)(ADC_Value_List[0]/16));
    Communication_Add8(PROTOCOL_ANALOG2,(uint8_t)(ADC_Value_List[1]/16));
    Communication_Add8(PROTOCOL_ANALOG3,(uint8_t)(ADC_Value_List[2]/16));
    Communication_Add8(PROTOCOL_ANALOG4,(uint8_t)(ADC_Value_List[3]/16));
    */
    Communication_Add8(USART1, PROTOCOL_DEBUG,(uint8_t)(ADC1_Values[1]/16));
    /*
    Communication_Add8(PROTOCOL_ANALOG1,(uint8_t)(advanced_keys[0].value<0?0:(advanced_keys[0].value>1.0?255:advanced_keys[0].value*255)));
    Communication_Add8(PROTOCOL_ANALOG2,(uint8_t)(advanced_keys[1].value<0?0:(advanced_keys[1].value>1.0?255:advanced_keys[1].value*255)));
    Communication_Add8(PROTOCOL_ANALOG3,(uint8_t)(advanced_keys[2].value<0?0:(advanced_keys[2].value>1.0?255:advanced_keys[2].value*255)));
    Communication_Add8(PROTOCOL_ANALOG4,(uint8_t)(advanced_keys[3].value<0?0:(advanced_keys[3].value>1.0?255:advanced_keys[3].value*255)));
    */

    Communication_Add32(USART1, PROTOCOL_ANALOG1_RAW,Keyboard_AdvancedKeys[0].raw);
    Communication_Add32(USART1, PROTOCOL_ANALOG2_RAW,Keyboard_AdvancedKeys[1].raw);
    Communication_Add32(USART1, PROTOCOL_ANALOG3_RAW,Keyboard_AdvancedKeys[2].raw);
    Communication_Add32(USART1, PROTOCOL_ANALOG4_RAW,Keyboard_AdvancedKeys[3].raw);

    //Communication_Add(3,4);
}


void Communication_Unpack(UART_HandleTypeDef *huart)
{
    if(RESET != __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
    {
      __HAL_UART_CLEAR_IDLEFLAG(huart);
      HAL_UART_DMAStop(huart);

      if(huart->Instance==USART1)
      {
          USART1_RX_Length = BUFFER_LENGTH - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
          //if(USART1_RX_Buffer[0]==1&&USART1_RX_Buffer[1]==2&&USART1_RX_Buffer[USART1_RX_Length-2]==3&&USART1_RX_Buffer[USART1_RX_Length-1]==4)
          if(USART1_RX_Buffer[USART1_RX_Length-1]==USART1_RX_Length)
          {
              for(uint8_t i = 0;i<USART1_RX_Length-1;)
              {
                  switch(USART1_RX_Buffer[i])
                  {
                      case PROTOCOL_CMD:
                          cmd_buffer=USART1_RX_Buffer[i+1];
                          i+=2;
                          break;
                      default:
                          i+=2;
                          break;
                  }
              }
          }
          HAL_UART_Receive_DMA(huart, USART1_RX_Buffer, BUFFER_LENGTH);
      }
    }
}


