/*
 * keyboard.h
 *
 *  Created on: May 21, 2023
 *      Author: xq123
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "lefl.h"
#include "usb_hid_keys.h"

#define KEY_NUM                 4
#define KEY1                    (!HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin))
#define KEY2                    (!HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin))
#define KEY3                    (!HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin))
#define KEY4                    (!HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin))
#define SHIFT                   HAL_GPIO_ReadPin(SHIFT_GPIO_Port,SHIFT_Pin)
#define ALPHA                   HAL_GPIO_ReadPin(ALPHA_GPIO_Port,ALPHA_Pin)
#define KNOB                    (!HAL_GPIO_ReadPin(KNOB_GPIO_Port,KNOB_Pin))
#define WHEEL                   (!HAL_GPIO_ReadPin(WHEEL_GPIO_Port,WHEEL_Pin))
#define EC11_A                  HAL_GPIO_ReadPin(EC11_A_GPIO_Port,EC11_A_Pin)
#define EC11_B                  HAL_GPIO_ReadPin(EC11_B_GPIO_Port,EC11_B_Pin)
#define CharacterID(x)          (x-'a'+4)

#define FUNCTION_KEY1_BINDING   0
#define FUNCTION_KEY2_BINDING   0
#define FUNCTION_KEY3_BINDING   0
#define FUNCTION_KEY4_BINDING   0

extern uint8_t Keyboard_ReportBuffer[18];
extern lefl_bit_array_t Keyboard_KeyArray;
extern uint8_t Keyboard_EC11Flag;
extern uint8_t Keyboard_WheelFlag;
extern lefl_key_t Keyboard_Keys[6];
/*
key buffer
K1 K2 K3 K4 SHIFT ALPHA KNOB KNOB_S WHEEL WHEEL_S
*/

void Keyboard_Scan();
void Keyboard_SendReport();

#endif /* KEYBOARD_H_ */
