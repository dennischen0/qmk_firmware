#include "main.h"
#include "oled.c"
#include "encoder.c"

bool is_alt_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.
static bool f4key_registered = false;
static bool delkey_registered = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        /* KEYBOARD PET STATUS START */

#ifdef OLED_DRIVER_ENABLE

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
                if(delkey_registered) {
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
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
