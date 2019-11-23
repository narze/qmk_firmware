#include "lily58.h"
#include "ssd1306.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
#ifdef SSD1306OLED
  return process_record_gfx(keycode,record) && process_record_user(keycode, record);
#else
  return process_record_user(keycode, record);
#endif
}

#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
        {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}},
        {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}},
        {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}},
        {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}},
        {{0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}},
        {{5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
        {{5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
        {{5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
        {{5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}},
        {{5, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 4}},
};
#endif
