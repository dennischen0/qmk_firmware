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

#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

#define DYNAMIC_KEYMAP_LAYER_COUNT 6

//#define USE_MATRIX_I2C

/* Select hand configuration */

///https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/

#define MASTER_LEFT
#define RIGHT_BOARD

#ifdef LEFT_BOARD
    #ifdef OLED_ENABLE
        #define LUNA_ENABLE
    #endif
#endif

#ifdef RIGHT_BOARD
    #ifdef OLED_ENABLE
        #define BONGO_CAT_ENABLE
    #endif
#endif

#define SPLIT_WPM_ENABLE
#define SPLIT_OLED_ENABLE
#define OLED_TIMEOUT 5000
#define OLED_FADE_OUT
#define OLED_FADE_OUT_INTERVAL 1

#define CUSTOM_LAYER_READ //if you remove this it causes issues - needs better guarding

#define TAPPING_FORCE_HOLD
#ifdef TAPPING_TERM
    #undef TAPPING_TERM
    #define TAPPING_TERM 200
#endif
#define ENCODER_DIRECTION_FLIP



/* ws2812 RGB LED */
#define RGB_DI_PIN D3

#ifdef RGB_MATRIX_ENABLE

#define RGBLED_NUM 72
#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
#define RGB_MATRIX_HUE_STEP 8
#define RGB_MATRIX_SAT_STEP 8
#define RGB_MATRIX_VAL_STEP 8
#define RGB_MATRIX_SPD_STEP 10
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_SPLIT {36,36}
#define SPLIT_TRANSPORT_MIRROR
#define ENABLE_RGB_MATRIX_RAINDROPS
#endif


#ifdef RGBLIGHT_ENABLE
    //#define RGBLIGHT_ANIMATIONS
	//#define RGBLIGHT_EFFECT_BREATHING
	//#define RGBLIGHT_EFFECT_RAINBOW_MOOD
	#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
	//#define RGBLIGHT_EFFECT_SNAKE
	//#define RGBLIGHT_EFFECT_KNIGHT
	//#define RGBLIGHT_EFFECT_CHRISTMAS
	//#define RGBLIGHT_EFFECT_STATIC_GRADIENT
	//#define RGBLIGHT_EFFECT_RGB_TEST
	//#define RGBLIGHT_EFFECT_ALTERNATING
	//#define RGBLIGHT_EFFECT_TWINKLE

    #define RGBLED_NUM 72
	#define RGBLED_SPLIT { 36, 36 }

    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17

    #define RGBLIGHT_SLEEP
    #define RGBLIGHT_SPLIT
    #define RGBLIGHT_LAYERS

    //RGB LED Conversion macro from physical array to electric array (+146). This results in better looking animated effects.
    //First section is the LED matrix, second section is the electrical wiring order, and the third section is the desired mapping
    #define LED_LAYOUT( \
    L00,  L01,  L02,  L03,  L04,  L05,                            R01,  R02,  R03,  R04,  R05,  R06, \
            L11,        L13,        L15,                            R11,        R13,        R15,      \
    L20,  L21,  L22,  L23,  L24,  L25,                            R21,  R22,  R23,  R24,  R25,  R26, \
    L30,  L31,  L32,  L33,  L34,  L35,  L36,                R30,  R31,  R32,  R33,  R34,  R35,  R36, \
    L40,  L41,  L42,  L43,  L44,  L45,                            R41,  R42,  R43,  R44,  R45,  R46, \
                L52,     L53,     L55,                            R51,     R52,     R54,             \
                L62,  L63,  L64,  L65,  L66,                R60,  R61,  R62,  R63,  R64            )\
    { \
        L36, L11, L13, L15, L55, L53, L52, L62, L40, L30, L20, L00, L01, L21, L31, L41, L63, L64, L42, L32, L22, L02, L03, L23, L33, L43, L65, L66, L44, L34, L24, L04, L05, L25, L35, L45, \
        R30, R15, R13, R11, R51, R52, R54, R64, R46, R36, R26, R06, R05, R25, R35, R45, R63, R62, R44, R34, R24, R04, R03, R23, R33, R43, R61, R60, R42, R32, R22, R02, R01, R21, R31, R41  \
        }

    //RGB LED logical order map
    #define RGBLIGHT_LED_MAP LED_LAYOUT( \
    68,  63,  57,  51,  45,  38,                            27,  22,  15,   9,  4,  0, \
         64,       52,       39,                            28,       16,       5,      \
    69,  65,  58,  53,  46,  40,                            29,  23,  17,  10,  6,  1, \
    70,  66,  59,  54,  47,  41,  36,                  34,  30,  24,  18,  11,  7,  2, \
    71,  67,  60,  55,  48,  42,                            31,  25,  19,  12,  8,  3, \
              61,     50,    43,                            32,     21,    13,             \
              62,  56,  49,  44,  37,                  35,  33,  26,  20,  14            )
#endif

