#ifdef RGBLIGHT_ENABLE
#define INDICATOR_BRIGHTNESS 30

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

// Light combinations
#define SET_UNDERGLOW(hsv) \
	{1, 6, hsv}, \
    {36+1, 6,hsv}
#define SET_LAYER_ID(hsv) 	\
	{34, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {36+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}

char layer_state_str[70];
// Now define the array of layers. Later layers take precedence

// QWERTY,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_RED)

);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(

    layer_qwerty_lights
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

	rgblight_mode(10);// haven't found a way to set this in a more useful way

}
#endif

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_kb() {

    RGB rgb;
    
    
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case _RAISE:
        {
            HSV hsv = {30, 218, 100};
            rgb = hsv_to_rgb(hsv);
            break;
        }
        case _LOWER:
        {
            HSV hsv = {123,  90, 100};
            rgb = hsv_to_rgb(hsv);           
            break;
        }
        case _ADJUST:
        {
            HSV hsv = {191, 255, 100};
            rgb = hsv_to_rgb(hsv);            
            break;
        }
        default:
        {
            HSV hsv = {106, 255, 100};
            rgb = hsv_to_rgb(hsv);
            break;
        }
    }
    rgb_matrix_set_color(0, rgb.r, rgb.g, rgb.b);
    rgb_matrix_set_color(36, rgb.r, rgb.g, rgb.b);
}
#endif