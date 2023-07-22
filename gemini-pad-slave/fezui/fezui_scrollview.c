/*
 * fezui_scrollviewer.c
 *
 *  Created on: Jul 21, 2023
 *      Author: xq123
 */
#include "fezui.h"

void fezui_draw_scrollview(fezui_t *fezui_ptr, uint8_t x, uint8_t y, fezui_scrollview_t* scrollview)
{
    if(scrollview->content_width>scrollview->width)
        fezui_draw_scrollbar(fezui_ptr, x, y + scrollview->height - 5, scrollview->width - 5, 5, (float)scrollview->width/(float)scrollview->content_width, (float)scrollview->abscissa/(float)(scrollview->content_width-scrollview->width), ORIENTATION_HORIZAIONTAL);
    if(scrollview->content_height>scrollview->height)
        fezui_draw_scrollbar(fezui_ptr, x + scrollview->width - 5, y, 5, scrollview->height-5, (float)scrollview->height/(float)scrollview->content_height, (float)scrollview->ordinate/(float)(scrollview->content_height-scrollview->height), ORIENTATION_VERTICAL);
}
