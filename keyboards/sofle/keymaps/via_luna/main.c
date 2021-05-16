#include "main.h"
#include "oled.c"
#include "encoder.c"

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


    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
