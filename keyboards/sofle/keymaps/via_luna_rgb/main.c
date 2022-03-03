#include "main.h"
#include "config.h"
#include "oled.c"
#include "encoder.c"
#include "rgb.c"

bool is_alt_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.
static bool f4key_registered = false;
static bool delkey_registered = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        /* KEYBOARD PET STATUS START */

#ifdef LUNA_ENABLE

        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
            break;
        case KC_SPC:
            if (record->event.pressed) {
                isJumping = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;

#endif

        /* KEYBOARD PET STATUS END */

        case KC_4:
            if (record->event.pressed) {
                if ((get_mods() & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT)) {
                    register_code(KC_F4);
                    f4key_registered = true;
                    return false;
                }
            } else {
                if(f4key_registered) {
                    unregister_code(KC_F4);
                    f4key_registered = false;
                    return false;
                }
            }
            return true;
        case KC_BSPC:
            if (record->event.pressed) {
                if ((get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT))) == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT))) {
                    register_code(KC_DEL);
                    delkey_registered = true;
                    return false;
                }
            } else {
                if(delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
            }
            return true;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
	rgblight_set_layer_state(0, layer_state_cmp(state, _QWERTY) && layer_state_cmp(default_layer_state,_QWERTY));

	// rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
	// rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
	// rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
#endif
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case _RAISE:
            rgb_matrix_set_color(36, RGB_BLUE);
            break;
        case _LOWER:
            rgb_matrix_set_color(0, RGB_YELLOW);
            break;
        case _ADJUST:
            rgb_matrix_set_color(0, RGB_GREEN);
            rgb_matrix_set_color(36, RGB_GREEN);
            break;
        default:
            break;
    }
}