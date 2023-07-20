/*
 * fezui_keyselectpage.c
 *
 *  Created on: 2023年6月19日
 *      Author: xq123
 */
#include "fezui.h"
#include "fezui_var.h"


float UI_KeySelection_Cursor_X=0;
float UI_KeySelection_Cursor_TargetX=0;
float UI_KeySelection_Scroller_X=0;
float UI_KeySelection_Scroller_TargetX=0;
// width: 5, height: 5
const unsigned char win_icon[] U8X8_PROGMEM = { 0x1b,0x1b,0x00,0x1b,0x1b };

lefl_keyboard_t keyboard = {
    .x=0,
    .y=0
};

lefl_animation_base_t keyboardanimation={
        .easing_func=lefl_animation_cubic_ease,
        .from=100,
        .to=0,
        .end=100,
        .tick=0,
        .parameter1=3.0,
        .parameter2=3.0,
        .mode=LEFL_ANIMATION_EASE_OUT,
        .target=&UI_KeySelection_Scroller_X,
};

lefl_page_t keyselectpage={keyselectpage_logic,keyselectpage_draw,keyselectpage_load};
void keyselectpage_logic(lefl_page_t *page)
{
    /*
    if (lefl_key_is_triggered(keys+2))
    {
        lefl_link_frame_go_back(&mainframe);
        //ui_cursor_reset();
    }
    if (lefl_key_is_triggered(keys+4))
    {
        lefl_keyboard_x_increase(&keyboard, 1);
    }
    if (lefl_key_is_triggered(keys+5))
    {
        lefl_keyboard_x_increase(&keyboard, -1);
    }
    if (lefl_key_is_triggered(keys+6))
    {
        lefl_keyboard_y_increase(&keyboard, 1);
    }
    if (lefl_key_is_triggered(keys+7))
    {
        lefl_keyboard_y_increase(&keyboard, -1);
    }
    */
    UI_KeySelection_Cursor_TargetX = 0;
    for (uint8_t i = 0; i < keyboard.x; i++)
    {
        UI_KeySelection_Cursor_TargetX += strlen(ansi_104_keymap[keyboard.y][i]) * 4 + 4;
    }
    UI_KeySelection_Scroller_TargetX = UI_KeySelection_Cursor_TargetX
            + strlen(ansi_104_keymap[keyboard.y][keyboard.x]) * 4 / 2;
    if (UI_KeySelection_Scroller_TargetX >= 64)
    {
        lefl_cursor_set(&target_cursor,
        64 - strlen(ansi_104_keymap[keyboard.y][keyboard.x]) * 4 / 2,
        keyboard.y * 10 + 4,
        strlen(ansi_104_keymap[keyboard.y][keyboard.x]) * 4+ 1,
        7);
    }
    else
    {
        lefl_cursor_set(&target_cursor,
        UI_KeySelection_Cursor_TargetX,
        keyboard.y * 10 + 4,
        strlen(ansi_104_keymap[keyboard.y][keyboard.x]) * 4+ 1,
        7);
    }
    lefl_easing_pid(&UI_KeySelection_Scroller_X,
            UI_KeySelection_Scroller_TargetX);
}
void keyselectpage_draw(lefl_page_t *page)
{
    uint16_t delta_x = 0;
    u8g2_SetFont(&u8g2, u8g2_font_micro_mr);
    if (UI_KeySelection_Scroller_X < 64)
    {
        for (uint8_t i = 0; i < 6; i++)
        {
            delta_x = 1;
            for (uint8_t j = 0; j < 17; j++)
            {
                u8g2_DrawStr(&u8g2, delta_x, 10 * (i + 1),
                        ansi_104_keymap[i][j]);
                delta_x += strlen(ansi_104_keymap[i][j]) * 4 + 4;
                //if(delta_x>WIDTH)
                //break;
            }
        }
        u8g2_DrawXBMP(&u8g2, 4 * 5 + 1, 10 * 6 - 5, 5, 5, win_icon);
    }
    else
    {
        for (uint8_t i = 0; i < 6; i++)
        {
            delta_x = 1;
            for (uint8_t j = 0; j < 17; j++)
            {
                u8g2_DrawStr(&u8g2,
                        delta_x + 64 - (int16_t) UI_KeySelection_Scroller_X,
                        10 * (i + 1), ansi_104_keymap[i][j]);
                delta_x += strlen(ansi_104_keymap[i][j]) * 4 + 4;
                //if(delta_x>WIDTH)
                //break;
            }
            u8g2_DrawXBMP(&u8g2,
                    4 * 5 + 65 - (int16_t) UI_KeySelection_Scroller_X,
                    10 * 6 - 5, 5, 5, win_icon);
            u8g2_DrawXBMP(&u8g2,
                    4 * 40 + 61 - (int16_t) UI_KeySelection_Scroller_X,
                    10 * 6 - 5, 5, 5, win_icon);
        }
    }
    lefl_cursor_draw(&cursor);
}

void keyselectpage_load(lefl_page_t *page)
{
    UI_KeySelection_Cursor_X = 0;
    UI_KeySelection_Scroller_X = 0;
    keys[2].key_cb=lambda(void,(lefl_key_t*k){lefl_link_frame_go_back(&mainframe);});
    keys[3].key_cb=lambda(void,(lefl_key_t*k){lefl_cursor_set(&cursor ,cursor.x-3 ,cursor.y-3 ,cursor.w+6 ,cursor.h+6);});
    keys[4].key_cb=lambda(void,(lefl_key_t*k){lefl_keyboard_x_increase(&keyboard, 1);});
    keys[5].key_cb=lambda(void,(lefl_key_t*k){lefl_keyboard_x_increase(&keyboard, -1);});
    keys[6].key_cb=lambda(void,(lefl_key_t*k){lefl_keyboard_y_increase(&keyboard, 1);});
    keys[7].key_cb=lambda(void,(lefl_key_t*k){lefl_keyboard_y_increase(&keyboard, -1);});
}
