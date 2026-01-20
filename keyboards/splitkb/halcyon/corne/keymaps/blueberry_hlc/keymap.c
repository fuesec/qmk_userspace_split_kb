#include QMK_KEYBOARD_H
#include "keymap_mac_system.h"
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#define ML_SAFE_RANGE SAFE_RANGE

enum custom_keycodes {
  MAC_DO_NOT_DISTURB = ML_SAFE_RANGE,
  MAC_SLEEP,
  MAC_LOCK
};

#define MAC_SCREENSHOT LGUI(LSFT(KC_3))
#define MAC_SCREENSHOT_AREA LGUI(LSFT(KC_4))
#define MAC_SLEEP_DISPLAY LCTL(LSFT(KC_MEDIA_EJECT))

enum tap_dance_codes {
  DANCE_0, // switch to num pad layer
  DANCE_1, // persist color to EEPROM
};

typedef union {
  uint32_t raw;
  struct {
    uint8_t   color_index :8;
  };
} user_config_t;

user_config_t user_config;

// _______ = KC_TRANSPARENT
// XXXXXXX = KC_NO
// QK_BOOT ??
// tap dance: TD(DANCE_0)
// old bottom layer:
// RM_TOGG, RM_HUEU, RM_SATU, RM_VALU
// RM_NEXT, RM_HUED, RM_SATD, RM_VALD
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_corne_hlc(
        KC_ESCAPE,  	KC_Q,    KC_W,  KC_E,    KC_R,  KC_T,		KC_Y,    KC_U,  KC_I,    KC_O,   KC_P,    KC_BSPC,
        KC_TAB, 		KC_A,    KC_S,  KC_D,    KC_F,  KC_G,   	KC_H,    KC_J,  KC_K,    KC_L,   KC_SCLN, KC_ENTER,
        XXXXXXX, 	KC_Z,    KC_X,  KC_C,    KC_V,  KC_B,   	KC_N,    KC_M,  KC_COMM, KC_DOT, KC_SLSH, CW_TOGG,
                                 MO(4), MO(3), 	 MO(1), MO(2),  	KC_SPACE,      MO(5),
                 KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, KC_MUTE, 	XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX
    ),
[1] = LAYOUT_corne_hlc(
        _______,  KC_LEFT_CTRL,    KC_LEFT_SHIFT,    KC_LEFT_ALT,    KC_LEFT_GUI,    XXXXXXX,    KC_HOME,   LGUI(KC_LBRC),  LGUI(KC_RBRC),  XXXXXXX,          XXXXXXX,          _______,
    _______, OSM(MOD_LCTL),  OSM(MOD_LSFT),  OSM(MOD_LALT),  OSM(MOD_LGUI),  OSM(MOD_HYPR),                                  KC_END,         KC_LEFT,        KC_RIGHT,       KC_DOWN,        KC_UP,          _______,
    _______,          XXXXXXX,          XXXXXXX,          XXXXXXX,          OSM(MOD_MEH),   XXXXXXX,                                          XXXXXXX,          LGUI(LSFT(KC_LBRC)),LGUI(LSFT(KC_RBRC)),KC_PGDN,        KC_PAGE_UP,     _______,
                                   _______, _______,    _______,  _______,  _______, _______,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
    ),
[2] = LAYOUT_corne_hlc(
    _______, KC_GRAVE,       KC_LBRC,        KC_LCBR,        KC_LPRN,        KC_KP_ASTERISK,                                 KC_PERC,        KC_RPRN,        KC_RCBR,        KC_RBRC,        KC_TILD,        _______,
    _______, KC_DQUO,        KC_EXLM,        KC_KP_EQUAL,    KC_KP_MINUS,    KC_HASH,                                        OSM(MOD_HYPR),  OSM(MOD_RGUI),  OSM(MOD_RALT),  OSM(MOD_RSFT),  OSM(MOD_RCTL),  _______,
    _______, KC_QUOTE,       KC_AT,          KC_KP_PLUS,     KC_UNDS,        KC_CIRC,                                        XXXXXXX,   OSM(MOD_MEH), KC_AMPR,        KC_PIPE,        KC_BSLS,        _______,
                                   _______, _______,    _______,  _______,  _______, _______,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
[3] = LAYOUT_corne_hlc(
    _______, XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,                                          KC_KP_0,        KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_KP_DOT, KC_KP_ASTERISK,
    _______, OSM(MOD_LCTL),  OSM(MOD_LSFT),  OSM(MOD_LALT),  OSM(MOD_LGUI),  OSM(MOD_HYPR),                                           KC_KP_PLUS,     KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_KP_COMMA,    KC_KP_SLASH,
    _______,          XXXXXXX,          XXXXXXX,          XXXXXXX,          OSM(MOD_MEH),          XXXXXXX,                                          KC_KP_MINUS,    KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_EQUAL,          XXXXXXX,
                                   _______, _______,    _______,  _______,  _______, _______,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
    ),
[4] = LAYOUT_corne_hlc(
    _______, XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,                                          XXXXXXX,        KC_F1,        KC_F2,        KC_F3,        KC_F10, XXXXXXX,
    _______, OSM(MOD_LCTL),  OSM(MOD_LSFT),  OSM(MOD_LALT),  OSM(MOD_LGUI),  OSM(MOD_HYPR),                                          XXXXXXX,     KC_F4,        KC_F5,        KC_F6,        KC_F11,    XXXXXXX,
    _______,          XXXXXXX,          XXXXXXX,          XXXXXXX,          OSM(MOD_MEH),          XXXXXXX,                                          XXXXXXX,    KC_F7,        KC_F8,        KC_F9,        KC_F12,          XXXXXXX,
                                   _______, _______,    _______,  _______,  _______, _______,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
    ),
[5] = LAYOUT_corne_hlc(
    XXXXXXX,          KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_MEDIA_STOP,  KC_MEDIA_PLAY_PAUSE,XXXXXXX,                                XXXXXXX,          MAC_SCREENSHOT,          MAC_SCREENSHOT_AREA,          XXXXXXX,          XXXXXXX,          XXXXXXX,
    XXXXXXX,         KC_BRIGHTNESS_DOWN,KC_BRIGHTNESS_UP,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,                                          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,
    XXXXXXX,          MAC_SLEEP_DISPLAY, MAC_DO_NOT_DISTURB,       MAC_SLEEP,MAC_LOCK, XXXXXXX,                                 XXXXXXX,          XXXXXXX,          RM_TOGG,          RM_NEXT,          XXXXXXX,          XXXXXXX,
                                   _______, _______,    _______,  _______,  XXXXXXX, XXXXXXX,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
[0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
[1] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
[2] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
[3] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
[4] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
[5] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)}};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MAC_DO_NOT_DISTURB:
      HSS(0x9B);
      return false;
	case MAC_SLEEP:
	  HSS(0x82);
      return false;
    case MAC_LOCK:
      HCS(0x19E);
  }
  return true; // Process all other keycodes normally
}

#ifdef TAP_DANCE_ENABLE
typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[2];

uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void dance_0_finished(tap_dance_state_t *state, void *user_data);
void dance_0_reset(tap_dance_state_t *state, void *user_data);

void dance_0_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case DOUBLE_TAP: layer_move(5); break;
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
    }
    dance_state[0].step = 0;
}

void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

void dance_1_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case DOUBLE_TAP: {
			eeconfig_update_user(user_config.raw);
            break;
        }
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
    }
    dance_state[1].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_1_finished, dance_1_reset),
};
#endif

#ifdef KEY_OVERRIDE_ENABLE
const key_override_t delete_key_override =
	ko_make_with_layers_negmods_and_options(
   		MOD_MASK_SHIFT,      // Trigger modifier
    	KC_BSPC,             // Trigger key
    	KC_DEL,              // Replacement key
    	~0,                  // Activate on all layers
    	MOD_MASK_GUI,        // Do not activate when
    	ko_option_no_reregister_trigger); // Specifies that the play key is not registered again after lifting "Trigger modifier"

const key_override_t delete_word_key_override =
	ko_make_with_layers_negmods_and_options(
   		MOD_MASK_SHIFT | MOD_MASK_ALT,      // Trigger modifier
    	KC_BSPC,             // Trigger key
    	MO(KC_DEL),              // Replacement key
    	~0,                  // Activate on all layers
    	MOD_MASK_GUI,        // Do not activate when
    	ko_option_no_reregister_trigger); // Specifies that the play key is not registered again after lifting "Trigger modifier"

const key_override_t *key_overrides[] = {
  &delete_key_override,
  &delete_word_key_override,
  NULL
};
#endif

