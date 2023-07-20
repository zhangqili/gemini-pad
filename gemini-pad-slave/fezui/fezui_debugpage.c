/*
 * fezui_debugpage.c
 *
 *  Created on: 2023年6月24日
 *      Author: xq123
 */
#include "fezui.h"
#include "communication.h"

lefl_page_t debugpage={debugpage_logic,debugpage_draw,debugpage_load};

static float targetnum = 50;
fezui_slider_t slider =
{
	.interval=1,
	.max=100,
	.min=0,
	.f_ptr=&targetnum,
	.orientation=ORIENTATION_VERTICAL
};

void debugpage_logic(lefl_page_t *page)
{

}
void debugpage_draw(lefl_page_t *page)
{
	fezui_veil(&u8g2, 0, 0, 128, 64, 4, 0);
	fezui_draw_dialog(&u8g2, 32, 16, 64, 32, NULL);
	fezui_draw_slider(&u8g2, 64, 16+2, 64-4, 20, &slider);
    u8g2_SetFont(&u8g2, u8g2_font_freedoomr10_tu);
    sprintf(fezui_tempstr,"%f", targetnum);
    u8g2_DrawStr(&u8g2, 0, 64, fezui_tempstr);
}

void debugpage_load(lefl_page_t *page)
{
    keys[2].key_cb=lambda(void,(lefl_key_t*k){lefl_link_frame_go_back(&mainframe);lefl_cursor_set(&cursor ,0 ,0 ,WIDTH ,HEIGHT);});
    keys[3].key_cb=NULL;
    keys[4].key_cb=lambda(void,(lefl_key_t*k){fezui_slider_increase(&slider, 1);});
    keys[5].key_cb=lambda(void,(lefl_key_t*k){fezui_slider_increase(&slider, -1);});
    keys[6].key_cb=lambda(void,(lefl_key_t*k){fezui_slider_increase(&slider, 1);});
    keys[7].key_cb=lambda(void,(lefl_key_t*k){fezui_slider_increase(&slider, -1);});
}

