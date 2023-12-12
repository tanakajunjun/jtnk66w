/*
Copyright 2021 Salicylic_Acid

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
//#include "keymap.h"


#include "jtu_custom_keycodes.h"

static uint16_t key_timer = 0;

enum custom_keycodes {
  CUSTOM_KEY_CODE_A = JTU_SAFE_RANGE, // 変更
  CUSTOM_KEY_CODE_B,
  CUSTOM_KEY_CODE_C
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_VOLU,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, JU_LBRC, JU_RBRC, JU_BSLS,    JU_7,    JU_8,    JU_9,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_VOLD, KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, JU_SCLN, JU_QUOT,  KC_ENT,             KC_4,    KC_5,    JU_6,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_ESC , KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,  KC_UP ,             KC_1,    JU_2,    KC_3,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      KC_PSCR, KC_LCTL, KC_LGUI, KC_LALT,  KC_SPC,         KC_BSPC,   MO(1), JU_MINS,  JU_EQL,  JU_GRV, KC_INT1, KC_LEFT,  KC_DOWN,         KC_RGHT,    KC_0,  KC_DOT
  //|------------------------------------------------------------------------------------------------------------------------------------------------------------------'
  ),
  [1] = LAYOUT(
  //,-----------------------------------------------------------------------------------------------------------------------------------------------------------------.
      RGB_MOD, _______,RGB_MOD, RGB_RMOD, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, _______, _______, _______,   KC_F7,   KC_F8,   KC_F9,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+---------+--------+--------|
      RGB_RMOD,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,_______,             KC_F4,   KC_F5,   KC_F6,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+---------+--------+-------|
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PAGE_UP,         KC_F1,   KC_F2,   KC_F3,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+---------+--------+-------|
      RGB_TOG, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, KC_PAGE_DOWN,       KC_F10,  KC_F11, KC_F12
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+---------+--------+-------|
  ),
  [2] = LAYOUT(
  //,-----------------------------------------------------------------------------------------------------------------------------------------------------------------.
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+---------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+---------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+---------+--------+--------|
      _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+---------+--------+--------|
  ),
  [3] = LAYOUT(
  //,-----------------------------------------------------------------------------------------------------------------------------------------------------------------.
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+---------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+---------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+---------+--------+--------|
      _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+---------+--------+--------|
  )
};

#if defined(ENCODER_MAP_ENABLE)
enum layers{
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] =   {  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_LOWER] =  {  ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_RAISE] =  {  ENCODER_CCW_CW(KC_RIGHT, KC_LEFT)  },
    [_ADJUST] = {  ENCODER_CCW_CW(KC_UP, KC_DOWN) },
};
#endif

#ifdef RGB_MATRIX_ENABLE
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  //  KC_VOLU,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, JU_LBRC, JU_RBRC, JU_BSLS,    JU_7,    JU_8,    JU_9,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  //  KC_VOLD, KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, JU_SCLN, JU_QUOT,  KC_ENT,             KC_4,    KC_5,    JU_6,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  //  KC_ESC , KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,  KC_UP ,             KC_1,    JU_2,    KC_3,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  //  KC_PSCR, KC_LCTRL, KC_LGUI, KC_LALT,  KC_SPC,         KC_BSPC,   MO(1), JU_MINS,  JU_EQL,  JU_GRV, KC_INT1, KC_LEFT,  KC_DOWN,         KC_RGHT,    KC_0,  KC_DOT
  //|------------------------------------------------------------------------------------------------------------------------------------------------------------------'


  // Logical Layout
  // Columns
  // Left
  // 0  1  2  3  4  5  6  7  8 ROWS
  // __ 5  6 13 14 20 21 28 29
  // __ 4  7 12 15 19 22 27 30
  // 0  3  8 11 16 18 23 26 31
  // 1  2  9 10 17 __ 24 25 32

  //
  // Right
  // 0  1  2  3  4  5  6  7  8 ROWS
  //36 37 44 45 52 53 54 61 62
  //35 38 43 46 51 __ 55 60 63
  //34 39 42 47 50 __ 56 59 64
  //33 40 41 48 49 __ 57 58 65

  //
  // Physical Layout
  //  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17ROWS
  // __  5  6 13 14 20 21 28 29 36 37 44 45 52 53 54 61 62   0
  // __  4  7 12 15 19 22 27 30 35 38 43 46 51 __ 55 60 63   1
  //  0  3  8 11 16 18 23 26 31 34 39 42 47 50 __ 56 59 64   2
  //  1  2  9 10 17 __ 24 25 32 33 40 41 48 49 __ 57 58 65   3

led_config_t g_led_config = { {
	{NO_LED, 5,  6, 13, 14, 20, 21, 28, 29 },
	{NO_LED, 4,  7, 12, 15, 19, 22, 27, 30 },
	{ 0,  3,  8, 11, 16, 18, 23, 26, 31 },
	{ 1,  2,  9, 10, 17, NO_LED, 24, 25, 32 },

	{ 36,37,44,45,52,53,54,61,62},
	{ 35,38,43,46,51,NO_LED,55,60,63},
	{ 34,39,42,47,50,NO_LED,56,59,64},
    { 33,40,41,48,49,NO_LED,57,58,65}

}, { //横 15, 縦 18
    {  0, 36},{  0, 54}, //0-1
    { 15, 54},{ 15, 36},{ 15, 18},{ 15, 0}, //2-5
    { 30,  0},{ 30, 18},{ 30, 36},{ 30,54}, //6-9
    { 45, 54},{ 45, 36},{ 45, 18},{ 45, 0}, //10-13
    { 60,  0},{ 60, 18},{ 60, 36},{ 60,54}, //14-17
    { 75, 36},{ 75, 18},{ 75, 0}, //18-20
    { 90,  0},{ 90, 18},{ 90, 36},{ 90,54}, //21-24
    {105, 54},{105, 36},{105, 18},{105, 0}, //25-28
    {120,  0},{120, 18},{120, 36},{120,54}, //29-32
    {135, 54},{135, 36},{135, 18},{135, 0}, //33-36
    {150,  0},{150, 18},{150, 36},{150,54}, //37-40
    {165, 54},{165, 36},{165, 18},{165, 0}, //41-44
    {180,  0},{180, 18},{180, 36},{180,54}, //45-48
    {195, 54},{195, 36},{195, 18},{195, 0}, //49-52
    {210,  0}, //53
    {225,  0},{225, 18},{225, 36},{225,54}, //54-57
    {240, 54},{240, 36},{240, 18},{240, 0}, //58-61
    {255,  0},{255, 18},{255, 36},{255,54} //62-65
\

}, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4
} };

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}


#ifdef OLED_ENABLE
#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
	if(key_timer > 0){
		key_timer -= 1;
	} else {
		key_timer = 0;
	}
    if (key_timer > 0) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
        oled_scroll_left();

    }
    return false;
}
/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}*/
#endif // OLED_ENABLE

bool should_process_keypress(void) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // 以下追加
  if (record->event.pressed) {
    oled_scroll_off();
    oled_clear();
    key_timer = 300;
    set_keylog(keycode, record);
  }
  bool continue_process = process_record_user_jtu(keycode, record);
  if (continue_process == false) {
    return false;
  }

  return true;
}
#endif

