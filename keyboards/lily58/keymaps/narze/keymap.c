#include QMK_KEYBOARD_H
#include "narze.h"
#include "keymap_colemak.h"
#include "keymap_steno.h"

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

enum layers {
    _QWERTY,
    _COLEMAK,
    _QWOC,
    _LOWER,
    _RAISE,
    _PLOVER,
    _SUPERDUPER,
    _DEV,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  PLOVER,
  LOWER,
  RAISE,
  ADJUST,
  SUPERDUPER,
  DEV,
  SDTOGG, // Toggle SuperDuper
  GUI_UNDS,
  LSFT_LPRN,
  RSFT_RPRN,
  EXT_PLV,
};

// Narze : Custom Macros
#define HPR_ESC ALL_T(KC_ESC)
#define SFT_ENT SFT_T(KC_ENT)

enum process_combo_event {
    CB_SUPERDUPER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  F19 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Hp/Esc|   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Sft/( |   Z  |   X  |   C  |   V  |   B  |-------.    ,-------|   N  |   M  |   ,  |   .  |   /  |Sft/) |
 * |------+------+------+------+------+------| Swap  |    | Swap  |------+------+------+------+------+------|
 * |Rse/[ | Ctrl | Alt  | GUI/_|Lower | Space|-------|    |-------| Space| Raise| Bksp | Alt  | Ctrl | Low/]|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /Space  /       \Enter \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_F19, \
  HPR_ESC, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  LSFT_LPRN, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  RSFT_RPRN, \
  LT(_RAISE, KC_LBRC), KC_LCTL, KC_LALT, GUI_UNDS,LOWER,  KC_SPC, SH_TT,  SH_TT,  KC_SPC,  RAISE,   KC_BSPC, KC_RALT, KC_RCTL,   LT(_LOWER, KC_RBRC), \
                             _______, _______, _______, KC_SPC,   KC_ENT,   _______,   _______, _______ \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |      |   _  |   +  |   {  |   }  |   |  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD, \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                    _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                    _______, _______, _______,_______, _______, _______,\
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
                             _______, _______, _______, _______, _______,  _______, _______, _______\
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   ~  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
  S(KC_GRV),KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                      _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______, _______, _______, _______, _______, \
                             _______, _______, _______,  _______, _______,  _______, _______, _______ \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
  PLOVER,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
),
/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  FN  |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |  PWR | RES1 | RES2 |
 * `-----------------------------------------------------------------------------------'
 */

// [_PLOVER] = {
//   {STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC },
//   {STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR },
//   {XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR },
//   {EXT_PLV, XXXXXXX, XXXXXXX, STN_A,   STN_O,   XXXXXXX, XXXXXXX, STN_E,   STN_U,   STN_PWR, STN_RE1, STN_RE2}
// },
/* Plover
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |  T←  |  T→  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | Alt  | [SuperDuper]| Bksp | Gui  |                    |  ←   |  ↓   |   ↑  |  →   | Del  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_PLOVER] = LAYOUT( \
  STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,                    STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC, \
  STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,                   STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR, \
  XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,                   STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR, \
  EXT_PLV, XXXXXXX, XXXXXXX, STN_A,   STN_O,   XXXXXXX, KC_LSFT, KC_LSFT, XXXXXXX, STN_E,   STN_U,   STN_PWR, STN_RE1, STN_RE2,\
                            QK_STENO_GEMINI, QK_STENO_BOLT, _______, KC_LSFT, KC_LSFT,  _______, _______, _______ \
),
/* SuperDuper : https://gist.github.com/narze/861e2167784842d38771
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |  T←  |  T→  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | Alt  | [SuperDuper]| Bksp | Gui  |                    |  ←   |  ↓   |   ↑  |  →   | Del  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_SUPERDUPER] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, S(LGUI(KC_LBRC)), S(LGUI(KC_RBRC)), _______, _______, \
  _______, KC_LALT, _______, _______, KC_BSPC, KC_LGUI,                   KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  KC_DEL, _______, \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, KC_LSFT, KC_LSFT, _______, _______, _______, _______, _______, _______,\
                             _______, _______, _______, KC_LSFT, KC_LSFT,  _______, _______, _______ \
),
/* Dev Layer
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_DEV] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
),
/* Colemak
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_COLEMAK] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
),
/* QWOC
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_QWOC] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
),
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    set_superduper_key_combos();
    steno_set_mode(STENO_MODE_GEMINI);

    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif

}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
        set_superduper_key_combo_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case PLOVER:
      if (!record->event.pressed) {
        layer_on(_PLOVER);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        layer_off(_PLOVER);
      }
      return false;
      break;

    // Macros

    // 1. Hold for LGUI, tap for Underscore
    case GUI_UNDS:
        perform_space_cadet(record, KC_LGUI, KC_LSFT, KC_MINS);
        return false;

    // 2. Hold for LSHIFT, tap for Parens open
    case LSFT_LPRN:
        perform_space_cadet(record, KC_LSFT, KC_LSFT, KC_9);
        return false;

    // 3. Hold for RSHIFT, tap for Parens close
    case RSFT_RPRN:
        perform_space_cadet(record, KC_RSFT, KC_RSFT, KC_0);
        return false;
  }
  return true;
}

void process_combo_event(uint8_t combo_index, bool pressed) {
    if (pressed) {
        switch(combo_index) {
            case CB_SUPERDUPER:
                layer_on(_SUPERDUPER);
                break;
        }
    } else {
        layer_off(_SUPERDUPER);
        unregister_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT)); // Sometimes mods are held, unregister them
    }
}

// matrix_setup is already used
void keyboard_pre_init_user(void) {
    set_superduper_key_combos();
}

char layer_state_str[24];

const char *read_layer(void) {
  switch (layer_state)
  {
  case _QWERTY:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Default");
    break;
  case 1 << _COLEMAK:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Colemak");
    break;
  case 1 << _QWOC:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Qwerty2Colemak");
    break;
  case 1 << _LOWER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Lower");
    break;
  case 1 << _RAISE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Raise");
    break;
  case 1 << _SUPERDUPER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: SuperDuper");
    break;
  case 1 << _DEV:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Dev");
    break;
  case 1 << _ADJUST:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Adjust");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
  }

  return layer_state_str;
}
