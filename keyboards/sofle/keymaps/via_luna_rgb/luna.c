#ifdef LUNA_ENABLE
/* KEYBOARD PET START */

/* settings */
#define MIN_WALK_SPEED 10
#define MIN_RUN_SPEED 40

/* advanced settings */
#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
#define ANIM_SIZE 96 // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

/* timers */
uint32_t anim_timer = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
int current_wpm = 0;
led_t led_usb_state;

bool isSneaking = false;
bool isJumping = false;
bool showedJump = true;

/* Sit */
static const char PROGMEM sit_1_block_x_map[] = {
0x00, 0xc0, 0xff, 0x03, 0xc0, 0x3f, 0xe0, 0x03, 0xc0, 0xff, 0xff, 0x00
};

static const char PROGMEM sit_1_block_x_list[] = {
0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0xe0, 0x10, 0x08, 0x68,
0x10, 0x08, 0x04, 0x03, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20,
0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f
};

static const char PROGMEM sit_2_block_x_map[] = {
0x00, 0xc0, 0xff, 0x03, 0xe0, 0x3f, 0xe0, 0x03, 0xc0, 0xff, 0xff, 0x00
};

static const char PROGMEM sit_2_block_x_list[] = {
0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0xe0, 0x90, 0x08, 0x18,
0x60, 0x10, 0x08, 0x04, 0x03, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10,
0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f
};

/* Walk */
static const char PROGMEM walk_1_block_x_map[] = {
0xe0, 0xff, 0xff, 0x0f, 0xe0, 0x21, 0x81, 0x0f, 0x80, 0xff, 0xff, 0x01
};

static const char PROGMEM walk_1_block_x_list[] = {
0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x70, 0x08, 0x14, 0x08,
0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x07, 0x08, 0xfc, 0x01, 0x80, 0x01, 0x08, 0x18, 0xea,
0x10, 0x0f, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03, 0x06, 0x18, 0x20, 0x20, 0x3c,
0x0c, 0x12, 0x1e, 0x01
};

static const char PROGMEM walk_2_block_x_map[] = {
0xc0, 0x1f, 0xfe, 0x07, 0xe0, 0xff, 0xa1, 0x0f, 0x80, 0xff, 0xff, 0x01, 0x01
};

static const char PROGMEM walk_2_block_x_list[] = {
0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48,
0xf0, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x01, 0x10, 0x30,
0xd5, 0x20, 0x1f, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x02, 0x1c, 0x14, 0x08,
0x10, 0x20, 0x2c, 0x32, 0x01
};

/* Run */
static const char PROGMEM run_1_block_x_map[] = {
0xf0, 0xff, 0xff, 0x3f, 0xf0, 0x21, 0x80, 0x3f, 0xe0, 0xff, 0xff, 0x07, 0x01
};

static const char PROGMEM run_1_block_x_list[] = {
0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c,
0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x80,
0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02,
0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06,
};

static const char PROGMEM run_2_block_x_map[] = {
0x78, 0x80, 0xff, 0x1f, 0xf8, 0x7f, 0x80, 0x3f, 0x00, 0xfe, 0xff, 0x01, 0x01
};

static const char PROGMEM run_2_block_x_list[] = {
0xe0, 0x10, 0x10, 0xf0, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20,
0x40, 0x80, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x10,
0xb0, 0x50, 0x55, 0x20, 0x1f, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20,
0x18, 0x0c, 0x14, 0x1e, 0x01,
};

/* Bark */
static const char PROGMEM bark_1_block_x_map[] = {
0x3e, 0xe0, 0xff, 0x07, 0xfe, 0x1f, 0xf0, 0x07, 0x80, 0xff, 0xff, 0x01, 0x01
};

static const char PROGMEM bark_1_block_x_list[] = {
0xc0, 0x20, 0x10, 0xd0, 0x30, 0x80, 0x80, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08,
0xb0, 0x40, 0x80, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x80,
0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04,
0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06,
};

static const char PROGMEM bark_2_block_x_map[] = {
0x1e, 0xe0, 0xff, 0x0f, 0xfe, 0x1f, 0xe0, 0xff, 0x80, 0xff, 0xff, 0x01, 0x01
};

static const char PROGMEM bark_2_block_x_list[] = {
0xe0, 0x10, 0x10, 0xf0, 0x80, 0x80, 0x40, 0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08,
0xb0, 0x40, 0x80, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x80,
0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28,
0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06,
};

/* Sneak */
static const char PROGMEM sneak_1_block_x_map[] = {
0xc0, 0x0f, 0xbc, 0x03, 0xf0, 0xff, 0xcf, 0x1f, 0xc0, 0xff, 0xff, 0x0f, 0x01
};

static const char PROGMEM sneak_1_block_x_list[] = {
0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0xc0, 0x40, 0x40, 0x80, 0x80, 0x40, 0x80, 0x1e, 0x21, 0xf0,
0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x09, 0x01, 0x80,
0x80, 0xab, 0x04, 0xf8, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06, 0x18, 0x20,
0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01,
};

static const char PROGMEM sneak_2_block_x_map[] = {
0xc0, 0x07, 0xfc, 0x07, 0xf0, 0xff, 0x47, 0x1f, 0xc0, 0xff, 0xff, 0x07, 0x01
};

static const char PROGMEM sneak_2_block_x_list[] = {
0x80, 0x40, 0x40, 0x40, 0x80, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x3e, 0x41,
0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x04, 0x40, 0x40,
0x55, 0x82, 0x7c, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04, 0x18, 0x10, 0x08,
0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01,
};

/* logic */
static void render_luna(int LUNA_X, int LUNA_Y) {
    current_wpm = get_current_wpm();
    led_usb_state = host_keyboard_led_state();

    /* animation */
    void animate_luna(void) {
        uint8_t y_offset = 0;

        /* jump */
        if (isJumping || !showedJump) {

            /* clear */
            oled_set_cursor(LUNA_X,LUNA_Y +2);
            oled_write("     ", false);

            y_offset = LUNA_Y -1;

            showedJump = true;
        } else {

            /* clear */
            oled_set_cursor(LUNA_X,LUNA_Y -1);
            oled_write("     ", false);

            y_offset = LUNA_Y;
        }

        /* switch frame */
        current_frame = (current_frame + 1) % 2;

        /* current status */
        if(led_usb_state.caps_lock) {
            if(current_frame == 0) {
                oled_write_compressed_P(bark_1_block_x_map, bark_1_block_x_list, y_offset, ANIM_SIZE);
            } else {
                oled_write_compressed_P(bark_2_block_x_map, bark_2_block_x_list, y_offset, ANIM_SIZE);
            }
        } else if(isSneaking) {
            if(current_frame == 0) {
                oled_write_compressed_P(sneak_1_block_x_map, sneak_1_block_x_list, y_offset, ANIM_SIZE);
            } else {
                oled_write_compressed_P(sneak_2_block_x_map, sneak_2_block_x_list, y_offset, ANIM_SIZE);
            }
        } else if(current_wpm <= MIN_WALK_SPEED) {
            if(current_frame == 0) {
                oled_write_compressed_P(sit_1_block_x_map, sit_1_block_x_list, y_offset, ANIM_SIZE);
            } else {
                oled_write_compressed_P(sit_2_block_x_map, sit_2_block_x_list, y_offset, ANIM_SIZE);
            }
        } else if(current_wpm <= MIN_RUN_SPEED) {
            if(current_frame == 0) {
                oled_write_compressed_P(walk_1_block_x_map, walk_1_block_x_list, y_offset, ANIM_SIZE);
            } else {
                oled_write_compressed_P(walk_2_block_x_map, walk_2_block_x_list, y_offset, ANIM_SIZE);
            }
        } else {
            if(current_frame == 0) {
                oled_write_compressed_P(run_1_block_x_map, run_1_block_x_list, y_offset, ANIM_SIZE);
            } else {
                oled_write_compressed_P(run_2_block_x_map, run_2_block_x_list, y_offset, ANIM_SIZE);
            }
        }
    }

    /* animation timer */
    if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        if(is_oled_on()) animate_luna();
    }
}

/* KEYBOARD PET END */

#endif
