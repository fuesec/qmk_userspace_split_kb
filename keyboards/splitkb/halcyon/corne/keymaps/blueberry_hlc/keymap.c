#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#pragma region - layer names

enum layer_names {
    LAYER_BASE,
    LAYER_NAVIGATION,
    LAYER_SPECIAL_CHARACTERS,
    LAYER_NUMPAD,
	LAYER_FUNCTION_KEYS,
	LAYER_SYSTEM,
};

#pragma endregion

#pragma region - CKC custom key codes

enum custom_keycodes {
  CKC_MAC_DO_NOT_DISTURB = SAFE_RANGE,
  CKC_MOUSE_JIGGLE
};

#define CKC_MEH  (LCTL(LSFT(LALT(KC_NO))))
#define CKC_HYPER (LCTL(LSFT(LALT(LGUI(KC_NO)))))

#define CKC_MAC_BACK LGUI(KC_LBRC)
#define CKC_MAC_FORWARD LGUI(KC_RBRC)

#define CKC_MAC_LOCK LGUI(LCTL(KC_Q))
#define CKC_MAC_SLEEP LALT(LGUI(KC_MEDIA_EJECT))
#define CKC_MAC_SCREENSHOT LGUI(LSFT(KC_3))
#define CKC_MAC_SCREENSHOT_AREA LGUI(LSFT(KC_4))
#define CKC_MAC_SLEEP_DISPLAY LCTL(LSFT(KC_MEDIA_EJECT))

#pragma endregion

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

// QK_BOOT ??
// tap dance: TD(DANCE_0)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LAYER_BASE] = LAYOUT_corne_hlc(
        KC_ESCAPE,  	KC_Q,    KC_W,  KC_E,    KC_R,  KC_T,		KC_Y,    KC_U,  KC_I,    KC_O,   KC_P,    KC_BSPC,
        KC_TAB, 		KC_A,    KC_S,  KC_D,    KC_F,  KC_G,   	KC_H,    KC_J,  KC_K,    KC_L,   KC_SCLN, KC_ENTER,
        KC_CAPS_LOCK, 	KC_Z,    KC_X,  KC_C,    KC_V,  KC_B,   	KC_N,    KC_M,  KC_COMM, KC_DOT, KC_SLSH, QK_CAPS_WORD_TOGGLE,
                                 MO(LAYER_FUNCTION_KEYS), MO(LAYER_NUMPAD), 	 MO(LAYER_NAVIGATION), MO(LAYER_SPECIAL_CHARACTERS),  	KC_SPACE,      MO(LAYER_SYSTEM),
                 KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, KC_MUTE, 	XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX
    ),
[LAYER_NAVIGATION] = LAYOUT_corne_hlc(
        _______,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_HOME,   CKC_MAC_BACK,  CKC_MAC_FORWARD,  XXXXXXX,          XXXXXXX,          _______,
    _______, KC_LEFT_CTRL,    KC_LEFT_SHIFT,    KC_LEFT_ALT,    KC_LEFT_GUI,  CKC_HYPER_KEY,                                  KC_END,         KC_LEFT,        KC_RIGHT,       KC_DOWN,        KC_UP,          _______,
    _______,          XXXXXXX,          XXXXXXX,          XXXXXXX,          CKC_MEH_KEY,   XXXXXXX,                                          XXXXXXX,          LGUI(LSFT(KC_LBRC)),LGUI(LSFT(KC_RBRC)),KC_PGDN,        KC_PAGE_UP,     _______,
                                   _______, _______,    _______,  _______,  _______, _______,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
    ),
[LAYER_SPECIAL_CHARACTERS] = LAYOUT_corne_hlc(
    _______, KC_GRAVE,       KC_LEFT_BRACKET,        KC_LEFT_CURLY_BRACE,        KC_LEFT_PAREN,        KC_KP_ASTERISK,                                 KC_PERCENT,        KC_RIGHT_PAREN,        KC_RIGHT_CURLY_BRACE,        KC_RIGHT_BRACKET,        KC_TILDE,        _______,
    _______, KC_DOUBLE_QUOTE,        KC_EXCLAIM,        KC_KP_EQUAL,    KC_KP_MINUS,    KC_HASH,                                        CKC_HYPER, KC_RIGHT_GUI,  KC_RIGHT_ALT,  KC_RIGHT_SHIFT,  KC_RIGHT_CTRL,  _______,
    _______, KC_QUOTE,       KC_AT,          KC_KP_PLUS,     KC_UNDERSCORE,        KC_CIRCUMFLEX,                                        KC_DOLLAR,   CKC_MEH, KC_AMPERSAND,        KC_PIPE,        KC_BACKSLASH,        _______,
                                   _______, _______,    _______,  _______,  _______, _______,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
[LAYER_NUMPAD] = LAYOUT_corne_hlc(
    _______, XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,                                          KC_0,        KC_1,        KC_2,        KC_3,        KC_KP_DOT, KC_KP_ASTERISK,
    _______, KC_LEFT_CTRL,    KC_LEFT_SHIFT,    KC_LEFT_ALT,    KC_LEFT_GUI,  CKC_HYPER_KEY,                                           KC_KP_PLUS,     KC_4,        KC_5,        KC_6,        KC_KP_COMMA,    KC_KP_SLASH,
    _______,          XXXXXXX,          XXXXXXX,          XXXXXXX,          CKC_MEH_KEY,          XXXXXXX,                                          KC_KP_MINUS,    KC_7,        KC_8,        KC_9,        KC_KP_EQUAL,          XXXXXXX,
                                   _______, _______,    _______,  _______,  _______, _______,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
    ),
[LAYER_FUNCTION_KEYS] = LAYOUT_corne_hlc(
    _______, XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,                                          XXXXXXX,        KC_F1,        KC_F2,        KC_F3,        KC_F10, XXXXXXX,
    _______,  KC_LEFT_CTRL,    KC_LEFT_SHIFT,    KC_LEFT_ALT,    KC_LEFT_GUI,  CKC_HYPER_KEY,                                          XXXXXXX,     KC_F4,        KC_F5,        KC_F6,        KC_F11,    XXXXXXX,
    _______,          XXXXXXX,          XXXXXXX,          XXXXXXX,          CKC_MEH_KEY,          XXXXXXX,                                          XXXXXXX,    KC_F7,        KC_F8,        KC_F9,        KC_F12,          XXXXXXX,
                                   _______, _______,    _______,  _______,  _______, _______,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
    ),
[LAYER_SYSTEM] = LAYOUT_corne_hlc(
    CKC_MOUSE_JIGGLE,          KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_MEDIA_STOP,  KC_MEDIA_PLAY_PAUSE,XXXXXXX,                                XXXXXXX,          CKC_MAC_SCREENSHOT,          CKC_MAC_SCREENSHOT_AREA,          XXXXXXX,          XXXXXXX,          XXXXXXX,
    XXXXXXX,         KC_BRIGHTNESS_DOWN,KC_BRIGHTNESS_UP,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,                                          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,
    XXXXXXX,          CKC_MAC_SLEEP_DISPLAY, CKC_MAC_DO_NOT_DISTURB,       CKC_MAC_SLEEP,CKC_MAC_LOCK, XXXXXXX,                                 XXXXXXX,          QK_RGB_MATRIX_TOGGLE,          QK_RGB_MATRIX_MODE_NEXT,          XXXXXXX,          XXXXXXX,          XXXXXXX,
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
    if (record->event.pressed) {
    static deferred_token token = INVALID_DEFERRED_TOKEN;
    static report_mouse_t report = {0};
    if (token) {
      // If jiggler is currently running, stop when any key is pressed.
      cancel_deferred_exec(token);
      token = INVALID_DEFERRED_TOKEN;
      report = (report_mouse_t){};  // Clear the mouse.
      host_mouse_send(&report);
    } else if (keycode == CKC_MOUSE_JIGGLE) {
      uint32_t jiggler_callback(uint32_t trigger_time, void* cb_arg) {
        // Deltas to move in a circle of radius 20 pixels over 32 frames.
        static const int8_t deltas[32] = {
            0, -1, -2, -2, -3, -3, -4, -4, -4, -4, -3, -3, -2, -2, -1, 0,
            0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 3, 3, 2, 2, 1, 0};
        static uint8_t phase = 0;
        // Get x delta from table and y delta by rotating a quarter cycle.
        report.x = deltas[phase];
        report.y = deltas[(phase + 8) & 31];
        phase = (phase + 1) & 31;
        host_mouse_send(&report);
        return 16;  // Call the callback every 16 ms.
      }

      token = defer_exec(1, jiggler_callback, NULL);  // Schedule callback.
    }
  }
  switch (keycode) {
    case CKC_MAC_DO_NOT_DISTURB:
      HSS(0x9B);
      return false;
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

