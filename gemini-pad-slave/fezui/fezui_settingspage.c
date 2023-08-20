/*
 * fezui_settingspage.c
 *
 *  Created on: 2023年6月19日
 *      Author: xq123
 */
#include "fezui.h"
#include "fezui_var.h"
lefl_menu_t settingsmenu;
const char* settingsmenu_items[] = {"Keys Configuration","Calibration","Debug","About"};
lefl_page_t settingspage={settingspage_logic,settingspage_draw,settingspage_load};


void settingspage_init()
{
    lefl_menu_init(&settingsmenu, settingsmenu_items, sizeof(settingsmenu_items)/sizeof(const char*), settings_menu_cb);
}

void settingspage_logic(void *page)
{
    lefl_cursor_set(&target_cursor, 3,
            settingsmenu.selected_index * ITEM_HEIGHT + 3,
            strlen(settingsmenu.items[settingsmenu.selected_index]) * 6 + 6,
            ITEM_HEIGHT);
}
void settingspage_draw(void *page)
{
    u8g2_SetFont(&(fezui.u8g2), u8g2_font_6x13_tf);
    for(uint8_t i=0;i<settingsmenu.len;i++)
    {
        u8g2_DrawStr(&(fezui.u8g2),5,ITEM_HEIGHT*(i+1),settingsmenu.items[i]);
    }
    fezui_draw_cursor(&fezui, &cursor);
}
void settings_menu_cb(void *menu)
{

    switch (((lefl_menu_t*)menu)->selected_index)
    {
    case 0:
        lefl_link_frame_navigate(&mainframe, &panelpage);
        break;
    case 1:
        lefl_link_frame_navigate(&mainframe, &calibrationpage);
        break;
    case 2:
        lefl_link_frame_navigate(&mainframe, &debugpage);
        break;
    case 3:
        lefl_link_frame_navigate(&mainframe, &aboutpage);
        break;
    default:
        break;
    }
}
void settingspage_load(void *page)
{
    lefl_key_attach(keys + 2, KEY_DOWN, LAMBDA(void,(void*k){lefl_link_frame_go_back(&mainframe);}));
    lefl_key_attach(keys + 3, KEY_DOWN, LAMBDA(void,(void*k){lefl_menu_click(&settingsmenu);}));
    lefl_key_attach(keys + 4, KEY_DOWN, LAMBDA(void,(void*k){lefl_menu_index_increase(&settingsmenu, 1);}));
    lefl_key_attach(keys + 5, KEY_DOWN, LAMBDA(void,(void*k){lefl_menu_index_increase(&settingsmenu, -1);}));
    lefl_key_attach(keys + 6, KEY_DOWN, LAMBDA(void,(void*k){lefl_menu_index_increase(&settingsmenu, 1);}));
    lefl_key_attach(keys + 7, KEY_DOWN, LAMBDA(void,(void*k){lefl_menu_index_increase(&settingsmenu, -1);}));
}
