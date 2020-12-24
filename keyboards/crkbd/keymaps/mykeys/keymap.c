/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#define CL(x)   LCTL((x))
#define SF(x)   LSFT((x))
#define AL(x)   LALT((x))
#define TC(x)   MT(CL((x)), (x))
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define JA_CLON KC_QUOT  // : and +
#define JA_AT   KC_LBRC  // @ and `
#define JA_HAT  KC_EQL   // ^ and ~

#define JA_EQL  SF(KC_MINS) // =
#define JA_PLUS SF(KC_SCLN) // +
#define JA_AMPR SF(KC_6)    // &
#define JA_PIPE SF(KC_INT3)  //|
#define JA_QUOT SF(KC_7)    // '
#define JA_DQUO SF(KC_2)    // "
#define JA_GRV  SF(KC_LBRC) // `
#define JA_EXLM SF(KC_1)    // !
#define JA_QUES SF(KC_SLSH) // ?
#define JA_TILD SF(KC_EQL) //  ~
#define JA_HASH SF(KC_3)    // "
#define JA_PAR  SF(KC_5)    // "
#define JA_DLR  SF(KC_4)    // "

#define JA_ENUN KC_RO      // \ and _ (EN mark and UNder score)
#define JA_ENVL KC_JYEN    // \ and | (EN mark and Vertical Line)
#define JA_LPRN SF(KC_8)    // (
#define JA_RPRN SF(KC_9)    // )
#define JA_LBRC KC_RBRC    // [ and {
#define JA_RBRC KC_BSLS    // ] and }
#define JA_LCBR SF(KC_RBRC) // {
#define JA_RCBR KC_PIPE    // }


enum Layer_names{ LyBase = 0
                , LySym
                , LyFnc
                , LyKbdCtrl
                , LyEndNum
                };
static uint16_t is_layer_on[LyEndNum] = {};

enum Macro_states{ SwBase    = 10 * LyBase
                 , SwSymSPC  = 10 * LySym
                 , SwFncENT  = 10 * LyFnc
                 , SwKCtlSPC = 10 * LyKbdCtrl
                 , SwEndNum  = 10 * LyEndNum
                 , McDummy
                 , McKana
                 , McEisu
                 , McTest
                 };


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LyBase] = LAYOUT_split_3x6_3(
  //,------------------------------------------------------------.                    ,------------------------------------------------------.
      KC_TAB       ,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_MINS,
  //|---------------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------+--------|
      CTL_T(JA_AT) ,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN , CTL_T(JA_CLON),
  //|---------------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------+--------|
      SFT_T(JA_HAT),    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH , SFT_T(JA_ENUN),
  //|---------------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------+--------|
                                               KC_RALT, KC_BSPC, SwSymSPC,     KC_DEL, SwFncENT, KC_ENT
                                           //`----------------------------'  `----------------------------'
  ),

  [LySym] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC      , JA_PLUS, KC_PMNS, KC_SLSH, KC_PAST,  JA_EQL,                      JA_AMPR, JA_QUOT, JA_LPRN, JA_RPRN, JA_EXLM, JA_HASH,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CTL_T(JA_AT) ,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      JA_PIPE, JA_DQUO, JA_LBRC, JA_RBRC, JA_QUES, JA_PAR,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      SFT_T(JA_HAT),    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      KC_DOT,   JA_GRV, JA_LCBR, JA_RCBR, JA_TILD, JA_DLR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_RALT, KC_LGUI, _______,     KC_DEL, MO(3),  KC_ENT
                                     //`--------------------------'  `--------------------------'
  ),

  [LyFnc] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX,  McEisu,  McKana,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, KC_RCTL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX,  KC_F10,   KC_F7,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_INS, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(3),  KC_ESC,     KC_RALT, _______, KC_ENT
                                      //`--------------------------'  `--------------------------'
  ),

  [LyKbdCtrl] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_ESC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};


//const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
//{ // MACRODOWN only works in this function
//  //  uint8_t cur_lay = biton32(layer_state);
//    switch(id) {
//        case Dummy:
//            return macro_divide_with_timig( record, 200
//                                          , MACRO(D(W)  , D(LSFT)      , END)
//                                          , MACRO(W(200), U(LSFT), U(W), END)
//                                          );
//            break;
//        default:
//            break;
//    }
//    return MACRO_NONE;
//};



#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_master) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_NUM_SYMBOL 2
#define L_FUNCTION 4
#define L_KBD_CONTROL 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    uint8_t cur_lay = biton32(layer_state);
    switch (cur_lay) {
        case LyBase:
            oled_write_ln_P(PSTR("BaseKey"), false);
            break;
        case LySym:
            oled_write_ln_P(PSTR("NumSymbol"), false);
            break;
        case LyFnc:
            oled_write_ln_P(PSTR("Functions"), false);
            break;
        case LyKbdCtrl:
            oled_write_ln_P(PSTR("KeybordCtrl"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Default"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
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

void oled_task_user(void) {
    if (is_master) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
}



//static uint16_t key_start;
//const macro_t *macro_divide_with_timig(keyrecord_t *record, uint16_t st, macro_t *m_fast, macro_t *m_slow) {
//    if (record->event.pressed) {
//        key_start = timer_read();
//    } else { 
//        return (st <= timer_elapsed(st)) ? m_fast : m_slow;
//    }
//    return MACRO_NONE;
//}
//

bool hit_code(uint16_t k_tgt, keyrecord_t *r) {
    if (r->event.pressed) {
        register_code(k_tgt);
    } else {
        unregister_code(k_tgt);
    }
    return false;
}

bool hit_code_immedi(uint16_t k_tgt) {
    register_code(k_tgt);
    unregister_code(k_tgt);
    return false;
}


//static bool is_l_symbol = false;
//static bool is_l_func = false;
bool switch_layer(uint16_t keycode, keyrecord_t *record, uint16_t k_base) {
    uint16_t tgt_lay= keycode / 10;

    if (record->event.pressed) {
        is_layer_on[tgt_lay] = timer_read();
        layer_on( tgt_lay );
    } else {
        layer_off( tgt_lay );
        if ( 0 < is_layer_on[tgt_lay] && timer_elapsed(is_layer_on[tgt_lay]) <= 300 ) {
            hit_code_immedi(k_base);
        }
        is_layer_on[tgt_lay] = 0;
    }

    return false;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }

    switch (keycode) {
        case SwSymSPC:
            return switch_layer( keycode, record, KC_SPC );
        case SwFncENT:
            return switch_layer( keycode, record, KC_ENT );
        default:
            if (record->event.pressed) {
                is_layer_on[LySym] = 0;
                is_layer_on[LyFnc] = 0;
            }
            switch (keycode) {
                case McKana:
                    return hit_code(KC_LANG1,record);
                case McEisu:
                    return hit_code(KC_LANG2,record);
                case McTest:
                    break;
                default:
                    break;
            }
            break;
    }

    return true;
}

#endif // OLED_DRIVER_ENABLE
