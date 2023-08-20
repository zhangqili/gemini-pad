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
#define BUFFER_LENGTH         64
#define NUMBER_STRING_LENGTH  BUFFER_LENGTH
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


void Analog_Read();
void fezui_read_counts();
void fezui_save_counts();


extern lefl_link_frame_t mainframe;

extern lefl_page_t homepage;
void homepage_logic(void *page);
void homepage_draw(void *page);
void homepage_load(void *page);

extern lefl_page_t menupage;
void menupage_init();
void menupage_logic(void *page);
void menupage_draw(void *page);
void menupage_load(void *page);
void main_menu_cb(void *menu);

extern lefl_page_t settingspage;
void settingspage_init();
void settingspage_logic(void *page);
void settingspage_draw(void *page);
void settingspage_load(void *page);
void settings_menu_cb(void *menu);

extern lefl_page_t oscilloscopepage;
void oscilloscopepage_logic(void *page);
void oscilloscopepage_draw(void *page);
void oscilloscopepage_load(void *page);

extern lefl_page_t keyselectpage;
void keyselectpage_logic(void *page);
void keyselectpage_draw(void *page);
void keyselectpage_load(void *page);

extern lefl_page_t keyconfigpage;
void keyconfigpage_init();
void keyconfigpage_logic(void *page);
void keyconfigpage_draw(void *page);

extern lefl_page_t panelpage;
void panelpage_logic(void *page);
void panelpage_draw(void *page);
void panelpage_load(void *page);

extern lefl_page_t debugpage;
void debugpage_logic(void *page);
void debugpage_draw(void *page);
void debugpage_load(void *page);

extern lefl_page_t calibrationpage;
void calibrationpage_init();
void calibrationpage_logic(void *page);
void calibrationpage_draw(void *page);
void calibrationpage_load(void *page);

extern lefl_page_t statisticpage;
void statisticpage_logic(void *page);
void statisticpage_draw(void *page);
void statisticpage_load(void *page);

extern lefl_page_t aboutpage;
void aboutpage_logic(void *page);
void aboutpage_draw(void *page);
void aboutpage_load(void *page);


#endif /* FEZUI_CONFIG_H_ */
