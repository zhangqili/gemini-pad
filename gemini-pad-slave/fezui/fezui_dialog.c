/*
 * fezui_dialog.c
 *
 *  Created on: Jul 20, 2023
 *      Author: xq123
 */
#include "fezui.h"

void fezui_draw_dialog(u8g2_t *u8g2_ptr, uint8_t x, uint8_t y, uint8_t w, uint8_t h, fezui_dialog_t *dialog)
{
	uint8_t previous_color;
	previous_color = u8g2_GetDrawColor(u8g2_ptr);
	u8g2_SetDrawColor(u8g2_ptr,1);
	u8g2_DrawBox(u8g2_ptr, x, y, w, h);

	u8g2_SetDrawColor(u8g2_ptr,0);
	u8g2_DrawFrame(u8g2_ptr, x, y, w, h);

	u8g2_SetDrawColor(u8g2_ptr,previous_color);
}
