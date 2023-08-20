/*
 * fezui_oscilloscopepage.c
 *
 *  Created on: 2023年6月19日
 *      Author: xq123
 */
#include "fezui.h"
#include "fezui_var.h"

lefl_page_t oscilloscopepage={oscilloscopepage_logic,oscilloscopepage_draw,oscilloscopepage_load};
void oscilloscopepage_logic(void *page)
{
    lefl_loop_array_push_back(analog_historys+0, (uint16_t)Keyboard_AdvancedKeys[0].raw);
    lefl_loop_array_push_back(analog_historys+1, (uint16_t)Keyboard_AdvancedKeys[1].raw);
    lefl_loop_array_push_back(analog_historys+2, (uint16_t)Keyboard_AdvancedKeys[2].raw);
    lefl_loop_array_push_back(analog_historys+3, (uint16_t)Keyboard_AdvancedKeys[3].raw);
}
void oscilloscopepage_draw(void *page)
{
    fezui_draw_wave(&(fezui), 0, 0, 64, 32, analog_historys+0, lines+0);
    fezui_draw_wave(&(fezui), 64, 0, 64, 32, analog_historys+1, lines+1);
    fezui_draw_wave(&(fezui), 0, 32, 64, 32, analog_historys+2, lines+2);
    fezui_draw_wave(&(fezui), 64, 32, 64, 32, analog_historys+3, lines+3);
}

void oscilloscopepage_load(void *page)
{
    lefl_key_attach(keys + 2, KEY_DOWN, LAMBDA(void,(void*k){lefl_link_frame_go_back(&mainframe);lefl_cursor_set(&cursor ,0 ,0 ,WIDTH ,HEIGHT);}));
    lefl_key_attach(keys + 3, KEY_DOWN, NULL);
    lefl_key_attach(keys + 4, KEY_DOWN, NULL);
    lefl_key_attach(keys + 5, KEY_DOWN, NULL);
    lefl_key_attach(keys + 6, KEY_DOWN, NULL);
    lefl_key_attach(keys + 7, KEY_DOWN, NULL);
}
