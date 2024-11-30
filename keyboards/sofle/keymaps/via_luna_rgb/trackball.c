#if defined(POINTING_DEVICE_ENABLE) && defined(RIGHT_BOARD)
#include <string.h>
#include "lib/lib8tion/lib8tion.h"

static uint32_t       last_mouse_activity = 0;
static report_mouse_t last_mouse_report   = {0};
static bool           is_scrolling        = false;

report_mouse_t smooth_mouse_movement(report_mouse_t mouse_report) {
    // Linear interpolation and ease-in-out
    static fract8 fract = 0.5;
    int8_t        x     = 0;
    int8_t        y     = 0;
    int8_t        h     = 0;
    int8_t        v     = 0;

    if (!is_scrolling) {
        x = ease8InOutApprox(lerp8by8(last_mouse_report.x, mouse_report.x, fract));
        y = ease8InOutApprox(lerp8by8(last_mouse_report.y, mouse_report.y, fract));
    } else {
        h = ease8InOutApprox(lerp8by8(last_mouse_report.x, mouse_report.x, fract));
        v = ease8InOutApprox(lerp8by8(last_mouse_report.y, mouse_report.y, fract));
    }

    // update the new smoothed report
    mouse_report.x = x;
    mouse_report.y = y;
    mouse_report.h = h;
    mouse_report.v = v;

    return mouse_report;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    #ifdef POINTING_DEVICE_ENABLE
        pimoroni_trackball_set_rgbw(0,153,95,0);
    #endif

    if (has_mouse_report_changed(&last_mouse_report, &mouse_report)) {
        last_mouse_activity = timer_read32();
        memcpy(&last_mouse_report, &mouse_report, sizeof(mouse_report));
    }
    if (layer_state_is(_RAISE) || layer_state_is(_LOWER)) {
        is_scrolling = true;
        pointing_device_set_cpi(2000);
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    } else {
        if (is_scrolling) {  // check if we were scrolling before and set disable if so
            is_scrolling = false;
            pointing_device_set_cpi(8000);
        }
    }


    return smooth_mouse_movement(mouse_report);
}

void keyboard_post_init_kb(void) {

    keyboard_post_init_user();
}
#endif

// layer_state_t layer_state_set_user(layer_state_t state) {
//     switch (get_highest_layer(state)) {
//     case _BASE:
//         trackball_set_rgbw(0,0,0,80);
//         break;
//     case _NAV:
//         trackball_set_rgbw(0,153,95,0);
//         break;
//     case _SYM:
//         trackball_set_rgbw(153,113,0,0);
//         break;
//     default: //  for any other layers, or the default layer
//         trackball_set_rgbw(0,0,0,80);
//         break;
//     }
//   return state;
// }
//https://github.com/greyhatmiddleman/qmk_firmware/blob/greyhatmiddleman/keyboards/crkbd/keymaps/greyhatmiddleman_trackball_right/keymap.c