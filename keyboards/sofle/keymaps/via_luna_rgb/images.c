#if defined(LEFT_BOARD) || defined(LUNA_ENABLE) || defined(BONGO_CAT_ENABLE)
static void oled_write_compressed_P(const char* input_block_map, const char* input_block_list, const uint16_t offset, const uint16_t bytes) {
    uint16_t block_index = 0;
    for (uint16_t i=0; i<bytes; i++) {
        uint8_t bit = i%8;
        uint8_t map_index = i/8;
        uint8_t _block_map = (uint8_t)pgm_read_byte_near(input_block_map + map_index);
        uint8_t nonzero_byte = (_block_map & (1 << bit));
        if (nonzero_byte) {
            const char data = (const char)pgm_read_byte_near(input_block_list + block_index++);
            oled_write_raw_byte(data, i+(32*offset));
        } else {
            const char data = (const char)0x00;
            oled_write_raw_byte(data, i+(32*offset));
        }
    }
}
#endif

#ifdef LEFT_BOARD
/* 32 * 14 os logos */
static const char PROGMEM windows_logo_block_x_map[] = {
0x00, 0x78, 0x3f, 0x00, 0x00, 0x78, 0x3f, 0x00
};

static const char PROGMEM windows_logo_block_x_list[] = {
0xbc, 0xbc, 0xbe, 0xbe, 0xbe, 0xbe, 0xbf, 0xbf, 0xbf, 0xbf, 0x07, 0x07, 0x0f, 0x0f, 0x0f, 0x0f,
0x1f, 0x1f, 0x1f, 0x1f
};

static const char PROGMEM mac_logo_block_x_map[] = {
0x00, 0xf8, 0x3f, 0x00, 0x00, 0xf8, 0x3f, 0x00
};

static const char PROGMEM mac_logo_block_x_list[] = {
0xc0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf0, 0xf6, 0xfb, 0xfb, 0x38, 0x10, 0x01, 0x07, 0x0f, 0x1f, 0x1f,
0x0f, 0x0f, 0x1f, 0x1f, 0x0f, 0x06
};
#endif
