/*
 * fezui_config.h
 *
 *  Created on: 2023年6月19日
 *      Author: xq123
 */

#ifndef FEZUI_CONFIG_H_
#define FEZUI_CONFIG_H_

#define WIDTH                 128
#define HEIGHT                64
#define STRING_LENGTH         64
#define NUMBER_STRING_LENGTH  STRING_LENGTH
#define REFRESH_RATE          170
#define KPS_HISTORY_LENGTH    65
//#define TILE_LENGTH         56
#define SCREEN_REST_TIME      60
#define KEY_NUM               12
#define MAIN_KEY_NUM          4
#define ITEM_HEIGHT           14
#define HISTORY_LENGTH        65

#define _SCREEN_REST_ON
#define _FPS_ON

#define roll()                rand()%2;

extern const uint8_t led_seg_like_font[195] U8G2_FONT_SECTION("led_seg_like_font");

extern uint8_t key_buffer[KEY_NUM];
extern lefl_advanced_key_t advanced_keys[MAIN_KEY_NUM];
extern lefl_key_t keys[KEY_NUM-MAIN_KEY_NUM];

extern uint32_t fezui_keytotalcounts[MAIN_KEY_NUM];
extern uint32_t fezui_keyinitcounts[MAIN_KEY_NUM];
extern uint32_t fezui_fps;
extern uint8_t fezui_is_updating;
extern uint8_t fezui_kps;
extern uint8_t KPS_history_max;
extern char fpsstr[STRING_LENGTH];
extern lefl_loop_array_t KPS_history;
extern uint8_t UI_KPSMaximumPerSecond;
extern uint8_t UI_IsDisplayOn;
extern char fezui_tempstr[STRING_LENGTH];
extern uint8_t fezui_debug;
extern uint8_t cmd_buffer;

extern uint32_t fezui_run_time;


extern lefl_loop_array_t analog_historys[4];
extern uint8_t analog_history_buffer[4];

extern lefl_bit_array_t lines[4];
extern lefl_loop_array_t KPS_queue;

extern lefl_animation_base_t animations[4];
extern uint8_t wheelcount;


void fezui_draw_cursor(lefl_cursor_t*c);
void Analog_Read();
void fezui_read_counts();
void fezui_save_counts();


extern lefl_link_frame_t mainframe;

extern lefl_page_t homepage;
void homepage_logic(lefl_page_t *page);
void homepage_draw(lefl_page_t *page);
void homepage_load(lefl_page_t *page);

extern lefl_page_t menupage;
void menupage_logic(lefl_page_t *page);
void menupage_draw(lefl_page_t *page);
void menupage_load(lefl_page_t *page);
void main_menu_cb(lefl_menu_t *menu);

extern lefl_page_t settingspage;
void settingspage_logic(lefl_page_t *page);
void settingspage_draw(lefl_page_t *page);
void settingspage_load(lefl_page_t *page);
void settings_menu_cb(lefl_menu_t *menu);

extern lefl_page_t oscilloscopepage;
void oscilloscopepage_logic(lefl_page_t *page);
void oscilloscopepage_draw(lefl_page_t *page);
void oscilloscopepage_load(lefl_page_t *page);

extern lefl_page_t keyselectpage;
void keyselectpage_logic(lefl_page_t *page);
void keyselectpage_draw(lefl_page_t *page);
void keyselectpage_load(lefl_page_t *page);

extern lefl_page_t keyconfigpage;
void keyconfigpage_logic(lefl_page_t *page);
void keyconfigpage_draw(lefl_page_t *page);


extern lefl_page_t debugpage;
void debugpage_logic(lefl_page_t *page);
void debugpage_draw(lefl_page_t *page);
void debugpage_load(lefl_page_t *page);

extern lefl_page_t calibrationpage;
void calibrationpage_logic(lefl_page_t *page);
void calibrationpage_draw(lefl_page_t *page);
void calibrationpage_load(lefl_page_t *page);

extern lefl_page_t statisticpage;
void statisticpage_logic(lefl_page_t *page);
void statisticpage_draw(lefl_page_t *page);
void statisticpage_load(lefl_page_t *page);

extern lefl_page_t aboutpage;
void aboutpage_logic(lefl_page_t *page);
void aboutpage_draw(lefl_page_t *page);
void aboutpage_load(lefl_page_t *page);

#endif /* FEZUI_CONFIG_H_ */
