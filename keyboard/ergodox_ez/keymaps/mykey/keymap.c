#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define JA_CLON KC_QUOT  // : and +
#define JA_AT   KC_LBRC  // @ and `
#define JA_HAT  KC_EQL   // ^ and ~
#define JA_ENUN KC_RO    // \ and _ (EN mark and UNder score)
#define JA_ENVL KC_JYEN  // \ and | (EN mark and Vertical Line)
#define JA_LBRC KC_RBRC  // [ and {
#define JA_RBRC KC_BSLS  // ] and }

#define CL(x)   LCTL((x))
#define SF(x)   LSFT((x))
#define AL(x)   LALT((x))
#define TC(x)   MT(CL((x)), (x))
#define _____   KC_TRNS

/*
#define Base 0  // layer: default
#define Medi 1  // layer: Medi
#define Sai  2  // layer: Sai
 */
enum Layer_names{ Base
                , Medi
                , Sai
                , Clip
                };
enum Macro_stat{ Dummy
               , Cut_paste
               , C_bucket
               , C_delete
               , C_add_l
               , C_del_l
               , C_transpa
               };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
/* Keymap 0: Base layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    | 1    | 2    | 3    | 4    | 5    | Z/H  |           | ^~   | 6    | 7    | 8    | 9    | 0    | -=     |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    | Q    | W    | E    | R    | T    | paste|           | Up   | Y    | U    | I    | O    | P    | \|     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CTRL   | A    | S    | D    | F    | G    |------|           |------| H    | J    | K    | L    | ;+   | :* /Ctl|
 * |--------+------+------+------+------+------| copy |           |      |------+------+------+------+------+--------|
 * | LShift | Z    | X    | C    | V    | B    | /cut |           | Down | N    | M    | ,<   | .>   | /?   | \_ /Sft|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | CTRL |      |      | Alt  | BS   |                                       | Enter| [{   | ]}   | @`   |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      | save |       | Home | End  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       | PgUp |        |      |
 *                                 | Space| Space|------|       |------|        |      |
 *                                 | /Lyr1|      | Del  |       | PgDn | Left   | Right|
 *                                 `--------------------'       `----------------------'
 */
{ [Base] = KEYMAP( KC_ESC  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_GRV //MT(KC_LANG1, KC_LANG2)
                 , KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , CL(KC_V)
                 , KC_LCTL , KC_A    , KC_S    , KC_D    , KC_F    , KC_G
                 , KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , M(Cut_paste)
                 , KC_LCTL , KC_NO   , KC_NO   , KC_LALT , KC_BSPC
                                                                   , KC_NO   , CL(KC_S)
                                                                             , KC_NO
                                                , LT(Medi, KC_SPC) , KC_SPC  , KC_DELT

                 /*      ^^ LEFT ^^      /      vv RIGHT vv      */
                 , JA_HAT  , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_MINS
                 , KC_UP   , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , JA_ENVL
                           , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , CTL_T(JA_CLON)
                 , KC_DOWN , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , SFT_T(JA_ENUN)
                                     , KC_ENT  , JA_LBRC , JA_RBRC , JA_AT   , JA_HAT
                 , KC_HOME , KC_END
                 , KC_PGUP
                 , KC_PGDN , KC_LEFT  , KC_RGHT
                 )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Keymap 1: Medi layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        | F1   | F4   | F6   | F8   | F9   |      |           | Lyr0 | F11  | F12  | F13  | F14  | F15  | Lyr2   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | M-Up |      |      |      |           | WH-U |      |      |      |      |      | Lyr3   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |LClick| M-Lf | M-Dn | M-Ri |RClick|------|           |------| Left | Down | Up   | Right|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | F2   | F3  |F5/CrlF5| F7  | F10  |      |           | WH-D |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       | Enter|LClick|LClick|RClick|RClick|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       | Home | End  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       | PgUp |        |      |
 *                                 | Lyr0 |      |------|       |------|        |      |
 *                                 |      |      | reset|       | PgDn | Left   | Right
 *                                 `--------------------'       `----------------------'
 */
, [Medi] = KEYMAP( _____   , KC_F1   , KC_F4   , KC_F6    , KC_F8    , KC_F9   , _____
                 , _____   , KC_NO   , KC_NO   , KC_MS_U  , KC_NO    , KC_NO   , _____
                 , _____   , KC_BTN1 , KC_MS_L , KC_MS_D  , KC_MS_R  , KC_BTN2
                 , _____   , KC_F2   , KC_F3   , TC(KC_F5), KC_F7    , KC_F10  , _____
                 , _____   , _____   , _____   , _____    , _____
                                                                     , KC_NO   , KC_NO
                                                                               , KC_NO
                                                          , _____    , KC_NO   , RESET
                 /*      ^^ LEFT ^^      /      vv RIGHT vv      */
                 , TG(Base), KC_F11  , KC_F12  , KC_F13   , KC_F14   , KC_F15  , TG(Sai)
                 , KC_WH_U , KC_NO   , KC_NO   , KC_MS_U  , KC_NO    , KC_NO   , TG(Clip)
                           , KC_LEFT , KC_DOWN , KC_UP    , KC_RGHT  , KC_NO   , KC_NO
                 , KC_WH_D , KC_NO   , KC_NO   , KC_NO    , KC_NO    , KC_NO   , KC_NO
                                     , KC_ENT  , KC_BTN1  , KC_BTN1  , KC_BTN2 , KC_BTN2
                 , KC_HOME , KC_END
                 , KC_PGUP
                 , KC_PGDN , KC_LEFT  , KC_RGHT
                 )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Keymap 2~: Draw
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | same   |  F1  |  F2  |  F3  |  F4  |  F5  | Esc  |           | F7   |  F8  |  F9  | F10  |  F11 |  F12 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | same   |      |      |      |      |      | paste|           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | same   |bucket| size+| rope+| undo |transp|----- |           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------| copy |           |      |------+------+------+------+------+--------|
 * | same   |delete| size-| rope-| redo |erease| /cut |           |      |      | pen  |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | same | same | same | same | same |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | save |      |       |      | Mute |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |L Rote|R Rote|------|       |------| Vol- | Vol+ |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
, [Sai] =  KEYMAP( _____   , KC_NO      , KC_NO   , KC_NO     , KC_NO   , KC_NO   , _____
                 , _____   , KC_NO      , KC_UP   , CL(KC_L)  , KC_NO   , KC_T    , _____
                 , _____   , AL(KC_DELT), JA_RBRC , KC_L      , CL(KC_Z), KC_MINS
                 , _____   , KC_D       , JA_LBRC , AL(KC_L)  , CL(KC_Y), KC_E    , _____
                 , _____   , _____      , _____   , _____     , _____
                                                                        , KC_H    , CL(KC_S)
                                                                                  , KC_NO
                                                              , KC_DELT , KC_END  , KC_INS
                 /*      ^^ LEFT ^^      /      vv RIGHT vv      */
                 , _____   , KC_NO      , KC_NO   , KC_NO     , KC_NO   , KC_NO   , _____
                 , _____   , KC_NO      , KC_NO   , KC_NO     , KC_NO   , KC_NO   , _____
                           , _____      , _____   , _____     , _____   , KC_NO   , KC_NO
                 , _____   , KC_NO      , KC_NO   , KC_NO     , KC_NO   , KC_NO   , KC_NO
                                        , KC_ENT  , KC_NO     , KC_NO   , KC_NO   , MO(Base)
                 , KC_HOME , KC_END
                 , KC_PGUP
                 , KC_PGDN , KC_LEFT  , KC_RGHT
                 )
, [Clip] = KEYMAP( _____   , KC_NO      , KC_NO   , KC_NO     , KC_NO   , KC_NO   , _____
                 , _____   , KC_NO      , KC_UP   , CL(KC_D)  , KC_NO   , KC_T    , _____
                 , _____   , M(C_bucket), JA_RBRC , M(C_add_l), CL(KC_Z), M(C_transpa)
                 , _____   , M(C_delete), JA_LBRC , M(C_del_l), CL(KC_Y), KC_E    , _____
                 , _____   , _____      , _____   , _____     , _____
                                                                        , CL(KC_H), CL(KC_S)
                                                                                  , KC_NO
                                                              , KC_MINS , JA_HAT  , S(CL(KC_H))
                 /*      ^^ LEFT ^^      /      vv RIGHT vv      */
                 , _____   , KC_NO      , KC_NO   , KC_NO     , KC_NO   , KC_NO   , _____
                 , _____   , KC_NO      , KC_NO   , KC_NO     , KC_NO   , KC_NO   , _____
                           , _____      , _____   , _____     , _____   , KC_NO   , KC_NO
                 , _____   , KC_NO      , KC_P    , KC_NO     , KC_NO   , KC_NO   , KC_NO
                                        , KC_ENT  , KC_NO     , KC_NO   , KC_NO   , MO(Base)
                 , KC_HOME , KC_END
                 , KC_PGUP
                 , KC_PGDN , KC_LEFT  , KC_RGHT
                 )
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(Medi)                // Medi - Momentary Layer 1 (Medi)
};

static uint16_t start;
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{ // MACRODOWN only works in this function
    switch(id) {
        case Dummy:
            if (record->event.pressed) /* 押したとき */ register_code(KC_RSFT);
            else                       /* 離したとき */ unregister_code(KC_RSFT);
            break;
        case Cut_paste:
            if (record->event.pressed) {
                start = timer_read();
            } else {
                if (300 <= timer_elapsed(start)) // 150ms以上なら 切り取り
                    return MACRO(D(LCTL), T(X), U(LCTL), END);
                else                             // 150ms未満なら コピー
                    return MACRO(D(LCTL), T(C), U(LCTL), END);
            }
            break;
        case C_bucket:
            if (record->event.pressed)
                return MACRO(D(G), W(800), END);
            else
                return MACRO(U(G), D(LCTL), T(D), U(LCTL), END);
            break;
        case C_delete:
            if (record->event.pressed)
                return MACRO(T(DEL), D(LCTL), T(D), U(LCTL), END);
            break;
        case C_add_l:
            if (record->event.pressed) return MACRO(D(M), D(LSFT), END);
            else                       return MACRO(W(200), U(LSFT), U(M), END);
            break;
        case C_del_l:
            if (record->event.pressed) return MACRO(D(M), D(LALT), END);
            else                       return MACRO(W(200), U(LALT), U(M), END);
            break;
        case C_transpa:
            return MACRO(T(C), END);
            break;
        default:
            break;
    }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    ergodox_board_led_off();
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
    ergodox_board_led_off();
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
    ergodox_board_led_off();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case Medi:
            ergodox_right_led_3_on();
            break;
        case Sai :
            ergodox_right_led_1_on();
            break;
        case Clip :
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case Base:
        default:
            break;
    }

};
