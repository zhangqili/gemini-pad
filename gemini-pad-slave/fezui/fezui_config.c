/*
 * fezui_config.c
 *
 *  Created on: 2023年6月19日
 *      Author: xq123
 */

#include "fezui.h"
#include "fezui_var.h"
#include "lefl.h"
#include "flash_address.h"
#include "MB85RC16.h"
#include "display.h"


uint8_t tempuint;


void fezui_init()
{
    MD_OLED_RST_Set();
    u8g2_Setup_ssd1306_128x64_noname_f(&(fezui.u8g2), U8G2_R0, u8x8_byte_4wire_hw_spi,
            u8x8_stm32_gpio_and_delay);
    u8g2_InitDisplay(&(fezui.u8g2));
    u8g2_SetPowerSave(&(fezui.u8g2), 0);
    //u8g2_SetBitmapMode(&(fezui.u8g2), 1);
    u8g2_SetFontMode(&(fezui.u8g2), 1);
    u8g2_ClearBuffer(&(fezui.u8g2));
    u8g2_DrawLine(&(fezui.u8g2), 15, 15, 20, 18);
    u8g2_DrawLine(&(fezui.u8g2), 15, 22, 20, 18);
    u8g2_DrawLine(&(fezui.u8g2), 26, 16, 20, 18);
    u8g2_DrawLine(&(fezui.u8g2), 26, 26, 20, 18);
    u8g2_DrawLine(&(fezui.u8g2), 26, 16, 31, 12);
    u8g2_DrawLine(&(fezui.u8g2), 21, 8, 31, 12);
    u8g2_DrawLine(&(fezui.u8g2), 39, 4, 31, 12);
    u8g2_DrawLine(&(fezui.u8g2), 42, 21, 31, 12);
    u8g2_DrawLine(&(fezui.u8g2), 26, 26, 33, 30);
    u8g2_DrawLine(&(fezui.u8g2), 46, 39, 33, 30);
    u8g2_DrawLine(&(fezui.u8g2), 26, 26, 26, 38);
    u8g2_DrawLine(&(fezui.u8g2), 42, 44, 26, 38);
    u8g2_DrawLine(&(fezui.u8g2), 42, 21, 52, 27);
    u8g2_DrawLine(&(fezui.u8g2), 55, 26, 52, 27);
    u8g2_DrawLine(&(fezui.u8g2), 42, 21, 50, 32);
    u8g2_SendBuffer(&(fezui.u8g2));

    Analog_Read();
    fezui_read_counts();
    lefl_link_frame_navigate(&mainframe, &homepage);
}

void fezui_timer_handler()
{
    //for (uint8_t i = 0; i < MAIN_KEY_NUM; i++)
    //{
    //    lefl_advanced_key_update_state(advanced_keys+i, key_buffer[i]);
    //}
    for (uint8_t i = MAIN_KEY_NUM; i < KEY_NUM; i++)
    {
        lefl_key_update(keys+i-4, key_buffer[i]);
    }

    lefl_link_frame_logic(&mainframe);
    lefl_cursor_move(&cursor, &target_cursor);

    uint8_t n=0;
    for (uint8_t i = 0; i < MAIN_KEY_NUM; i++)
    {
        if (lefl_advanced_key_is_triggered(advanced_keys+i))
        {
            fezui_keytotalcounts[i]++;
            n++;
        }
        lefl_bit_array_shift(lines+i, 1);
        if (advanced_keys[i].key.state)
        {
            lefl_bit_array_set(lines+i, 0, true);
        }
    }
    lefl_loop_array_push_back(&KPS_queue, n);

    fezui_kps = 0;
    for (uint8_t i = 0; i < REFRESH_RATE; i++)
    {
        fezui_kps += KPS_queue.list[i];
    }
    if (fezui_kps > UI_KPSMaximumPerSecond)
    {
        UI_KPSMaximumPerSecond = fezui_kps;
    }
    KPS_history_max=lefl_loop_array_max(&KPS_history);
    if(fezui_kps>KPS_history_max)
    {
        KPS_history_max=fezui_kps;
        KPS_history.list[KPS_history.index]=fezui_kps;
    }
    fezui_save_counts();

    if (KPS_history_max || keys[0].state||keys[1].state||keys[2].state||keys[3].state||keys[4].state||keys[5].state||keys[6].state||keys[7].state)
    {
        //tempuint=keys[0].state+(keys[1].state<<1)+(keys[2].state<<2)+(keys[3].state<<3)+(keys[4].state<<4)+(keys[5].state<<5)+(keys[6].state<<6)+(keys[7].state<<7);

        fezui_rest_countdown = SCREEN_REST_TIME;
    }
    /*
    u8g2_ClearBuffer(&(fezui.u8g2));
    //sprintf(fezui_tempstr,"%d",UI_IsDisplayOn);
    //u8g2_DrawStr(&(fezui.u8g2), 64, 10, fezui_tempstr);
    lefl_link_frame_draw(&mainframe);
#ifdef _SCREEN_REST_ON
    u8g2_SetPowerSave(&(fezui.u8g2),!UI_IsDisplayOn);
#endif
    u8g2_SendBuffer(&(fezui.u8g2));

    UI_FPS++;
    */
}

extern fezui_t fezui;

void fezui_menu_update_selection(lefl_menu_t *menu)
{
    if (lefl_key_is_triggered(keys+4))
    {
        lefl_menu_index_increase(menu, 1);
    }
    if (lefl_key_is_triggered(keys+5))
    {
        lefl_menu_index_increase(menu, -1);
    }
    if (lefl_key_is_triggered(keys+6))
    {
        lefl_menu_index_increase(menu, 1);
    }
    if (lefl_key_is_triggered(keys+7))
    {
        lefl_menu_index_increase(menu, -1);
    }
}

void Analog_Read()
{
    for (uint16_t i = 0; i < MAIN_KEY_NUM; i++)
    {
        MB85RC16_ReadByte (i*64+KEY1_CONFIG_ADDRESS,       &(advanced_keys[i].mode));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1,     &(advanced_keys[i].trigger_distance));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*1, &(advanced_keys[i].release_distance));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*2, &(advanced_keys[i].schmitt_parameter));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*3, &(advanced_keys[i].trigger_speed));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*4, &(advanced_keys[i].release_speed));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*5, &(advanced_keys[i].upper_deadzone));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*6, &(advanced_keys[i].lower_deadzone));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*7, &(advanced_keys[i].range));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*8, &(advanced_keys[i].upper_bound));
        MB85RC16_ReadFloat(i*64+KEY1_CONFIG_ADDRESS+1+4*9, &(advanced_keys[i].lower_bound));
    }
}

void fezui_save_counts()
{
    for (uint16_t i = 0; i < MAIN_KEY_NUM; i++)
    {
        MB85RC16_WriteLong(KEY_COUNTS_ADDRESS+i*4, fezui_keytotalcounts[i]);
    }
}

void fezui_read_counts()
{
    for (uint16_t i = 0; i < MAIN_KEY_NUM; i++)
    {
        MB85RC16_ReadLong(KEY_COUNTS_ADDRESS+i*4, fezui_keyinitcounts+i);
        fezui_keytotalcounts[i]=fezui_keyinitcounts[i];
    }
}
