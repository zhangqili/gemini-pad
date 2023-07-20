/*
 * fez_ui.h
 *
 *  Created on: 2023年6月18日
 *      Author: xq123
 */

#ifndef FEZUI_H_
#define FEZUI_H_

#include "display.h"
#include "lefl.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "fezui_config.h"
#include "fezui_interface.h"

typedef uint8_t fezui_uint_t;
typedef int8_t fezui_int_t;

extern char fezui_buffer[STRING_LENGTH];

typedef struct __fezui_t
{
	u8g2_t u8g2;
    uint16_t width;
    uint16_t height;
    bool invert;
} fezui_t;

void fezui_timer_handler();
void fezui_init();

typedef struct __fezui_point_t
{
    fezui_uint_t x;
    fezui_uint_t y;
} fezui_point_t;

typedef struct __fezui_size_t
{
    fezui_uint_t w;
    fezui_uint_t h;
} fezui_size_t;


typedef struct __fezui_base_t
{
    fezui_point_t location;
    fezui_size_t size;
} fezui_base_t;

/*
 * fezui_interface.c
 */
/*
 uint8_t ui_init();
 void fezui_clear_buf();
 void fezui_send_buf();
 void fezui_draw_rectangle(uint16_t x,uint16_t y,uint16_t w,uint16_t h,bool fill);
 void fezui_draw_pixel(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
 void fezui_draw_line(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
 */

/*
 * fezui_controls.c
 */
void fezui_draw_flowingwater(u8g2_t *u8g2_ptr, u8g2_uint_t x, u8g2_uint_t y,
        u8g2_uint_t w, u8g2_uint_t h, lefl_bit_array_t *bits);
void fezui_draw_wave(u8g2_t *u8g2_ptr, u8g2_uint_t x, u8g2_uint_t y,
        u8g2_uint_t w, u8g2_uint_t h, lefl_loop_array_t *arr,
        lefl_bit_array_t *l);
void fezui_draw_chart(u8g2_t *u8g2_ptr, u8g2_uint_t x, u8g2_uint_t y,
        u8g2_uint_t w, u8g2_uint_t h, lefl_loop_array_t *arr, uint8_t max);
void fezui_veil(u8g2_t *u8g2_ptr, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w,
        u8g2_uint_t h, uint8_t level, uint8_t color);

typedef enum
{
	ORIENTATION_HORIZAIONTAL,
	ORIENTATION_VERTICAL
} fezui_orientation_t;

typedef struct __fezui_slider_t
{
    //fezui_base_t base;
    //fezui_base_t base;
    float max;
    float min;
    float interval;
    float *f_ptr;
    fezui_orientation_t orientation;
} fezui_slider_t;

void fezui_slider_increase(fezui_slider_t *slider, int8_t n);
void fezui_draw_slider(u8g2_t *u8g2_ptr, uint8_t x, uint8_t y, uint8_t w,uint8_t h, fezui_slider_t *slider);

typedef struct __fezui_tile_t
{
    char *header;
    char *icon;
    void (*tile_cb)(struct __fezui_tile_t *tile);
} fezui_tile_t;

/*
 * fezui_dialog.c
 */

typedef enum
{
	DIALOG_NORMAL,
	DIALOG_WARNING,
	DIALOG_ERROR,
} fezui_dialog_type_t;

typedef struct __fezui_dialog_t
{
    char *title;
    float *text;
    fezui_dialog_type_t type;
} fezui_dialog_t;

void fezui_draw_dialog(u8g2_t *u8g2_ptr, uint8_t x, uint8_t y, uint8_t w, uint8_t h, fezui_dialog_t *dialog);


#endif /* FEZUI_H_ */
