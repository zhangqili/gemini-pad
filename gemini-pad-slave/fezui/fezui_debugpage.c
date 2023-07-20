/*
 * fezui_debugpage.c
 *
 *  Created on: 2023年6月24日
 *      Author: xq123
 */
#include "fezui.h"
#include "communication.h"

lefl_page_t debugpage={debugpage_logic,debugpage_draw,debugpage_load};

void debugpage_logic(lefl_page_t *page)
{

}
void debugpage_draw(lefl_page_t *page)
{
    u8g2_SetFont(&u8g2, u8g2_font_freedoomr10_tu);
    sprintf(fezui_tempstr,"%d", Communication_RX_Count);
    u8g2_DrawStr(&u8g2, 0, 15, comstr);
    sprintf(fezui_tempstr,"%f",advanced_keys[1].raw);
    u8g2_DrawStr(&u8g2, 0, 30, fezui_tempstr);
    sprintf(fezui_tempstr,"%f",advanced_keys[2].raw);
    u8g2_DrawStr(&u8g2, 0, 45, fezui_tempstr);
    sprintf(fezui_tempstr,"%f",advanced_keys[3].raw);
    u8g2_DrawStr(&u8g2, 0, 60, fezui_tempstr);
}

void debugpage_load(lefl_page_t *page)
{
    keys[2].key_cb=lambda(void,(lefl_key_t*k){lefl_link_frame_go_back(&mainframe);lefl_cursor_set(&cursor ,0 ,0 ,WIDTH ,HEIGHT);});
    keys[3].key_cb=NULL;
    keys[4].key_cb=NULL;
    keys[5].key_cb=NULL;
    keys[6].key_cb=NULL;
    keys[7].key_cb=NULL;
}

