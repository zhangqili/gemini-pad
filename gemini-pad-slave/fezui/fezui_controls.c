/*
 * fez_ui_controls.c
 *
 *  Created on: 2023年6月19日
 *      Author: xq123
 */

#include "fezui.h"

void fezui_draw_flowingwater(u8g2_t *u8g2_ptr, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w,
        u8g2_uint_t h, lefl_bit_array_t *bits)
{
    for (uint8_t i=0;i<w;i++)
    {
        //if (lefl_bit_array_get(bits, i))
        //  u8g2_DrawVLine(&u8g2,x+i,y,h);
        if (lefl_bit_array_get(bits, i))
          u8g2_DrawVLine(&u8g2,x+i,y+1,h-2);
        if (lefl_bit_array_get(bits, i)^lefl_bit_array_get(bits, i+1))
          u8g2_DrawVLine(&u8g2,x+i,y,h);
    }
}


extern fezui_t ui;
void fezui_draw_wave(u8g2_t *u8g2_ptr, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w,
        u8g2_uint_t h, lefl_loop_array_t *arr, lefl_bit_array_t *l)
{
    uint8_t y1;
    uint8_t y2;
    for (int8_t i = 0; i < w - 1; i++)
    {
        y1=lefl_loop_array_get(arr, i)/128;
        y2=lefl_loop_array_get(arr, i+1)/128;
        if (y1 > h || y2 > h)
            if (!lefl_bit_array_get(l, i))
                u8g2_DrawLine(u8g2_ptr, x + w - i - 1, y + 1,x + w - i - 2,y+1);
            else
            {
                u8g2_DrawVLine(u8g2_ptr, x + w - i - 1, y + i, h - 1);
                u8g2_DrawLine(u8g2_ptr, x + w - i - 1, y + 1,x + w - i - 2,y+1);
            }
        else if (lefl_bit_array_get(l, i))
        {
            u8g2_DrawVLine(u8g2_ptr, x + w - i - 1, y + h - y1, y1);
            u8g2_DrawLine(u8g2_ptr, x + w - i - 1, y + h - y1,x + w - i - 2,y+h-y2);
        }
        else
            u8g2_DrawLine(u8g2_ptr, x + w - i - 1, y + h-y1,x + w - i - 2,y+h-y2);
    }
    u8g2_SetFont(u8g2_ptr, u8g2_font_micro_tr);
    u8g2_DrawBox(&u8g2, x, y, 17, 7);
    u8g2_SetDrawColor(&u8g2, 2);
    sprintf(fezui_tempstr, "%04d", lefl_loop_array_get(arr, 0));
    u8g2_DrawStr(u8g2_ptr, x + 1, y + 6, fezui_tempstr);
    u8g2_SetDrawColor(&u8g2, !ui.invert);
    //u8g2_DrawButtonUTF8(&u8g2, x+1, y+6, U8G2_BTN_INV, 2, 1, 1, UI_TempString);
}

void fezui_draw_chart(u8g2_t *u8g2_ptr, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w,
        u8g2_uint_t h, lefl_loop_array_t *arr, uint8_t max)
{
    float y1;
    float y2;
    float ymax = (float)max;
    for (int8_t i = 0; i < w; i++)
    {
        y1=lefl_loop_array_get(arr, i);
        y2=lefl_loop_array_get(arr, i+1);

        u8g2_DrawLine(u8g2_ptr, x + w - i,
            h + y - (uint8_t) ((float) (h - 1) * (y1 / ymax)),
            x + w - i - 1,
            h + y - (uint8_t) ((float) (h - 1) * (y2 / ymax)));
    }
}

void fezui_veil(u8g2_t *u8g2_ptr, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w,
        u8g2_uint_t h, uint8_t level, uint8_t color)
{
	uint8_t previous_color;
	previous_color = u8g2_GetDrawColor(u8g2_ptr);
    u8g2_SetDrawColor(&u8g2, color);
    switch(level)
    {
        case 0:
            break;
        case 2:
            for (u8g2_uint_t i = y + 2; i < y+h; i+=4)
            {
                for (u8g2_uint_t j = x + 2; j < x+w; j+=4)
                {
                    u8g2_DrawPixel(u8g2_ptr, j, i);
                }
            }
        case 1:
            for (u8g2_uint_t i = y; i < y+h; i+=4)
            {
                for (u8g2_uint_t j = x; j < x+w; j+=4)
                {
                    u8g2_DrawPixel(u8g2_ptr, j, i);
                }
            }
            break;
        case 6:
            for (u8g2_uint_t i = y; i < y+h; i+=2)
            {
                for (u8g2_uint_t j = x+1; j < x+w; j+=2)
                {
                    u8g2_DrawPixel(u8g2_ptr, j, i);
                }
            }
        case 5:
            for (u8g2_uint_t i = y+1; i < y+h; i+=2)
            {
                for (u8g2_uint_t j = x; j < x+w; j+=2)
                {
                    u8g2_DrawPixel(u8g2_ptr, j, i);
                }
            }
        case 4:
            for (u8g2_uint_t i = y+1; i < y+h; i+=2)
            {
                for (u8g2_uint_t j = x+1; j < x+w; j+=2)
                {
                    u8g2_DrawPixel(u8g2_ptr, j, i);
                }
            }
        case 3:
            for (u8g2_uint_t i = y; i < y+h; i+=2)
            {
                for (u8g2_uint_t j = x; j < x+w; j+=2)
                {
                    u8g2_DrawPixel(u8g2_ptr, j, i);
                }
            }
            break;
        case 7:
            u8g2_DrawBox(u8g2_ptr, x, y, w, h);
            break;
        default:
            break;
    }
	u8g2_SetDrawColor(u8g2_ptr,previous_color);
}

void fezui_slider_increase(fezui_slider_t *slider, int8_t n)
{
    *(slider->f_ptr)+=slider->interval*n;
    if(*(slider->f_ptr)>slider->max)
        *(slider->f_ptr)=slider->max;
    if(*(slider->f_ptr)<slider->min)
        *(slider->f_ptr)=slider->min;
}

void fezui_draw_slider(u8g2_t *u8g2_ptr, uint8_t x, uint8_t y, uint8_t w, uint8_t h, fezui_slider_t *slider)
void fezui_draw_slider(u8g2_t *u8g2_ptr, uint8_t x, uint8_t y, uint8_t w, uint8_t h, fezui_slider_t *slider)
{
	if(slider->orientation == ORIENTATION_HORIZAIONTAL)
	{
		u8g2_DrawHLine(u8g2_ptr, x+1, y+2, w-2);
		u8g2_DrawBox(u8g2_ptr, x + ((*(slider->f_ptr)-slider->min)/slider->max-slider->min)*(w-2), y, 3, 5);
	}
	else
	{
		u8g2_DrawVLine(u8g2_ptr, x+2, y+1, h-2);
		u8g2_DrawBox(u8g2_ptr, x , y + ((slider->max-*(slider->f_ptr))/slider->max-slider->min)*(h-2), 5, 3);
	}
}
