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
#include "luna.c"
#include "bongo_cat.c"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

static void print_status_narrow(void) {
    // Print current mode
    oled_set_cursor(0,0);

    if (keymap_config.swap_lctl_lgui) {
        oled_write_raw_P(mac_logo, sizeof(mac_logo));
    } else {
        oled_write_raw_P(windows_logo, sizeof(windows_logo));
    }

    oled_set_cursor(0,3);

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("QWRTY"), false);
            break;
        case _COLEMAK:
            oled_write_ln_P(PSTR("CLMK"), false);
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
        case _COLEMAK:
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

    oled_set_cursor(0,9);

    oled_write_char('S', get_mods() & MOD_MASK_SHIFT);
    oled_write_char('C', get_mods() & MOD_MASK_CTRL);
    oled_write_char('A', get_mods() & MOD_MASK_ALT);
    oled_write_char('G', get_mods() & MOD_MASK_GUI);

    oled_set_cursor(0,11);

    oled_write_ln_P(PSTR("CPSLK"), host_keyboard_led_state().caps_lock);

    /* KEYBOARD PET RENDER START */

    render_luna(0,13);

    /* KEYBOARD PET RENDER END */
}

static void print_slave_narrow(void) {
    render_bongo();
    /* wpm counter */
    char wpm_str[8];
    oled_set_cursor(0,14);
    sprintf(wpm_str, " %03d", get_current_wpm());
    oled_write(wpm_str, false);

    oled_set_cursor(0,15);
    oled_write(" wpm", false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        print_slave_narrow();
    }
    return false;
}

#endif
