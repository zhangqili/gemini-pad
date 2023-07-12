/*
 * fezui_statisticpage.c
 *
 *  Created on: Jun 25, 2023
 *      Author: xq123
 */
#include "fezui.h"
#include "communication.h"

lefl_page_t statisticpage={statisticpage_logic,statisticpage_draw,statisticpage_load};

void statisticpage_logic(lefl_page_t *page)
{

}
void statisticpage_draw(lefl_page_t *page)
{
    u8g2_SetFont(&u8g2, u8g2_font_6x13_tf);

    sprintf(fezui_tempstr,"%s","Total hits");
    u8g2_DrawStr(&u8g2,0,10*1,fezui_tempstr);

    sprintf(fezui_tempstr,"%s","KEY1");
    u8g2_DrawStr(&u8g2,0,10*2,fezui_tempstr);

    sprintf(fezui_tempstr,"%s","KEY2");
    u8g2_DrawStr(&u8g2,0,10*3,fezui_tempstr);

    sprintf(fezui_tempstr,"%s","KEY3");
    u8g2_DrawStr(&u8g2,0,10*4,fezui_tempstr);

    sprintf(fezui_tempstr,"%s","KEY4");
    u8g2_DrawStr(&u8g2,0,10*5,fezui_tempstr);


    u8g2_SetFont(&u8g2, led_seg_like_font);

    sprintf(fezui_tempstr,"%8ld",fezui_keytotalcounts[0]);
    u8g2_DrawStr(&u8g2,WIDTH-6*9,10*2,fezui_tempstr);

    sprintf(fezui_tempstr,"%8ld",fezui_keytotalcounts[1]);
    u8g2_DrawStr(&u8g2,WIDTH-6*9,10*3,fezui_tempstr);

    sprintf(fezui_tempstr,"%8ld",fezui_keytotalcounts[2]);
    u8g2_DrawStr(&u8g2,WIDTH-6*9,10*4,fezui_tempstr);

    sprintf(fezui_tempstr,"%8ld",fezui_keytotalcounts[3]);
    u8g2_DrawStr(&u8g2,WIDTH-6*9,10*5,fezui_tempstr);
}

void statisticpage_load(lefl_page_t *page)
{
    keys[2].key_cb=lambda(void,(lefl_key_t*k){lefl_link_frame_go_back(&mainframe);lefl_cursor_set(&cursor ,0 ,0 ,WIDTH ,HEIGHT);});
    keys[3].key_cb=lambda(void,(lefl_key_t*k){;});
    keys[4].key_cb=lambda(void,(lefl_key_t*k){;});
    keys[5].key_cb=lambda(void,(lefl_key_t*k){;});
    keys[6].key_cb=lambda(void,(lefl_key_t*k){;});
    keys[7].key_cb=lambda(void,(lefl_key_t*k){;});
}
