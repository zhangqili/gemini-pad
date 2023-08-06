/*
 * communication.c
 *
 *  Created on: Jun 11, 2023
 *      Author: xq123
 */
#include "main.h"
#include "communication.h"
#include "lefl.h"
#include "fezui.h"
#include "fezui_var.h"

COM_CREATE(USART1)

uint32_t USART1_TX_Count=0;
uint32_t USART1_RX_Count=0;

extern DMA_HandleTypeDef hdma_usart1_rx;

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
              USART1_RX_Count++;
              for(uint8_t i = 0;i<USART1_RX_Length-1;)
              {
                  switch(USART1_RX_Buffer[i])
                  {
                  case PROTOCOL_KEYS0:
                      /*
                      analog_keys[0].state=(USART1_RX_Buffer[i+1]&BIT(3));
                      analog_keys[1].state=(USART1_RX_Buffer[i+1]&BIT(2));
                      analog_keys[2].state=(USART1_RX_Buffer[i+1]&BIT(1));
                      analog_keys[3].state=(USART1_RX_Buffer[i+1]&BIT(0));
                      */
                      //lefl_analog_key_update(analog_keys+0, (USART1_RX_Buffer[i+1]&BIT(3)));
                      //lefl_analog_key_update(analog_keys+2, (USART1_RX_Buffer[i+1]&BIT(2)));
                      //lefl_analog_key_update(analog_keys+3, (USART1_RX_Buffer[i+1]&BIT(1)));
                      //lefl_analog_key_update(analog_keys+4, (USART1_RX_Buffer[i+1]&BIT(0)));
                      key_buffer[0]=(USART1_RX_Buffer[i+1]&BIT(3));
                      key_buffer[1]=(USART1_RX_Buffer[i+1]&BIT(2));
                      key_buffer[2]=(USART1_RX_Buffer[i+1]&BIT(1));
                      key_buffer[3]=(USART1_RX_Buffer[i+1]&BIT(0));
                      key_buffer[4]=(USART1_RX_Buffer[i+1]&BIT(7));
                      key_buffer[5]=(USART1_RX_Buffer[i+1]&BIT(6));
                      key_buffer[6]=!(USART1_RX_Buffer[i+1]&BIT(5));
                      key_buffer[7]=!(USART1_RX_Buffer[i+1]&BIT(4));
                      i+=2;
                      break;
                  case PROTOCOL_KEYS1:
                      key_buffer[8]=(USART1_RX_Buffer[i+1]&BIT(3));
                      key_buffer[9]=(USART1_RX_Buffer[i+1]&BIT(2));
                      key_buffer[10]=(USART1_RX_Buffer[i+1]&BIT(1));
                      key_buffer[11]=(USART1_RX_Buffer[i+1]&BIT(0));
                      i+=2;
                      break;
                      /*
                  case PROTOCOL_ANALOG1:
                      analog_history_buffer[0]=USART1_RX_Buffer[i+1];
                      i+=2;
                      break;
                  case PROTOCOL_ANALOG2:
                      analog_history_buffer[1]=USART1_RX_Buffer[i+1];
                      i+=2;
                      break;
                  case PROTOCOL_ANALOG3:
                      analog_history_buffer[2]=USART1_RX_Buffer[i+1];
                      i+=2;
                      break;
                  case PROTOCOL_ANALOG4:
                      analog_history_buffer[3]=USART1_RX_Buffer[i+1];
                      i+=2;
                      break;
                      */
                  case PROTOCOL_ANALOG1_RAW:
                      memcpy((uint8_t *)&(advanced_keys[0].raw),USART1_RX_Buffer+i+1,4);
                      lefl_advanced_key_update_raw(advanced_keys + 0, (uint16_t)advanced_keys[0].raw);
                      i+=5;
                      break;
                  case PROTOCOL_ANALOG2_RAW:
                      memcpy((uint8_t *)&(advanced_keys[1].raw),USART1_RX_Buffer+i+1,4);
                      lefl_advanced_key_update_raw(advanced_keys + 1, (uint16_t)advanced_keys[1].raw);
                      i+=5;
                      break;
                  case PROTOCOL_ANALOG3_RAW:
                      memcpy((uint8_t *)&(advanced_keys[2].raw),USART1_RX_Buffer+i+1,4);
                      lefl_advanced_key_update_raw(advanced_keys + 2, (uint16_t)advanced_keys[2].raw);
                      i+=5;
                      break;
                  case PROTOCOL_ANALOG4_RAW:
                      memcpy((uint8_t *)&(advanced_keys[3].raw),USART1_RX_Buffer+i+1,4);
                      lefl_advanced_key_update_raw(advanced_keys + 3, (uint16_t)advanced_keys[3].raw);
                      i+=5;
                      break;
                  case PROTOCOL_CMD:
                      cmd_buffer=USART1_RX_Buffer[i+1];
                      i+=2;
                      break;
                  case PROTOCOL_DEBUG:
                      fezui_debug=USART1_RX_Buffer[i+1];
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




