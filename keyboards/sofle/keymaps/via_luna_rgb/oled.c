 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

//Sets up what the OLED screens display.
#ifdef OLED_ENABLE
#include <stdio.h>
#include "images.c"
#ifdef LUNA_ENABLE
#include "luna.c"
#endif
#ifdef BONGO_CAT_ENABLE
#include "bongo_cat.c"
#endif

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

#define LOGO_BYTES 16 * 4

#if defined(LUNA_ENABLE) || defined(BONGO_CAT_ENABLE)
uint32_t anim_sleep = 0;
static void oled_sleep(void) {
    if(get_current_wpm() > 0) {
        oled_on();
        anim_sleep = timer_read32();
    } else if(timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
        oled_off();
    }
}
#endif

#ifdef LEFT_BOARD
static void print_status_narrow(void) {
    // Print current mode
    oled_set_cursor(0,0);

    if (keymap_config.swap_lctl_lgui) {
        oled_write_compressed_P(mac_logo_block_x_map, mac_logo_block_x_list, 0, LOGO_BYTES);
    } else {
        oled_write_compressed_P(windows_logo_block_x_map, windows_logo_block_x_list, 0, LOGO_BYTES);
    }

    oled_set_cursor(0,3);

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("QWRTY"), false);
            break;
        case _GAMING:
            oled_write_ln_P(PSTR("GAME"), false);
            break;
        default:
            oled_write_ln_P(PSTR("UNDEF"), false);
    }

    // Print current layer
    oled_set_cursor(0,5);

    oled_write("LAYER", false);

    oled_set_cursor(0,6);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
        case _GAMING:
            oled_write("Base\n", false);
            break;
        case _LOWER:
            oled_write_ln("Lower", false);
            break;
        case _RAISE:
            oled_write_ln("Raise", false);
            break;
        case _ADJUST:
            oled_write_ln("Adj", false);
            break;
        default:
            oled_write_ln("Undef", false);
    }

    oled_set_cursor(0,8);

    oled_write_char('S', get_mods() & MOD_MASK_SHIFT);
    oled_write_char('C', get_mods() & MOD_MASK_CTRL);
    oled_write_char('A', get_mods() & MOD_MASK_ALT);
    oled_write_char('G', get_mods() & MOD_MASK_GUI);

    oled_set_cursor(0,9);

    oled_write_ln_P(PSTR("CPSLK"), host_keyboard_led_state().caps_lock);

    /* KEYBOARD PET RENDER START */
#ifdef LUNA_ENABLE
    render_luna(0,13);
#endif
    /* KEYBOARD PET RENDER END */
}
#endif

#ifdef RIGHT_BOARD
static void print_slave_narrow(void) {
    #ifdef BONGO_CAT_ENABLE
        render_bongo();
    #endif
    /* wpm counter */
    char wpm_str[8];
    oled_set_cursor(0,14);
    sprintf(wpm_str, " %03d", get_current_wpm());
    oled_write(wpm_str, false);

    oled_set_cursor(0,15);
    oled_write(" wpm", false);
}
#endif

bool oled_task_user(void) {
#if defined(LUNA_ENABLE) || defined(BONGO_CAT_ENABLE)
    oled_sleep();
#endif
#ifdef LEFT_BOARD
    print_status_narrow();
#endif

#ifdef RIGHT_BOARD
    print_slave_narrow();
#endif
    return false;
}



#endif
