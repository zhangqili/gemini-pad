/*
 * fezui_keyconfigpage.c
 *
 *  Created on: 2023年6月19日
 *      Author: xq123
 */
#include "fezui.h"
#include "fezui_var.h"

#define ROW_HEIGHT 8



void keyconfigpage_init()
{
}

void keyconfigpage_logic(void *page)
{
}

void keyconfigpage_draw(void *page)
{
}

void keyconfigpage_load(void *page)
{
    lefl_key_attach(keys + 2, KEY_DOWN, LAMBDA(void,(void*k)
        {
            lefl_link_frame_go_back(&mainframe);
        }));
}

lefl_page_t keyconfigpage={keyconfigpage_logic,keyconfigpage_draw,keyconfigpage_load};
/*
static lefl_animation_base_t keyconfiganimationx={
        .easing_func=lefl_animation_bounce_ease,
        .from=100,
        .to=0,
        .end=100,
        .tick=0,
        .parameter1=3.0,
        .parameter2=3.0,
        .mode=LEFL_ANIMATION_EASE_OUT,
        .target=&deltax,
};

static lefl_animation_base_t keyconfiganimationy={
        .easing_func=lefl_animation_elastic_ease,
        .end=100,
        .tick=0,
        .parameter1=3.0,
        .parameter2=3.0,
        .mode=LEFL_ANIMATION_EASE_OUT,
        .target=&deltay,
};
*/
/*
void draw_pad()
{
    u8g2_DrawRFrame(&(fezui.u8g2), (uint8_t)deltax+40, 6, 86, 54, 3);
    u8g2_DrawFrame(&(fezui.u8g2), (uint8_t)deltax+40+30, 9, 50, 22);
    u8g2_DrawFrame(&(fezui.u8g2), (uint8_t)deltax+40+73, 3, 6, 4);
    u8g2_DrawFrame(&(fezui.u8g2), (uint8_t)deltax+40+60, 3, 6, 4);
    if(keys[1].state)
        u8g2_DrawBox(&(fezui.u8g2), (uint8_t)deltax+40+73, 59, 6, 4);
    else
        u8g2_DrawFrame(&(fezui.u8g2), (uint8_t)deltax+40+73, 59, 6, 4);
    if(keys[0].state)
        u8g2_DrawBox(&(fezui.u8g2), (uint8_t)deltax+40+60, 59, 6, 4);
    else
        u8g2_DrawFrame(&(fezui.u8g2), (uint8_t)deltax+40+60, 59, 6, 4);
    if(Keyboard_AdvancedKeys[0].key.state)
        u8g2_DrawBox(&(fezui.u8g2), (uint8_t)deltax+44+20*0, 6+32, 19, 19);
    else
        u8g2_DrawFrame(&(fezui.u8g2), (uint8_t)deltax+44+20*0, 6+32, 19, 19);
    if(Keyboard_AdvancedKeys[1].key.state)
        u8g2_DrawBox(&(fezui.u8g2), (uint8_t)deltax+44+20*1, 6+32, 19, 19);
    else
        u8g2_DrawFrame(&(fezui.u8g2), (uint8_t)deltax+44+20*1, 6+32, 19, 19);
    if(Keyboard_AdvancedKeys[2].key.state)
        u8g2_DrawBox(&(fezui.u8g2), (uint8_t)deltax+44+20*2, 6+32, 19, 19);
    else
        u8g2_DrawFrame(&(fezui.u8g2), (uint8_t)deltax+44+20*2, 6+32, 19, 19);
    if(Keyboard_AdvancedKeys[3].key.state)
        u8g2_DrawBox(&(fezui.u8g2), (uint8_t)deltax+44+20*3, 6+32, 19, 19);
    else
        u8g2_DrawFrame(&(fezui.u8g2), (uint8_t)deltax+44+20*3, 6+32, 19, 19);
    u8g2_DrawCircle(&(fezui.u8g2), (uint8_t)deltax+44, 32, 7, U8G2_DRAW_ALL);
    u8g2_DrawCircle(&(fezui.u8g2), (uint8_t)deltax+55, 20, 7, U8G2_DRAW_ALL);
}
*/
