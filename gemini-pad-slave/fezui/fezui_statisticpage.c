/*
 * fezui_statisticpage.c
 *
 *  Created on: Jun 25, 2023
 *      Author: xq123
 */
#include "fezui.h"
#include "fezui_var.h"
#include "communication.h"

#define ROW_HEIGHT 10
#define KEY_WIDTH 5

lefl_page_t statisticpage={statisticpage_logic,statisticpage_draw,statisticpage_load};

static fezui_scrollview_t scrollview =
{
    .content_height=100,
    .content_width=64,
    .ordinate=0
};

static float target_ordinate=0;

void statisticpage_logic(void *page)
{
    lefl_easing_pid(&(scrollview.ordinate), target_ordinate);
}
void statisticpage_draw(void *page)
{


    u8g2_SetFont(&(fezui.u8g2), u8g2_font_helvB08_tr);
    u8g2_DrawStr(&(fezui.u8g2),0,ROW_HEIGHT*7-(u8g2_int_t)(scrollview.ordinate),"- System");
    u8g2_DrawStr(&(fezui.u8g2),0,ROW_HEIGHT*1-(u8g2_int_t)(scrollview.ordinate),"- Total hits");

    u8g2_SetFont(&(fezui.u8g2), u8g2_font_5x8_mr);


    u8g2_DrawStr(&(fezui.u8g2),0,ROW_HEIGHT*2-(u8g2_int_t)(scrollview.ordinate),"  KEY1");

    u8g2_DrawStr(&(fezui.u8g2),0,ROW_HEIGHT*3-(u8g2_int_t)(scrollview.ordinate),"  KEY2");

    u8g2_DrawStr(&(fezui.u8g2),0,ROW_HEIGHT*4-(u8g2_int_t)(scrollview.ordinate),"  KEY3");

    u8g2_DrawStr(&(fezui.u8g2),0,ROW_HEIGHT*5-(u8g2_int_t)(scrollview.ordinate),"  KEY4");

    u8g2_DrawStr(&(fezui.u8g2),0,ROW_HEIGHT*6-(u8g2_int_t)(scrollview.ordinate),"  KEY4");


    u8g2_DrawStr(&(fezui.u8g2),0,ROW_HEIGHT*8-(u8g2_int_t)(scrollview.ordinate),"  Run time");

    sprintf(fezui_buffer,"%02ldh%02ldm%02lds",fezui_run_time/3600,fezui_run_time/60%60,fezui_run_time%60);
    u8g2_DrawStr(&(fezui.u8g2),WIDTH-KEY_WIDTH*10,ROW_HEIGHT*8-(u8g2_int_t)(scrollview.ordinate),fezui_buffer);

    u8g2_DrawStr(&(fezui.u8g2),0,ROW_HEIGHT*9-(u8g2_int_t)(scrollview.ordinate),"  Temperature");

    //double temp = (((( ((int32_t)(((((((fezui_temp_raw))) << ((((((0x00000000UL))))) >> (((3U)) - 1UL))) >> (((0x00000000UL)) >> (((3U)) - 1UL))) * ((3324))) / (3000.0)) - (int32_t) *((uint16_t*) (0x1FFF75A8UL)))) * (int32_t)((130L) - (30L))) / (double)((int32_t)*((uint16_t*) (0x1FFF75CAUL)) - (int32_t)*((uint16_t*)(0x1FFF75A8UL)))) + (30L));
    //sprintf(fezui_buffer,"%4.2lfC", temp);
    sprintf(fezui_buffer,"%2ldC",__HAL_ADC_CALC_TEMPERATURE(3324,fezui_temp_raw,ADC_RESOLUTION_12B));
    //sprintf(fezui_buffer,"%d",fezui_temp_raw);
    u8g2_DrawStr(&(fezui.u8g2),WIDTH-KEY_WIDTH*4,ROW_HEIGHT*9-(u8g2_int_t)(scrollview.ordinate),fezui_buffer);

//    /u8g2_SetFont(&(fezui.u8g2), led_seg_like_font);


    sprintf(fezui_buffer,"%8ld",fezui_keytotalcounts[0]);
    u8g2_DrawStr(&(fezui.u8g2),WIDTH-KEY_WIDTH*9,ROW_HEIGHT*2-(u8g2_int_t)(scrollview.ordinate),fezui_buffer);

    sprintf(fezui_buffer,"%8ld",fezui_keytotalcounts[1]);
    u8g2_DrawStr(&(fezui.u8g2),WIDTH-KEY_WIDTH*9,ROW_HEIGHT*3-(u8g2_int_t)(scrollview.ordinate),fezui_buffer);

    sprintf(fezui_buffer,"%8ld",fezui_keytotalcounts[2]);
    u8g2_DrawStr(&(fezui.u8g2),WIDTH-KEY_WIDTH*9,ROW_HEIGHT*4-(u8g2_int_t)(scrollview.ordinate),fezui_buffer);

    sprintf(fezui_buffer,"%8ld",fezui_keytotalcounts[3]);
    u8g2_DrawStr(&(fezui.u8g2),WIDTH-KEY_WIDTH*9,ROW_HEIGHT*5-(u8g2_int_t)(scrollview.ordinate),fezui_buffer);



    fezui_draw_scrollview(&fezui, 0, 0, 128, 64, &scrollview);
}

void statisticpage_load(void *page)
{
    lefl_key_attach(keys + 2, KEY_DOWN, lambda(void,(void*k){lefl_link_frame_go_back(&mainframe);lefl_cursor_set(&cursor ,0 ,0 ,WIDTH ,HEIGHT);}));
    lefl_key_attach(keys + 3, KEY_DOWN, NULL);
    lefl_key_attach(keys + 4, KEY_DOWN, lambda(void,(void*k){target_ordinate+=10;if(target_ordinate+64>scrollview.content_height)target_ordinate=scrollview.content_height-64;}));
    lefl_key_attach(keys + 5, KEY_DOWN, lambda(void,(void*k){target_ordinate-=10;if(target_ordinate<0)target_ordinate=0;}));
    lefl_key_attach(keys + 6, KEY_DOWN, lambda(void,(void*k){target_ordinate+=10;if(target_ordinate+64>scrollview.content_height)target_ordinate=scrollview.content_height-64;}));
    lefl_key_attach(keys + 7, KEY_DOWN, lambda(void,(void*k){target_ordinate-=10;if(target_ordinate<0)target_ordinate=0;}));
}
