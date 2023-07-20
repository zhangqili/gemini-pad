/*
 * fezui_keyconfigpage.c
 *
 *  Created on: 2023年6月19日
 *      Author: xq123
 */
#include "fezui.h"
#include "fezui_var.h"


lefl_menu_t keyconfigmenu={
        .items={"KEY1","KEY2","KEY3","KEY4","SHIFT","ALPHA","KNOB","WHEEL"},
        .len=8,
        .selected_index=0
};

lefl_menu_t keyconfig_digital_mode_menu={
        .items={"Bindings","Mode"},
        .len=2,
        .selected_index=0
};

lefl_menu_t keyconfig_analog_normal_mode_menu={
        .items={"Bindings","Mode","Trigger distance","Schmitt parameter","Upper deadzone","Lower deadzone"},
        .len=6,
        .selected_index=0
};

lefl_menu_t keyconfig_analog_rapid_mode_menu={
        .items={"Bindings","Mode","Trigger distance","Release distance","Schmitt parameter","Upper deadzone","Lower deadzone"},
        .len=7,
        .selected_index=0
};

lefl_menu_t keyconfig_analog_speed_mode_menu={
        .items={"Bindings","Mode","Trigger speed","Release speed","Upper deadzone","Lower deadzone"},
        .len=6,
        .selected_index=0
};

static float deltay=0;
//static float targety=0;
static float deltax=64;
//static float targetx=0;
static uint8_t selection1=0;
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


static lefl_cursor_t selectedkey={0,0,0,0};
static lefl_cursor_t targetselectedkey={0,0,0,0};

void draw_pad()
{
    u8g2_DrawRFrame(&u8g2, (uint8_t)deltax+40, 6, 86, 54, 3);
    u8g2_DrawFrame(&u8g2, (uint8_t)deltax+40+30, 9, 50, 22);
    u8g2_DrawFrame(&u8g2, (uint8_t)deltax+40+73, 3, 6, 4);
    u8g2_DrawFrame(&u8g2, (uint8_t)deltax+40+60, 3, 6, 4);
    if(keys[0].state)
        u8g2_DrawBox(&u8g2, (uint8_t)deltax+40+73, 59, 6, 4);
    else
        u8g2_DrawFrame(&u8g2, (uint8_t)deltax+40+73, 59, 6, 4);
    if(keys[1].state)
        u8g2_DrawBox(&u8g2, (uint8_t)deltax+40+60, 59, 6, 4);
    else
        u8g2_DrawFrame(&u8g2, (uint8_t)deltax+40+60, 59, 6, 4);
    if(advanced_keys[0].state)
        u8g2_DrawBox(&u8g2, (uint8_t)deltax+44+20*0, 6+32, 19, 19);
    else
        u8g2_DrawFrame(&u8g2, (uint8_t)deltax+44+20*0, 6+32, 19, 19);
    if(advanced_keys[1].state)
        u8g2_DrawBox(&u8g2, (uint8_t)deltax+44+20*1, 6+32, 19, 19);
    else
        u8g2_DrawFrame(&u8g2, (uint8_t)deltax+44+20*1, 6+32, 19, 19);
    if(advanced_keys[2].state)
        u8g2_DrawBox(&u8g2, (uint8_t)deltax+44+20*2, 6+32, 19, 19);
    else
        u8g2_DrawFrame(&u8g2, (uint8_t)deltax+44+20*2, 6+32, 19, 19);
    if(advanced_keys[3].state)
        u8g2_DrawBox(&u8g2, (uint8_t)deltax+44+20*3, 6+32, 19, 19);
    else
        u8g2_DrawFrame(&u8g2, (uint8_t)deltax+44+20*3, 6+32, 19, 19);
    u8g2_DrawCircle(&u8g2, (uint8_t)deltax+44, 32, 7, U8G2_DRAW_ALL);
    u8g2_DrawCircle(&u8g2, (uint8_t)deltax+55, 20, 7, U8G2_DRAW_ALL);
}

void keyconfigpage_logic(lefl_page_t *page)
{
    lefl_animation_tick(&keyconfiganimationx);
    lefl_animation_tick(&keyconfiganimationy);
    /*
    if(lefl_key_is_triggered(keys+2))
    {
        lefl_link_frame_go_back(&mainframe);
    }
    */
    //fezui_menu_update_selection(&keyconfigmenu);
    if(selection1!=keyconfigmenu.selected_index)
    {
        keyconfiganimationy.from = deltay;
        keyconfiganimationy.to = keyconfigmenu.selected_index*ITEM_HEIGHT;
        lefl_animation_begin(&keyconfiganimationy);
    }
    selection1=keyconfigmenu.selected_index;
    //targety=keyconfigmenu.selected_index*ITEM_HEIGHT;
    //lefl_easing_pid(&deltay,targety);
    //lefl_easing_pid(&deltax,targetx);
    lefl_cursor_move(&selectedkey, &targetselectedkey);
}

void keyconfigpage_draw(lefl_page_t *page)
{
    u8g2_SetFont(&u8g2, u8g2_font_6x13_tf);
    for(uint8_t i=0;i<keyconfigmenu.len;i++)
    {
        u8g2_DrawStr(&u8g2,1,32+3-(int16_t)deltay+i*ITEM_HEIGHT+2,keyconfigmenu.items[i]);
    }
    lefl_cursor_draw(&cursor);
    u8g2_DrawVLine(&u8g2, 32, 0, 64);
    draw_pad();
}

void keyconfigpage_load(lefl_page_t *page)
{
    keyconfiganimationy.from = 64;
    keyconfiganimationy.to = keyconfigmenu.selected_index*ITEM_HEIGHT;
    keys[2].key_cb=lambda(void,(lefl_key_t*k){lefl_link_frame_go_back(&mainframe);});
    keys[3].key_cb=lambda(void,(lefl_key_t*k){lefl_link_frame_navigate(&mainframe, &keyselectpage);});
    keys[4].key_cb=lambda(void,(lefl_key_t*k){lefl_menu_index_increase(&keyconfigmenu, 1);});
    keys[5].key_cb=lambda(void,(lefl_key_t*k){lefl_menu_index_increase(&keyconfigmenu, -1);});
    keys[6].key_cb=lambda(void,(lefl_key_t*k){lefl_menu_index_increase(&keyconfigmenu, 1);});
    keys[7].key_cb=lambda(void,(lefl_key_t*k){lefl_menu_index_increase(&keyconfigmenu, -1);});
    lefl_animation_begin(&keyconfiganimationy);
    lefl_animation_begin(&keyconfiganimationx);
    lefl_cursor_set(&target_cursor, 0,32-8,32,ITEM_HEIGHT + 2);
}

lefl_page_t keyconfigpage={keyconfigpage_logic,keyconfigpage_draw,keyconfigpage_load};
