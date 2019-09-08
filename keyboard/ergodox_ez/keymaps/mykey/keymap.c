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
#define xxxxx   KC_NO

#define TGSPACE LT(Media, KC_SPC)

/*
#define Base 0  // layer: default
#define Media 1  // layer: Media
#define Sai  2  // layer: Sai
 */
enum Layer_names{ Base
                , Media
                , Sai
                , Clip
                };
enum Macro_stat{ Dummy
               // common
               , K_cut_copy
               , K_bucket
               , K_bucke2
               , T_arr
               , T_ar2
               // to draw
               , C_delete
               , C_bucket
               , C_outLn
               , C_autol
               , C_add_l
               , C_del_l
               , C_voPen
               , C_rotR
               , C_rotL
               };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
/* Keymap 0: Base layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    | 1    | 2    | 3    | 4    | 5    | Z/H  |           | Undo | 6    | 7    | 8    | 9    | 0    | \|     |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    | Q    | W    | E    | R    | T    | paste|           | @`   | Y    | U    | I    | O    | P    | -=     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CTRL   | A    | S    | D    | F    | G    |------|           |------| H    | J    | K    | L    | ;+   | :* /Ctl|
 * |--------+------+------+------+------+------| copy |           |      |------+------+------+------+------+--------|
 * | LShift | Z    | X    | C    | V    | B    | /cut |           | ^~   | N    | M    | ,<   | .>   | /?   | \_ /Sft|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Enter| [{   | ]}   | Alt  | BS   |                                       | Enter|TSpace|      |      | Dollr |
 *   `----------------------------------'                                       `----------------------------------'
 *                                      ,-------------.           ,-------------.
 *                                      |      | save |           | Home | End  |
 *                               ,------|------|------|           |------+--------+------.
 *                               |      |      |      |           | Up   |        |      |
 *                               | Space| Tab  |------|           |------| Left   | Right|
 *                               | /Lyr1|      | Del  |           | Dn   |        |      |
 *                               `--------------------'           `----------------------'
 */
{ [Base] = KEYMAP( KC_ESC  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_GRV //MT(KC_LANG1, KC_LANG2)
                 , KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , M(K_bucke2)
                 , KC_LCTL , KC_A    , KC_S    , KC_D    , KC_F    , KC_G
                 , KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , M(K_bucket)
                 , KC_ENT  , JA_LBRC , JA_RBRC , KC_LALT , KC_BSPC
                                                                   , xxxxx   , CL(KC_S)
                                                                             , CL(KC_V)
                                               , TGSPACE , KC_DELT , M(K_cut_copy)

                 /*      ^^ LEFT ^^      /      vv RIGHT vv      */
                 , CL(KC_Z), KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , JA_ENVL
                 , JA_AT   , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_MINS
                           , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , CTL_T(JA_CLON)
                 , JA_HAT  , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , SFT_T(JA_ENUN)
                                     , KC_ENT  , TGSPACE , xxxxx   , xxxxx   , KC_DLR
                 , KC_HOME , KC_END
                 , KC_UP
                 , KC_DOWN , KC_LEFT , KC_RGHT
                 )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Keymap 1: Media layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        | F1   | F3   | F6   | F8   | F9   |      |           | Lyr0 | F11  | F12  | F13  | F14  | F15  | Lyr2   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | M-Up |      |      |      |           | WH-U |      |      |      |      |      | Lyr3   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |LClick| M-Lf | M-Dn | M-Ri |RClick|------|           |------| Left | Down | Up   | Right|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | F2   | F4  |F5/CrlF5| F7  | F10  |      |           | WH-D |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | reset|      |      |      |      |                                       | Enter|      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                      ,-------------.           ,-------------.
 *                                      |      |      |           | Home | End  |
 *                               ,------|------|------|           |------+--------+------.
 *                               |      |      |      |           | PgUp |        |      |
 *                               | Lyr0 |      |------|           |------|        |      |
 *                               |      |      |      |           | PgDn | Left   | Right
 *                               `--------------------'           `----------------------'
 */
, [Media] = KEYMAP( _____   , KC_F1   , KC_F3   , KC_F6    , KC_F8    , KC_F9   , RESET
                  , _____   , xxxxx   , xxxxx   , KC_BTN1  , KC_MS_U  , KC_BTN2 , KC_WH_U
                  , _____   , xxxxx   , xxxxx   , KC_MS_L  , KC_MS_D  , KC_MS_R 
                  , _____   , KC_F2   , KC_F4   , TC(KC_F5), KC_F7    , KC_F10  , KC_WH_D
                  , KC_ENT  , _____   , _____   , _____    , _____
                                                                      , xxxxx   , xxxxx
                                                                                , xxxxx
                                                           , _____    , xxxxx   , _____
                  /*      ^^ LEFT ^^      /      vv RIGHT vv      */
                  , TG(Base), KC_F11  , KC_F12  , KC_F13   , KC_F14   , KC_F15  , TG(Sai)
                  , M(T_ar2), xxxxx   , xxxxx   , xxxxx    , xxxxx    , xxxxx   , TG(Clip)
                            , KC_LEFT , KC_DOWN , KC_UP    , KC_RGHT  , xxxxx   , xxxxx
                  , M(T_arr), KC_GRV  , xxxxx   , xxxxx    , xxxxx    , xxxxx   , xxxxx
                                      , _____   , _____    , _____    , _____   , _____
                  , KC_HOME , KC_END
                  , KC_PGUP
                  , KC_PGDN , _____   , _____
                  )

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Keymap 2~: Draw
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | same   |  F1  |  F2  |  F3  |  F4  |  F5  | Esc  |           | F7   |  F8  |  F9  | F10  |  F11 |  F12 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | same   |      |      |autoRp|      |areaPn| paste|           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | same   |bucket| size+| rope+| undo |voidPn|----- |           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------| copy |           |      |------+------+------+------+------+--------|
 * | same   |delete| size-| rope-| redo |erease| /cut |           |      |      | pen  |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | same | same | same |unrope| same |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      | save |       |      | Mute |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |L Rote|R Rote|------|       |------| Vol- | Vol+ |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
, [Sai] =  KEYMAP( _____   , xxxxx      , xxxxx   , xxxxx      , xxxxx    , xxxxx     , _____
                 , _____   , M(C_outLn) , xxxxx   , M(C_autol) , xxxxx    , KC_T      , _____
                 , _____   , M(C_delete), JA_RBRC , M(C_add_l) , CL(KC_Z) , M(C_voPen)
                 , _____   , M(C_bucket), JA_LBRC , M(C_del_l) , CL(KC_Y) , KC_E      , _____
                 , _____   , _____      , _____   , CL(KC_D)   , _____
                                                                          , KC_H      , CL(KC_S)
                                                                                      , xxxxx
                                                               , M(C_rotL), M(C_rotR) , KC_HOME
                 /*      ^^ LEFT ^^      /      vv RIGHT vv       */
                 , _____   , xxxxx      , xxxxx   , xxxxx      , xxxxx    , xxxxx     , _____
                 , _____   , xxxxx      , xxxxx   , xxxxx      , xxxxx    , xxxxx     , _____
                           , _____      , _____   , _____      , _____    , xxxxx     , xxxxx
                 , _____   , xxxxx      , xxxxx   , xxxxx      , xxxxx    , xxxxx     , xxxxx
                                        , KC_ENT  , CL(KC_D)   , xxxxx    , xxxxx     , MO(Base)
                 , KC_HOME , KC_END
                 , KC_PGUP
                 , KC_PGDN , KC_LEFT  , KC_RGHT
                 )
, [Clip] = KEYMAP( _____   , xxxxx      , xxxxx   , xxxxx      , xxxxx    , xxxxx     , _____
                 , _____   , xxxxx      , xxxxx   , M(C_autol) , xxxxx    , KC_T      , _____
                 , _____   , M(C_delete), JA_RBRC , M(C_add_l) , CL(KC_Z) , M(C_voPen)
                 , _____   , M(C_bucket), JA_LBRC , M(C_del_l) , CL(KC_Y) , KC_E      , _____
                 , _____   , _____      , _____   , CL(KC_D)   , _____
                                                                          , CL(KC_H)  , CL(KC_S)
                                                                                      , xxxxx
                                                               , M(C_rotL), M(C_rotR) , S(CL(KC_H))
                 /*      ^^ LEFT ^^      /      vv RIGHT vv       */
                 , _____   , xxxxx      , xxxxx   , xxxxx      , xxxxx    , xxxxx     , _____
                 , _____   , xxxxx      , xxxxx   , xxxxx      , xxxxx    , xxxxx     , _____
                           , _____      , _____   , _____      , _____    , xxxxx     , xxxxx
                 , _____   , xxxxx      , KC_P    , xxxxx      , xxxxx    , xxxxx     , xxxxx
                                        , KC_ENT  , xxxxx      , xxxxx    , xxxxx     , MO(Base)
                 , KC_HOME , KC_END
                 , KC_PGUP
                 , KC_PGDN , KC_LEFT  , KC_RGHT
                 )
};


const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(Media)                // Media - Momentary Layer 1 (Media)
};

static uint16_t start;
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{ // MACRODOWN only works in this function
    uint8_t curr_lay = biton32(layer_state);
    switch(id) {
        case Dummy:
            if (record->event.pressed) /* 押したとき */ register_code(KC_RSFT);
            else                       /* 離したとき */ unregister_code(KC_RSFT);
            break;
        case K_cut_copy:
            if (record->event.pressed) {
                start = timer_read();
            } else {
                if (300 <= timer_elapsed(start)) // 150ms以上なら 切り取り
                    return MACRO(D(LCTL), T(X), U(LCTL), END);
                else                             // 150ms未満なら コピー
                    return MACRO(D(LCTL), T(C), U(LCTL), END);
            }
            break;
        case K_bucket:
            if (record->event.pressed) {
                start = timer_read();
            } else {
                if (300 <= timer_elapsed(start)) // 150ms以上なら [
                    return MACRO(T(BSLS), END);
                else                             // 150ms未満なら ]
                    return MACRO(T(RBRC), END);
            }
            break;
        case K_bucke2:
            if (record->event.pressed) {
                start = timer_read();
            } else {
                if (300 <= timer_elapsed(start)) // 150ms以上なら (
                    return MACRO(D(LSFT), T(9) ,U(LSFT), END);
                else                             // 150ms未満なら )
                    return MACRO(D(LSFT), T(8) ,U(LSFT), END);
            }
            break;
        case T_arr:
            if (record->event.pressed) {
                start = timer_read();
            } else {
                if (300 <= timer_elapsed(start)) // 150ms以上なら <-
                    return MACRO(D(LSFT), T(COMM), U(LSFT), T(MINS), END);
                else                             // 150ms未満なら ->
                    return MACRO(T(MINS), D(LSFT), T(DOT), U(LSFT), END);
            }
            break;
        case T_ar2:
            if (record->event.pressed) {
                start = timer_read();
            } else {
                if (300 <= timer_elapsed(start)) // 150ms以上なら =<<
                    return MACRO(D(LSFT), T(MINS), T(COMM), T(COMM), U(LSFT), END);
                else                             // 150ms未満なら >>=
                    return MACRO(D(LSFT), T(DOT), T(DOT), T(MINS), U(LSFT), END);
            }
            break;
        // to draw
        case C_delete:
            if (curr_lay == Sai){
                if (record->event.pressed)
                    return MACRO(T(DEL), END);
                else
                    return MACRO(D(LCTL), T(D), U(LCTL),END);
            } else if(curr_lay == Clip) {
                if (record->event.pressed)
                    return MACRO(T(DEL), D(LCTL), T(D), U(LCTL), END);
            }
            break;
        case C_bucket:
            if (curr_lay == Sai){
                return MACRO(D(LALT), T(DEL), U(LALT), END);
            } else if(curr_lay == Clip) {
                if (record->event.pressed)
                    return MACRO(D(G), W(800), END);
                else
                    return MACRO(U(G), D(LCTL), T(D), U(LCTL), END);
            }
            break;
        case C_outLn:
            if (curr_lay == Sai){
                if (!record->event.pressed)
                    return MACRO(D(LALT), T(L), T(U), U(LALT), T(ENT));
            } else if(curr_lay == Clip) {
                // TODO
            }
            break;
        case C_autol:
            if (curr_lay == Sai){
                if (record->event.pressed) return MACRO(D(W)  , D(LSFT), END);
                else                       return MACRO(W(200), U(LSFT), U(W), END);
            } else if(curr_lay == Clip) {
                // TODO
            }
            break;
        case C_add_l:
            if (curr_lay == Sai){
                if (record->event.pressed) return MACRO(D(L)  , D(LSFT), END);
                else                       return MACRO(W(200), U(LSFT), U(L), END);
            } else if (curr_lay == Clip){
                if (record->event.pressed) return MACRO(D(M)  , D(LSFT), END);
                else                       return MACRO(W(200), U(LSFT), U(M), END);
            }
            break;
        case C_del_l:
            if (curr_lay == Sai){
                if (record->event.pressed) return MACRO(D(L)  , D(LALT), END);
                else                       return MACRO(W(200), U(LALT), U(L), END);
            } else if (curr_lay == Clip){
                if (record->event.pressed) return MACRO(D(M)  , D(LALT), END);
                else                       return MACRO(W(200), U(LALT), U(M), END);
            }
            break;
        case C_voPen:
            if (curr_lay == Sai)
                return MACRO(T(MINS), END);
            else if (curr_lay == Clip)
                return MACRO(T(C), END);
            break;
        case C_rotL:
            if (curr_lay == Sai)
                if (!record->event.pressed)
                    return MACRO(D(LSFT), T(PGUP), U(LSFT), END);
            else if (curr_lay == Clip)
                return MACRO(T(MINS), END);
            break;
        case C_rotR:
            if (curr_lay == Sai)
                if (!record->event.pressed)
                    return MACRO(D(LSFT), T(PGDN), U(LSFT), END);
            else if (curr_lay == Clip)
                return MACRO(T(CIRC), END);
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
        case Media:
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
