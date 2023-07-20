/*
 * fezui_var.h
 *
 *  Created on: Jul 21, 2023
 *      Author: xq123
 */

#ifndef FEZUI_VAR_H_
#define FEZUI_VAR_H_
#include "fezui.h"

extern const uint8_t led_seg_like_font[195] U8G2_FONT_SECTION("led_seg_like_font");
extern fezui_t fezui;
extern uint8_t key_buffer[KEY_NUM];
extern lefl_advanced_key_t advanced_keys[MAIN_KEY_NUM];
extern lefl_key_t keys[KEY_NUM-MAIN_KEY_NUM];

extern uint32_t fezui_keytotalcounts[MAIN_KEY_NUM];
extern uint32_t fezui_keyinitcounts[MAIN_KEY_NUM];
extern uint32_t fezui_fps;
extern uint8_t fezui_kps;
extern uint8_t KPS_history_max;
extern char fpsstr[8];
extern char comstr[8];
extern lefl_loop_array_t KPS_history;
extern uint8_t UI_KPSMaximumPerSecond;
extern uint8_t fezui_rest_countdown;
extern uint8_t fezui_debug;
extern uint8_t cmd_buffer;

extern uint32_t fezui_run_time;


extern lefl_loop_array_t analog_historys[4];
extern uint8_t analog_history_buffer[4];

extern lefl_bit_array_t lines[4];
extern lefl_loop_array_t KPS_queue;


#endif /* FEZUI_VAR_H_ */
