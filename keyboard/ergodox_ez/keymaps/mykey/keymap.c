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
#define TC(x)  MT(CL((x)), (x))


#define BASE 0  // layer: default
#define MEDI 1  // layer: medi
#define DRAW 2  // layer: draw

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
/* Keymap 0: Base layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ZenHan | 1    | 2    | 3    | 4    | 5    | Esc  |           | `~   | 6    | 7    | 8    | 9    | 0    | -=     |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    | Q    | W    | E    | R    | T    |Delete|           | Up   | Y    | U    | I    | O    | P    | \|     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CTRL   | A    | S    | D    | F    | G    |------|           |------| H    | J    | K    | L    | ;+   | :* /Ctl|
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift | Z    | X    | C    | V    | B    |Backsp|           | Down | N    | M    | ,<   | .>   | /?   | \_ /Sft|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Alt  | undo | copy | paste| cut  |                                       | Enter| [{   | ]}   | @`   | ^~   |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Enter|      |       | Home | End  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Lyr2 |       | PgUp |        |      |
 *                                 | Space|      |------|       |------|        |      |
 *                                 | /Lyr1| Space|      |       | PgDn | Left   | Right|
 *                                 `--------------------'       `----------------------'
 */
{ [BASE] = KEYMAP( KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_ESC
                 , KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_DELT
                 , KC_LCTL , KC_A    , KC_S    , KC_D    , KC_F    , KC_G
                 , KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , KC_BSPC
                 , KC_LALT , CL(KC_Z), CL(KC_X), CL(KC_V), CL(KC_C)
                                                                   , KC_ENT  , RESET
                                                                             , KC_HOME
                                            , MT(MO(MEDI), KC_SPC) , KC_SPC  , KC_NO
                 /*      ^^ LEFT ^^      /      vv RIGHT vv      */
                 , KC_NO   , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_MINS
                 , KC_UP   , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , JA_ENVL
                           , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , CTL_T(JA_CLON)
                 , KC_DOWN , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , SFT_T(JA_ENUN)
                                     , KC_ENT  , JA_LBRC , JA_RBRC , JA_AT   , JA_HAT
                 , KC_HOME , KC_END
                 , KC_PGUP
                 , KC_PGDN , KC_LEFT  , KC_RGHT
                 )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Keymap 1: medi layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | zenhan | F1   | F6   | F8   |      |      |      |           | F11  | F12  | F13  | F14  | F15  | F16  | Lyr0   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |      |      | Up   |      |      |      |           | WH-U |      |      | M-up |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CTRL   |      | Left | Down | Right|      |------|           |------|      | M-le | M-do | M-ri |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift | F2   | F3   | F4  |F5/CrlF5| F7  | F10  |           | WH-D |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Alt  | undo | copy | paste| cut  |                                       | Enter|LClick|LClick|RClick|RClick|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       | Home | End  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       | PgUp |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       | PgDn | Left   | Right
 *                                 `--------------------'       `----------------------'
 */
, [MEDI] = KEYMAP( KC_GRV  , KC_F1   , KC_F6   , KC_F8   , KC_NO    , KC_NO   , KC_NO
                  , KC_TAB  , KC_NO   , KC_NO   , KC_WH_U , KC_NO    , KC_NO   , KC_NO
                  , KC_LCTL , KC_NO   , KC_LEFT , KC_WH_D , KC_RGHT  , KC_NO
                  , KC_LSFT , KC_F2   , KC_F3   , KC_F4   , TC(KC_F5), KC_F7   , KC_F10
                  , KC_LALT , KC_NO   , KC_NO   , KC_NO   , KC_NO
                                                                     , KC_NO   , KC_NO
                                                                               , KC_NO
                                                          , KC_NO    , KC_NO   , KC_NO
                  /*      ^^ LEFT ^^      /      vv RIGHT vv      */
                  , KC_F10  , KC_F11  , KC_F12  , KC_F13  , KC_F14   , KC_NO   , MO(BASE)
                  , KC_UP   , KC_F15  , KC_F16  , KC_MS_U , KC_NO    , KC_NO   , KC_NO
                            , KC_NO   , KC_MS_L , KC_MS_D , KC_MS_R  , KC_NO   , KC_NO(JA_CLON)
                  , KC_DOWN , KC_NO   , KC_NO   , KC_NO   , KC_NO    , KC_NO   , KC_RSFT
                                      , KC_ENT  , KC_BTN1 , KC_BTN1  , KC_BTN2 , KC_BTN2
                  , KC_HOME , KC_END
                  , KC_PGUP
                  , KC_PGDN , KC_LEFT  , KC_RGHT
                  )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Keymap 2: Draw Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | zenhan |  F1  |  F2  |  F3  |  F4  |  F5  | Esc  |           | F7   |  F8  |  F9  | F10  |  F11 |  F12 | Lyr0   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |      |      |      | seve |      |expand|           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CTRL   |      |      |      | sel +|      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |      |      |      | sel -|      |reduce|           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Alt  | undo | copy | paste| cut  |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      | Mute |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |Space |Enter |------|       |------| Vol- | Vol+ |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
, [DRAW] = KEYMAP( KC_GRV  , KC_NO   , KC_NO      , KC_NO   , KC_NO   , KC_NO   , KC_ESC
                 , KC_TAB  , KC_NO   , KC_NO      , KC_UP   , CL(KC_L), KC_NO   , KC_WH_D
                 , KC_LCTL , CL(KC_A), AL(KC_DELT), JA_LBRC , SF(KC_L), KC_NO
                 , KC_LSFT , CL(KC_S), KC_D       , JA_RBRC , AL(KC_L), KC_MINS   , KC_WH_U
                 , KC_LALT , CL(KC_Z), CL(KC_X)   , CL(KC_V), CL(KC_C)
                                                                   , KC_H    , KC_HOME
                                                                             , KC_NO
                                                         , KC_DELT , KC_END  , KC_INS
                 /*      ^^ LEFT ^^      /      vv RIGHT vv      */
                 , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , MO(BASE)
                 , KC_UP   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO
                           , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO
                 , KC_DOWN , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO
                                     , KC_NO   , KC_NO   ,  KC_NO  , KC_NO   , KC_NO
                 , KC_HOME , KC_END
                 , KC_PGUP
                 , KC_PGDN , KC_LEFT  , KC_RGHT
                 )
,
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(MEDI)                // MEDI1 - Momentary Layer 1 (medi)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    switch(id) {
        case 0:
            if (record->event.pressed) {
                register_code(KC_RSFT);
            } else {
                unregister_code(KC_RSFT);
            }
            break;
    }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    ergodox_board_led_off();
    ergodox_right_led_1_on(); ergodox_right_led_2_on(); ergodox_right_led_3_on();
    ergodox_board_led_off();
    ergodox_right_led_1_on(); ergodox_right_led_2_on(); ergodox_right_led_3_on();
    ergodox_board_led_off();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off(); ergodox_right_led_2_off(); ergodox_right_led_3_off();

    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case BASE:
            ergodox_right_led_1_on();
            break;
        case MEDI:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case DRAW:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
