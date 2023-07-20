/*
 * communication.h
 *
 *  Created on: Jun 11, 2023
 *      Author: xq123
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_
#include "stdint.h"

#define BUFFER_LENGTH 64
#define BIT(a) (1<<a)


#define Communication_SOH() USART1_TX_Buffer[0]=1;
#define Communication_STX() USART1_TX_Buffer[1]=2;
#define Communication_ETX() USART1_TX_Buffer[USART1_TX_Length]=3;
#define Communication_EOH() USART1_TX_Buffer[USART1_TX_Length]=4;

#define Communication_Add8(a,b) USART1_TX_Buffer[USART1_TX_Length]=(a);\
                               USART1_TX_Buffer[USART1_TX_Length+1]=(b);\
                               if(USART1_TX_Length<BUFFER_LENGTH)USART1_TX_Length+=2;

#define Communication_Add32(a,b) USART1_TX_Buffer[USART1_TX_Length]=(a);\
                               memcpy(USART1_TX_Buffer+USART1_TX_Length+1,(uint8_t*)&(b),4);\
                               if(USART1_TX_Length<BUFFER_LENGTH)USART1_TX_Length+=5;

#define Communication_AddLength()   USART1_TX_Buffer[USART1_TX_Length]=(USART1_TX_Length+1);\
                                    USART1_TX_Length++;

#define Communication_Transmit()    Communication_AddLength();\
                                    HAL_UART_Transmit_DMA(&huart1,USART1_TX_Buffer,USART1_TX_Length);\
                                    USART1_TX_Length=0;

#define Communication_Enable(huart,buf,len) HAL_UART_Receive_DMA(huart,buf,len);\
                                            __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);

typedef enum
{
    //0x00
    PROTOCOL_KEYS0,
    PROTOCOL_KEYS1,
    PROTOCOL_NA_02,
    PROTOCOL_NA_03,
    PROTOCOL_NA_04,
    PROTOCOL_NA_05,
    PROTOCOL_NA_06,
    PROTOCOL_NA_07,
    PROTOCOL_NA_08,
    PROTOCOL_NA_09,
    PROTOCOL_NA_0A,
    PROTOCOL_NA_0B,
    PROTOCOL_NA_0C,
    PROTOCOL_NA_0D,
    PROTOCOL_NA_0E,
    PROTOCOL_NA_0F,
    //0x10
    PROTOCOL_ANALOG1,
    PROTOCOL_ANALOG2,
    PROTOCOL_ANALOG3,
    PROTOCOL_ANALOG4,
    PROTOCOL_NA_14,
    PROTOCOL_NA_15,
    PROTOCOL_NA_16,
    PROTOCOL_NA_17,
    PROTOCOL_NA_18,
    PROTOCOL_NA_19,
    PROTOCOL_NA_1A,
    PROTOCOL_NA_1B,
    PROTOCOL_NA_1C,
    PROTOCOL_NA_1D,
    PROTOCOL_NA_1E,
    PROTOCOL_NA_1F,
    //0x20
    PROTOCOL_ANALOG1_RAW,
    PROTOCOL_ANALOG2_RAW,
    PROTOCOL_ANALOG3_RAW,
    PROTOCOL_ANALOG4_RAW,
    PROTOCOL_NA_24,
    PROTOCOL_NA_25,
    PROTOCOL_NA_26,
    PROTOCOL_NA_27,
    PROTOCOL_NA_28,
    PROTOCOL_NA_29,
    PROTOCOL_NA_2A,
    PROTOCOL_NA_2B,
    PROTOCOL_NA_2C,
    PROTOCOL_NA_2D,
    PROTOCOL_NA_2E,
    PROTOCOL_NA_2F,
    //0x30
    PROTOCOL_SCAN_COUNT,
    PROTOCOL_CMD,
    //0xF0
    PROTOCOL_DEBUG=0xF0,
} USART_PROTOCOL;


typedef enum
{
    //0x00
    CMD_NULL,
    CMD_CALIBRATION_START,
    CMD_CALIBRATION_UP,
    CMD_CALIBRATION_DOWN,
    CMD_CALIBRATION_END,
    CMD_READ_CONFIG,
    CMD_REPORT_START,
    CMD_REPORT_STOP,
    CMD_NA_08,
    CMD_NA_09,
    CMD_NA_0A,
    CMD_NA_0B,
    CMD_NA_0C,
    CMD_NA_0D,
    CMD_NA_0E,
    CMD_NA_0F,
} USART_CMD;

extern uint8_t USART1_TX_Buffer[BUFFER_LENGTH];
extern uint8_t USART1_TX_Length;
extern uint8_t USART1_RX_Buffer[BUFFER_LENGTH];
extern uint8_t USART1_RX_Length;

extern uint16_t USART1_TX_Count;
extern uint16_t USART1_RX_Count;

void Communication_Pack();
void Communication_Unpack(UART_HandleTypeDef *huart);

#endif /* COMMUNICATION_H_ */
