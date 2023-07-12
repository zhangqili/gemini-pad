/*
 * fez_ui_controls.c
 *
 *  Created on: 2023年6月19日
 *      Author: xq123
 */

#include "fezui.h"

void fezui_draw_wave(u8g2_t *u8g2_ptr, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w,
        u8g2_uint_t h, lefl_loop_array_t *arr, lefl_bit_array_t *l)
{
    uint8_t y1;
    uint8_t y2;
    for (int8_t i = 0; i < w - 1; i++)
    {
        y1=lefl_loop_array_get(arr, i)/8;
        y2=lefl_loop_array_get(arr, i+1)/8;
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
            u8g2_DrawVLine(u8g2_ptr, x + w - i - 1, y + y1, h - y1);
            u8g2_DrawLine(u8g2_ptr, x + w - i - 1, y + y1,x + w - i - 2,y+y2);
        }
        else
            u8g2_DrawLine(u8g2_ptr, x + w - i - 1, y + y1,x + w - i - 2,y+y2);
    }
    u8g2_SetFont(u8g2_ptr, u8g2_font_micro_tr);
    u8g2_DrawBox(&u8g2, x, y, 13, 7);
    u8g2_SetDrawColor(&u8g2, 2);
    sprintf(fezui_tempstr, "%03d", lefl_loop_array_get(arr, 0));
    u8g2_DrawStr(u8g2_ptr, x + 1, y + 6, fezui_tempstr);
    u8g2_SetDrawColor(&u8g2, 1);
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
