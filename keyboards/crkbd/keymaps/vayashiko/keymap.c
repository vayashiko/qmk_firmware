#include QMK_KEYBOARD_H
#include "bootloader.h"
#include "keymap_jp.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------------.                ,-----------------------------------------------------------.
        KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  KC_BSPC,\
  //|---------+---------+---------+---------+---------+---------|                |---------+---------+---------+---------+---------+---------|
      KC_ALTKN,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                      KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,  KC_QUOT,\
  //|---------+---------+---------+---------+---------+---------|                |---------+---------+---------+---------+---------+---------|
       KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                      KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,  KC_RSFT,\
  //|---------+---------+---------+---------+---------+---------+------|  |------+---------+---------+---------+---------+---------+---------|
                                              KC_CTLTB, KC_LOWER,KC_SPC,   KC_ENT, KC_RAISE, KC_ALTKN \
                                          //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------------.                ,-----------------------------------------------------------.
     KC_DELETE,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                 KC_XXXXX,     KC_7,     KC_8,     KC_9,  JP_MINS, KC_DELETE,\
  //|---------+---------+---------+---------+---------+---------|                |---------+---------+---------+---------+---------+---------|
      KC_ALTKN,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,                 KC_XXXXX,     KC_4,     KC_5,     KC_6,  JP_PLUS,  LSFT(KC_CAPS),\
  //|---------+---------+---------+---------+---------+---------|                |---------+---------+---------+---------+---------+---------|
       KC_LSFT,   KC_F11,   KC_F12,   KC_F13,   KC_F14,   KC_F15,                     KC_0,     KC_1,     KC_2,     KC_3,   KC_DOT,  KC_RSFT,\
  //|---------+---------+---------+---------+---------+---------+------|  |------+---------+---------+---------+---------+---------+---------|
                                              KC_CTLTB, KC_LOWER,KC_SPC,   KC_ENT, KC_RAISE, KC_ALTKN \
                                          //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------------.                ,-----------------------------------------------------------.
        KC_ESC,  JP_EXLM,   JP_DQT,  JP_HASH,   JP_DLR,  JP_PERC,                   KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_MINS,  JP_CIRC,\
  //|---------+---------+---------+---------+---------+---------|                |---------+---------+---------+---------+---------+---------|
      KC_ALTKN,   KC_GRV, KC_XXXXX, KC_XXXXX,  KC_MHEN,     KC_G,                  KC_XXXXX,  KC_HENK,  JP_LBRC,  JP_RBRC, KC_XXXXX,  KC_JYEN,\
  //|---------+---------+---------+---------+---------+---------|                |---------+---------+---------+---------+---------+---------|
       KC_LSFT, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX,                  JP_EQL,JP_AT,LSFT(JP_LBRC),LSFT(JP_RBRC), KC_XXXXX,  JP_UNDS,\
  //|---------+---------+---------+---------+---------+---------+------|  |------+---------+---------+---------+---------+---------+---------|
                                              KC_CTLTB, KC_LOWER,KC_SPC,   KC_ENT, KC_RAISE, KC_ALTKN \
                                          //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------------.                ,-----------------------------------------------------------.
        KC_ESC,  KC_LRST, KC_XXXXX, KC_XXXXX,     KC_R, KC_XXXXX,                  KC_XXXXX, KC_XXXXX,    KC_UP, KC_XXXXX, KC_XXXXX, KC_XXXXX,\
  //|---------+---------+---------+---------+---------+---------|                |---------+---------+---------+---------+---------+---------|
      KC_ALTKN,  KC_HOME,     KC_S, KC_XXXXX,   KC_END,     KC_G,                  KC_XXXXX,  KC_LEFT,  KC_DOWN, KC_RIGHT, KC_XXXXX, KC_XXXXX,\
  //|---------+---------+---------+---------+---------+---------|                |---------+---------+---------+---------+---------+---------|
       KC_LSFT,  KC_LHUD,  KC_LSAD,  KC_LVAD, KC_XXXXX, KC_XXXXX,                  KC_XXXXX, KC_XXXXX,  KC_DOWN, KC_XXXXX, KC_XXXXX,  KC_RSFT,\
  //|---------+---------+---------+---------+---------+---------+------|  |------+---------+---------+---------+---------+---------+---------|
                                              KC_GUIEI, KC_LOWER,KC_SPC,   KC_ENT, KC_RAISE, KC_ALTKN \
                                          //`--------------------------'  `--------------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
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
const char *read_layer_state(void);
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
    matrix_write_ln(matrix, read_layer_state());
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
        persistent_default_layer_set(1UL<<_QWERTY);
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
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}
