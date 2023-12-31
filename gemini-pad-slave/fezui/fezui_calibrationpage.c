/*
 * fezui_calibrationpage.c
 *
 *  Created on: 2023年6月24日
 *      Author: xq123
 */

#include "fezui.h"
#include "fezui_var.h"
#include "communication.h"
#include "usart.h"

lefl_page_t calibrationpage={calibrationpage_logic,calibrationpage_draw,calibrationpage_load};

lefl_menu_t calibrationmenu;
const char* calibrationmenu_items[] = {"KEY1","KEY2","KEY3","KEY4"};

uint8_t calibrationstate=0;

void drawrawdata(uint8_t x, uint8_t y,uint8_t n)
{
    u8g2_SetFont(&(fezui.u8g2), u8g2_font_4x6_mr);

    sprintf(fezui_buffer,"state:%d",Keyboard_AdvancedKeys[n].key.state);
    u8g2_DrawStr(&(fezui.u8g2), x, y+7*1, fezui_buffer);

    sprintf(fezui_buffer,"raw:%4.1f",Keyboard_AdvancedKeys[n].raw);
    u8g2_DrawStr(&(fezui.u8g2), x, y+7*2, fezui_buffer);

    sprintf(fezui_buffer,"value:%.3f",Keyboard_AdvancedKeys[n].value);
    u8g2_DrawStr(&(fezui.u8g2), x+64, y+7*2, fezui_buffer);

    sprintf(fezui_buffer,"mode:%d",Keyboard_AdvancedKeys[n].mode);
    u8g2_DrawStr(&(fezui.u8g2), x, y+7*3, fezui_buffer);

    sprintf(fezui_buffer,"distance:(%.3f, %.3f)",Keyboard_AdvancedKeys[n].trigger_distance, Keyboard_AdvancedKeys[n].release_distance);
    u8g2_DrawStr(&(fezui.u8g2), x, y+7*4, fezui_buffer);

    sprintf(fezui_buffer,"speed:(%.3f, %.3f)",Keyboard_AdvancedKeys[n].trigger_speed,Keyboard_AdvancedKeys[n].release_speed);
    u8g2_DrawStr(&(fezui.u8g2), x, y+7*5, fezui_buffer);

    sprintf(fezui_buffer,"deadzone:(%.3f, %.3f)",Keyboard_AdvancedKeys[n].upper_deadzone, Keyboard_AdvancedKeys[n].lower_deadzone);
    u8g2_DrawStr(&(fezui.u8g2), x, y+7*6, fezui_buffer);

    sprintf(fezui_buffer,"bound:(%.3f, %.3f)",Keyboard_AdvancedKeys[n].upper_bound, Keyboard_AdvancedKeys[n].lower_bound);
    u8g2_DrawStr(&(fezui.u8g2), x, y+7*7, fezui_buffer);

    sprintf(fezui_buffer,"range:%.3f",Keyboard_AdvancedKeys[n].range);
    u8g2_DrawStr(&(fezui.u8g2), x, y+7*8, fezui_buffer);

}


void calibrationpage_init()
{
    lefl_menu_init(&calibrationmenu, calibrationmenu_items, sizeof(calibrationmenu_items)/sizeof(const char*), NULL);
}

void calibrationpage_logic(void *page)
{
    if(cmd_buffer!=CMD_NULL)
    {
        calibrationstate=cmd_buffer;
        if(cmd_buffer==CMD_CALIBRATION_END)
            Analog_Read();
        cmd_buffer=CMD_NULL;
    }
    lefl_cursor_set(
            &target_cursor ,
            100,
            0 ,
            28,
            9);
}

void calibrationpage_draw(void *page)
{
    switch(calibrationstate)
    {
    case CMD_CALIBRATION_START:
    case CMD_CALIBRATION_UP:
        u8g2_SetFont(&(fezui.u8g2), u8g2_font_4x6_mr);
        sprintf(fezui_buffer, "Leave alone the keys");
        u8g2_DrawStr(&(fezui.u8g2), 0, 7, fezui_buffer);
        sprintf(fezui_buffer, "until light up.");
        u8g2_DrawStr(&(fezui.u8g2), 0, 14, fezui_buffer);
        break;
    case CMD_CALIBRATION_DOWN:
        u8g2_SetFont(&(fezui.u8g2), u8g2_font_4x6_mr);
        sprintf(fezui_buffer, "Press all the keys");
        u8g2_DrawStr(&(fezui.u8g2), 0, 7, fezui_buffer);
        sprintf(fezui_buffer, "to the bottom right now!");
        u8g2_DrawStr(&(fezui.u8g2), 0, 14, fezui_buffer);
        break;
    case CMD_CALIBRATION_END:
        drawrawdata(0, 8, calibrationmenu.selected_index);
        u8g2_SetFont(&(fezui.u8g2), u8g2_font_4x6_mr);
        //u8g2_DrawBox(&(fezui.u8g2), x, y, 13, 7);
        //u8g2_SetDrawColor(&(fezui.u8g2), 2);
        sprintf(fezui_buffer, "Calibration over.");
        u8g2_DrawStr(&(fezui.u8g2), 0, 7, fezui_buffer);
        sprintf(fezui_buffer, "<%s>", calibrationmenu.items[calibrationmenu.selected_index]);
        u8g2_DrawStr(&(fezui.u8g2), 102, 7, fezui_buffer);
        //u8g2_SetDrawColor(&(fezui.u8g2), 1);
        fezui_draw_cursor(&fezui, &cursor);
        break;
    default:
        drawrawdata(0, 8, calibrationmenu.selected_index);
        u8g2_SetFont(&(fezui.u8g2), u8g2_font_4x6_mr);
        //u8g2_DrawBox(&(fezui.u8g2), x, y, 13, 7);
        //u8g2_SetDrawColor(&(fezui.u8g2), 2);
        sprintf(fezui_buffer, "Press OK to start");
        u8g2_DrawStr(&(fezui.u8g2), 0, 7, fezui_buffer);
        sprintf(fezui_buffer, "<%s>", calibrationmenu.items[calibrationmenu.selected_index]);
        u8g2_DrawStr(&(fezui.u8g2), 102, 7, fezui_buffer);
        //u8g2_SetDrawColor(&(fezui.u8g2), 1);
        fezui_draw_cursor(&fezui, &cursor);
        break;
    }
}

void calibrationpage_load(void *page)
{
    calibrationstate=0;
    lefl_key_attach(keys + 2, KEY_DOWN, lambda(void,(void*k){lefl_link_frame_go_back(&mainframe);}));
    lefl_key_attach(keys + 3, KEY_DOWN, lambda(void,(void*k){Communication_Add8(USART1, PROTOCOL_CMD, CMD_CALIBRATION_START);
                                                            Communication_USART1_Transmit();
                                                            calibrationstate=CMD_CALIBRATION_START;}));
    lefl_key_attach(keys + 4, KEY_DOWN, lambda(void,(void*k){lefl_menu_index_increase(&calibrationmenu, 1);}));
    lefl_key_attach(keys + 5, KEY_DOWN, lambda(void,(void*k){lefl_menu_index_increase(&calibrationmenu, -1);}));
    lefl_key_attach(keys + 6, KEY_DOWN, lambda(void,(void*k){lefl_menu_index_increase(&calibrationmenu, 1);}));
    lefl_key_attach(keys + 7, KEY_DOWN, lambda(void,(void*k){lefl_menu_index_increase(&calibrationmenu, -1);}));
}
