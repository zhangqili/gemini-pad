/*
 * fezui_debugpage.c
 *
 *  Created on: 2023年6月24日
 *      Author: xq123
 */
#include "fezui.h"
#include "fezui_var.h"
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

static fezui_scrollview_t scrollview =
{
    .content_height=120,
    .content_width=250,
    .abscissa=0,
    .ordinate=0
};

void debugpage_logic(lefl_page_t *page)
{

}
void debugpage_draw(lefl_page_t *page)
{
	//fezui_veil(&(fezui), 0, 0, 128, 64, 4, 0);
	//fezui_draw_dialog(&(fezui), 32, 16, 64, 32, NULL);
	fezui_draw_slider(&(fezui), 64-(u8g2_int_t)scrollview.abscissa, 16+2-(u8g2_int_t)scrollview.ordinate , 5, 20, &slider);
    u8g2_SetFont(&(fezui.u8g2), u8g2_font_freedoomr10_tu);
    sprintf(fezui_buffer,"%f", targetnum);
    u8g2_DrawStr(&(fezui.u8g2), 0-(u8g2_int_t)scrollview.abscissa, 64- (u8g2_int_t)scrollview.ordinate, fezui_buffer);
    u8g2_DrawStr(&(fezui.u8g2), 10-(u8g2_int_t)scrollview.abscissa, 10- (u8g2_int_t)scrollview.ordinate, "123");
    u8g2_DrawBox(&(fezui.u8g2), 70-(u8g2_int_t)scrollview.abscissa, 5- (u8g2_int_t)scrollview.ordinate, 10, 10);
    u8g2_DrawHLine(&(fezui.u8g2), 3-(u8g2_int_t)scrollview.abscissa, 40- (u8g2_int_t)scrollview.ordinate, 100);
    fezui_draw_scrollview(&fezui, 0, 0, 128, 64, &scrollview);
}

void debugpage_load(lefl_page_t *page)
{
    keys[2].key_cb=lambda(void,(lefl_key_t*k){lefl_link_frame_go_back(&mainframe);lefl_cursor_set(&cursor ,0 ,0 ,WIDTH ,HEIGHT);});
    keys[3].key_cb=NULL;
    keys[4].key_cb=lambda(void,(lefl_key_t*k){fezui_slider_increase(&slider, 1);scrollview.abscissa+=1.0;});
    keys[5].key_cb=lambda(void,(lefl_key_t*k){fezui_slider_increase(&slider, -1);scrollview.abscissa-=1.0;});
    keys[6].key_cb=lambda(void,(lefl_key_t*k){fezui_slider_increase(&slider, 1);scrollview.ordinate+=1.0;});
    keys[7].key_cb=lambda(void,(lefl_key_t*k){fezui_slider_increase(&slider, -1);scrollview.ordinate-=1.0;});
}

