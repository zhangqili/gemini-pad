/*
 * fezui_calibrationpage.c
 *
 *  Created on: 2023年6月24日
 *      Author: xq123
 */

#include "fezui.h"
#include "communication.h"
#include "usart.h"

lefl_page_t calibrationpage={calibrationpage_logic,calibrationpage_draw,calibrationpage_load};

lefl_menu_t calibrationmenu={
        .items={"KEY1","KEY2","KEY3","KEY4"},
        .len=4,
        .selected_index=0,
};

uint8_t calibrationstate=0;

void drawrawdata(uint8_t x, uint8_t y,uint8_t n)
{
    u8g2_SetFont(&u8g2, u8g2_font_4x6_mr);

    sprintf(fezui_tempstr,"state:%d",advanced_keys[n].state);
    u8g2_DrawStr(&u8g2, x, y+7*1, fezui_tempstr);

    sprintf(fezui_tempstr,"value:%.3f",advanced_keys[n].value);
    u8g2_DrawStr(&u8g2, x, y+7*2, fezui_tempstr);

    sprintf(fezui_tempstr,"mode:%d",advanced_keys[n].mode);
    u8g2_DrawStr(&u8g2, x, y+7*3, fezui_tempstr);

    sprintf(fezui_tempstr,"distance:(%.3f, %.3f)",advanced_keys[n].trigger_distance, advanced_keys[n].release_distance);
    u8g2_DrawStr(&u8g2, x, y+7*4, fezui_tempstr);

    sprintf(fezui_tempstr,"speed:(%.3f, %.3f)",advanced_keys[n].trigger_speed,advanced_keys[n].release_speed);
    u8g2_DrawStr(&u8g2, x, y+7*5, fezui_tempstr);

    sprintf(fezui_tempstr,"deadzone:(%.3f, %.3f)",advanced_keys[n].upper_deadzone, advanced_keys[n].lower_deadzone);
    u8g2_DrawStr(&u8g2, x, y+7*6, fezui_tempstr);

    sprintf(fezui_tempstr,"bound:(%.3f, %.3f)",advanced_keys[n].upper_bound, advanced_keys[n].lower_bound);
    u8g2_DrawStr(&u8g2, x, y+7*7, fezui_tempstr);

    sprintf(fezui_tempstr,"range:%.3f",advanced_keys[n].range);
    u8g2_DrawStr(&u8g2, x, y+7*8, fezui_tempstr);

}

void calibrationpage_logic(lefl_page_t *page)
{
    if(cmd_buffer!=CMD_NULL)
    {
        calibrationstate=cmd_buffer;
        if(cmd_buffer==CMD_CALIBRATION_END)
            Analog_Read();
        cmd_buffer=CMD_NULL;
    }
    for (uint8_t i = 0; i < MAIN_KEY_NUM; i++)
    {
        advanced_keys[i].value=(float)analog_history_buffer[i]/255.0;
    }
    lefl_cursor_set(
            &target_cursor ,
            100,
            0 ,
            28,
            9);
}

void calibrationpage_draw(lefl_page_t *page)
{
    switch(calibrationstate)
    {
    case CMD_CALIBRATION_START:
    case CMD_CALIBRATION_UP:
        u8g2_SetFont(&u8g2, u8g2_font_4x6_mr);
        sprintf(fezui_tempstr, "Leave alone the keys");
        u8g2_DrawStr(&u8g2, 0, 7, fezui_tempstr);
        sprintf(fezui_tempstr, "until light up.");
        u8g2_DrawStr(&u8g2, 0, 14, fezui_tempstr);
        break;
    case CMD_CALIBRATION_DOWN:
        u8g2_SetFont(&u8g2, u8g2_font_4x6_mr);
        sprintf(fezui_tempstr, "Press all the keys");
        u8g2_DrawStr(&u8g2, 0, 7, fezui_tempstr);
        sprintf(fezui_tempstr, "to the bottom right now!");
        u8g2_DrawStr(&u8g2, 0, 14, fezui_tempstr);
        break;
    case CMD_CALIBRATION_END:
        drawrawdata(0, 8, calibrationmenu.selected_index);
        u8g2_SetFont(&u8g2, u8g2_font_4x6_mr);
        //u8g2_DrawBox(&u8g2, x, y, 13, 7);
        //u8g2_SetDrawColor(&u8g2, 2);
        sprintf(fezui_tempstr, "Calibration over.");
        u8g2_DrawStr(&u8g2, 0, 7, fezui_tempstr);
        sprintf(fezui_tempstr, "<%s>", calibrationmenu.items[calibrationmenu.selected_index]);
        u8g2_DrawStr(&u8g2, 102, 7, fezui_tempstr);
        //u8g2_SetDrawColor(&u8g2, 1);
        fezui_draw_cursor(&cursor);
        break;
    default:
        drawrawdata(0, 8, calibrationmenu.selected_index);
        u8g2_SetFont(&u8g2, u8g2_font_4x6_mr);
        //u8g2_DrawBox(&u8g2, x, y, 13, 7);
        //u8g2_SetDrawColor(&u8g2, 2);
        sprintf(fezui_tempstr, "Press OK to start");
        u8g2_DrawStr(&u8g2, 0, 7, fezui_tempstr);
        sprintf(fezui_tempstr, "<%s>", calibrationmenu.items[calibrationmenu.selected_index]);
        u8g2_DrawStr(&u8g2, 102, 7, fezui_tempstr);
        //u8g2_SetDrawColor(&u8g2, 1);
        fezui_draw_cursor(&cursor);
        break;
    }
}

void calibrationpage_load(lefl_page_t *page)
{
    calibrationstate=0;
    keys[6].key_cb=lambda(void,(lefl_key_t*k){;});
    keys[7].key_cb=lambda(void,(lefl_key_t*k){;});
    keys[2].key_cb=lambda(void,(lefl_key_t*k){lefl_link_frame_go_back(&mainframe);});
    keys[3].key_cb=lambda(void,(lefl_key_t*k){Communication_Add8(PROTOCOL_CMD,CMD_CALIBRATION_START);
                                                Communication_Transmit();
                                                calibrationstate=CMD_CALIBRATION_START;});
    keys[4].key_cb=lambda(void,(lefl_key_t*k){lefl_menu_index_increase(&calibrationmenu, 1);});
    keys[5].key_cb=lambda(void,(lefl_key_t*k){lefl_menu_index_increase(&calibrationmenu, -1);});
    keys[6].key_cb=lambda(void,(lefl_key_t*k){lefl_menu_index_increase(&calibrationmenu, 1);});
    keys[7].key_cb=lambda(void,(lefl_key_t*k){lefl_menu_index_increase(&calibrationmenu, -1);});
}
