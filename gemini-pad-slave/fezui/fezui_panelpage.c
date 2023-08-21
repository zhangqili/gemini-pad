#include "fezui.h"
#include "fezui_var.h"

#define MARGIN_TILE 3

uint8_t selection;

void panelpage_init()
{

}

void panelpage_logic(void *page)
{
    lefl_cursor_set(
            &target_cursor ,
            (32*selection)%128,
            (selection)/4*32,
            32,
            32);
}

void panelpage_draw(void *page)
{
    uint8_t color = u8g2_GetDrawColor(&(fezui.u8g2));

    u8g2_SetFont(&(fezui.u8g2), u8g2_font_4x6_mr);

    if(Keyboard_AdvancedKeys[0].key.state)
    {
        u8g2_DrawBox(&(fezui.u8g2), 32*0+MARGIN_TILE, MARGIN_TILE, 32-MARGIN_TILE*2, 32-MARGIN_TILE*2);
    }
    else
    {
        u8g2_DrawFrame(&(fezui.u8g2), 32*0+MARGIN_TILE, MARGIN_TILE, 32-MARGIN_TILE*2, 32-MARGIN_TILE*2);
    }

    if(Keyboard_AdvancedKeys[1].key.state)
    {
        u8g2_DrawBox(&(fezui.u8g2), 32*1+MARGIN_TILE, MARGIN_TILE, 32-MARGIN_TILE*2, 32-MARGIN_TILE*2);
    }
    else
    {
        u8g2_DrawFrame(&(fezui.u8g2), 32*1+MARGIN_TILE, MARGIN_TILE, 32-MARGIN_TILE*2, 32-MARGIN_TILE*2);
    }

    if(Keyboard_AdvancedKeys[2].key.state)
    {
        u8g2_DrawBox(&(fezui.u8g2), 32*2+MARGIN_TILE, MARGIN_TILE, 32-MARGIN_TILE*2, 32-MARGIN_TILE*2);
    }
    else
    {
        u8g2_DrawFrame(&(fezui.u8g2), 32*2+MARGIN_TILE, MARGIN_TILE, 32-MARGIN_TILE*2, 32-MARGIN_TILE*2);
    }

    if(Keyboard_AdvancedKeys[3].key.state)
    {
        u8g2_DrawBox(&(fezui.u8g2), 32*3+MARGIN_TILE, MARGIN_TILE, 32-MARGIN_TILE*2, 32-MARGIN_TILE*2);
    }
    else
    {
        u8g2_DrawFrame(&(fezui.u8g2), 32*3+MARGIN_TILE, MARGIN_TILE, 32-MARGIN_TILE*2, 32-MARGIN_TILE*2);
    }

    u8g2_DrawFrame(&(fezui.u8g2), 32*0+MARGIN_TILE, 32+MARGIN_TILE, 32-MARGIN_TILE*2, 32-MARGIN_TILE*2);
    u8g2_DrawFrame(&(fezui.u8g2), 32*1+MARGIN_TILE, 32+MARGIN_TILE, 32-MARGIN_TILE*2, 32-MARGIN_TILE*2);
    if(Keyboard_Keys[0].state)
    {
        u8g2_DrawBox(&(fezui.u8g2), 32*2+MARGIN_TILE, 32+MARGIN_TILE, 32-MARGIN_TILE*2, 32-MARGIN_TILE*2);
    }
    else
    {
        u8g2_DrawFrame(&(fezui.u8g2), 32*2+MARGIN_TILE, 32+MARGIN_TILE, 32-MARGIN_TILE*2, 32-MARGIN_TILE*2);
    }
    if(Keyboard_Keys[1].state)
    {
        u8g2_DrawBox(&(fezui.u8g2), 32*3+MARGIN_TILE, 32+MARGIN_TILE, 32-MARGIN_TILE*2, 32-MARGIN_TILE*2);
    }
    else
    {
        u8g2_DrawFrame(&(fezui.u8g2), 32*3+MARGIN_TILE, 32+MARGIN_TILE, 32-MARGIN_TILE*2, 32-MARGIN_TILE*2);
    }

    if(Keyboard_Keys[2].state)
    {

        u8g2_DrawBox(&(fezui.u8g2), 32*1+MARGIN_TILE, 32+MARGIN_TILE, 32-MARGIN_TILE*2, 32-MARGIN_TILE*2);
    }

    if(Keyboard_Keys[3].state)
    {
        u8g2_DrawBox(&(fezui.u8g2), 32*0+MARGIN_TILE, 32+MARGIN_TILE, 32-MARGIN_TILE*2, 32-MARGIN_TILE*2);
    }

    if(Keyboard_Keys[4].state)
    {
        u8g2_DrawBox(&(fezui.u8g2), 32*0+MARGIN_TILE, 32+MARGIN_TILE, (32-MARGIN_TILE*2)/2, 32-MARGIN_TILE*2);
    }
    if(Keyboard_Keys[5].state)
    {
        u8g2_DrawBox(&(fezui.u8g2), 32*0+16+MARGIN_TILE, 32+MARGIN_TILE, (32-MARGIN_TILE*2)/2, 32-MARGIN_TILE*2);
    }

    if(Keyboard_Keys[6].state)
    {
        u8g2_DrawBox(&(fezui.u8g2), 32*1+MARGIN_TILE, 32+MARGIN_TILE, 32-MARGIN_TILE*2, (32-MARGIN_TILE*2)/2);
    }
    if(Keyboard_Keys[7].state)
    {
        u8g2_DrawBox(&(fezui.u8g2), 32*1+MARGIN_TILE, 32+16, 32-MARGIN_TILE*2, (32-MARGIN_TILE*2)/2);
    }
    u8g2_SetDrawColor(&(fezui.u8g2), 2);

    u8g2_DrawStr(&(fezui.u8g2), 32*0+16-8,16,"KEY1");
    u8g2_DrawStr(&(fezui.u8g2), 32*1+16-8,16,"KEY2");
    u8g2_DrawStr(&(fezui.u8g2), 32*2+16-8,16,"KEY3");
    u8g2_DrawStr(&(fezui.u8g2), 32*3+16-8,16,"KEY4");
    u8g2_DrawStr(&(fezui.u8g2), 32*0+16-10,32+16,"WHEEL");
    u8g2_DrawStr(&(fezui.u8g2), 32*1+16-8,32+16,"KNOB");
    u8g2_DrawStr(&(fezui.u8g2), 32*2+16-10,32+16,"SHIFT");
    u8g2_DrawStr(&(fezui.u8g2), 32*3+16-10,32+16,"ALPHA");

    u8g2_SetDrawColor(&(fezui.u8g2), color);
    fezui_draw_cursor(&fezui, &cursor);
}

static void selection_update(int8_t x)
{
    if(selection+x<0)
    {
        selection+=8+x;
    }
    else if(selection+x>=8)
    {
        selection+=x-8;
    }
    else
    {
        selection+=x;
    }
    if(selection<0)
    {
        selection=7;
    }
    if(selection>=8)
    {
        selection=0;
    }
}

void panelpage_load(void *page)
{
    lefl_key_attach(&KEY_KNOB, KEY_DOWN, LAMBDA(void,(void*k){lefl_link_frame_go_back(&mainframe);}));
    lefl_key_attach(&KEY_WHEEL, KEY_DOWN, LAMBDA(void,(void*k)
    {
        if (selection<4)
        {
            current_config_advanced_key = Keyboard_AdvancedKeys + selection;
            lefl_link_frame_navigate(&mainframe,&advancedconfigpage);
        }
    }));
    lefl_key_attach(&KEY_KNOB_CLOCKWISE, KEY_DOWN, LAMBDA(void,(void*k){selection_update(1);}));
    lefl_key_attach(&KEY_KNOB_ANTICLOCKWISE, KEY_DOWN, LAMBDA(void,(void*k){selection_update(-1);}));
    lefl_key_attach(&KEY_WHEEL_CLOCKWISE, KEY_DOWN, LAMBDA(void,(void*k){selection_update(4);}));
    lefl_key_attach(&KEY_WHEEL_ANTICLOCKWISE, KEY_DOWN, LAMBDA(void,(void*k){selection_update(-4);}));
}

lefl_page_t panelpage={panelpage_logic,panelpage_draw,panelpage_load};
