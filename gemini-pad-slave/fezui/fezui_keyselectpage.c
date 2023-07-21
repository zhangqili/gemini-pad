/*
 * fezui_keyselectpage.c
 *
 *  Created on: 2023年6月19日
 *      Author: xq123
 */
#include "fezui.h"
#include "fezui_var.h"


static float Cursor_X=0;
static float Cursor_TargetX=0;
static float Scroller_X=0;
static float Scroller_TargetX=0;
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
        .target=&Scroller_X,
};

lefl_page_t keyselectpage={keyselectpage_logic,keyselectpage_draw,keyselectpage_load};
void keyselectpage_logic(lefl_page_t *page)
{

    Cursor_TargetX = 0;
    for (uint8_t i = 0; i < keyboard.x; i++)
    {
        Cursor_TargetX += strlen(ansi_104_keymap[keyboard.y][i]) * 4 + 4;
    }
    Scroller_TargetX = Cursor_TargetX
            + strlen(ansi_104_keymap[keyboard.y][keyboard.x]) * 4 / 2;
    if (Scroller_TargetX >= 64)
    {
        lefl_cursor_set(&target_cursor,
        64 - strlen(ansi_104_keymap[keyboard.y][keyboard.x]) * 4 / 2,
        keyboard.y * 10,
        strlen(ansi_104_keymap[keyboard.y][keyboard.x]) * 4+ 1,
        7);
    }
    else
    {
        lefl_cursor_set(&target_cursor,
        Cursor_TargetX,
        keyboard.y * 10,
        strlen(ansi_104_keymap[keyboard.y][keyboard.x]) * 4+ 1,
        7);
    }
    lefl_easing_pid(&Scroller_X,
            Scroller_TargetX);
}
void keyselectpage_draw(lefl_page_t *page)
{
    uint16_t delta_x = 0;
    u8g2_SetFont(&(fezui.u8g2), u8g2_font_micro_mr);
    if (Scroller_X < 64)
    {
        for (uint8_t i = 0; i < 6; i++)
        {
            delta_x = 1;
            for (uint8_t j = 0; j < 17; j++)
            {
                u8g2_DrawStr(&(fezui.u8g2), delta_x, 10 * (i + 1) - 4,
                        ansi_104_keymap[i][j]);
                delta_x += strlen(ansi_104_keymap[i][j]) * 4 + 4;
                //if(delta_x>WIDTH)
                //break;
            }
        }
        u8g2_DrawXBMP(&(fezui.u8g2), 4 * 5 + 1, 10 * 6 - 5 - 4, 5, 5, win_icon);
    }
    else
    {
        for (uint8_t i = 0; i < 6; i++)
        {
            delta_x = 1;
            for (uint8_t j = 0; j < 17; j++)
            {
                u8g2_DrawStr(&(fezui.u8g2),
                        delta_x + 64 - (int16_t) Scroller_X,
                        10 * (i + 1) - 4, ansi_104_keymap[i][j]);
                delta_x += strlen(ansi_104_keymap[i][j]) * 4 + 4;
                //if(delta_x>WIDTH)
                //break;
            }
            u8g2_DrawXBMP(&(fezui.u8g2),
                    4 * 5 + 65 - (int16_t) Scroller_X,
                    10 * 6 - 5 - 4, 5, 5, win_icon);
            u8g2_DrawXBMP(&(fezui.u8g2),
                    4 * 40 + 61 - (int16_t) Scroller_X,
                    10 * 6 - 5 - 4, 5, 5, win_icon);
        }
    }
    fezui_draw_cursor(&fezui, &cursor);
    if (Scroller_X < 64)
    	fezui_draw_scrollbar(&fezui, 1, 58, 126, 3, 363, 64, 0, ORIENTATION_HORIZAIONTAL);
    else
    	fezui_draw_scrollbar(&fezui, 1, 58, 126, 3, 363, 64, (Scroller_X-64)/(363-64), ORIENTATION_HORIZAIONTAL);
}

void keyselectpage_load(lefl_page_t *page)
{
    Cursor_X = 0;
    Scroller_X = 0;
    keys[2].key_cb=lambda(void,(lefl_key_t*k){lefl_link_frame_go_back(&mainframe);});
    keys[3].key_cb=lambda(void,(lefl_key_t*k){lefl_cursor_set(&cursor ,cursor.x-3 ,cursor.y-3 ,cursor.w+6 ,cursor.h+6);});
    keys[4].key_cb=lambda(void,(lefl_key_t*k){lefl_keyboard_x_increase(&keyboard, 1);});
    keys[5].key_cb=lambda(void,(lefl_key_t*k){lefl_keyboard_x_increase(&keyboard, -1);});
    keys[6].key_cb=lambda(void,(lefl_key_t*k){lefl_keyboard_y_increase(&keyboard, 1);});
    keys[7].key_cb=lambda(void,(lefl_key_t*k){lefl_keyboard_y_increase(&keyboard, -1);});
}
