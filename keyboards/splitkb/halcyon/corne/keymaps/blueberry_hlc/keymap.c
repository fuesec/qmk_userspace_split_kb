#include QMK_KEYBOARD_H
#include "custom_oneshot.h"
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

enum layer_names {
    LAYER_BASE,
    LAYER_NAVIGATION,
    LAYER_SPECIAL_CHARACTERS,
    LAYER_NUMPAD,
	LAYER_FUNCTION_KEYS,
	LAYER_SYSTEM,
};

enum custom_keycodes {
  CKC_MAC_DO_NOT_DISTURB = SAFE_RANGE,
  CKC_MOUSE_JIGGLE,
  CKC_SHIFT,
  CKC_CTRL,
  CKC_ALT,
  CKC_CMD,
  CKC_MEH,
  CKC_HYPER,
};

#define CKC_MAC_BACK LGUI(KC_LBRC)
#define CKC_MAC_FORWARD LGUI(KC_RBRC)
#define CKC_MAC_PREVIOUS_TAB LGUI(LSFT(KC_LEFT_BRACKET))
#define CKC_MAC_NEXT_TAB LGUI(LSFT(KC_RIGHT_BRACKET))

#define CKC_MAC_LOCK LGUI(LCTL(KC_Q))
#define CKC_MAC_SLEEP LALT(LGUI(KC_MEDIA_EJECT))
#define CKC_MAC_SCREENSHOT LGUI(LSFT(KC_3))
#define CKC_MAC_SCREENSHOT_AREA LGUI(LSFT(KC_4))
#define CKC_MAC_SLEEP_DISPLAY LCTL(LSFT(KC_MEDIA_EJECT))
#define CKC_MAC_INTELLIJ_TOOLWINDOW_TAB_LEFT LCTL(KC_LEFT)
#define CKC_MAC_INTELLIJ_TOOLWINDOW_TAB_RIGHT LCTL(KC_RIGHT)

#define CKC_MO_LAYER_NAVIGATION MO(LAYER_NAVIGATION)
#define CKC_MO_LAYER_SPECIAL_CHARACTERS MO(LAYER_SPECIAL_CHARACTERS)
#define CKC_MO_LAYER_NUMPAD MO(LAYER_NUMPAD)
#define CKC_MO_LAYER_FUNCTION_KEYS MO(LAYER_FUNCTION_KEYS)
#define CKC_MO_LAYER_SYSTEM MO(LAYER_SYSTEM)


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
        QK_CAPS_WORD_TOGGLE, 	KC_Z,    KC_X,  KC_C,    KC_V,  KC_B,   	KC_N,    KC_M,  KC_COMM, KC_DOT, KC_SLSH, QK_CAPS_WORD_TOGGLE,
                                 CKC_MO_LAYER_FUNCTION_KEYS, CKC_MO_LAYER_NUMPAD, 	 CKC_MO_LAYER_NAVIGATION, CKC_MO_LAYER_SPECIAL_CHARACTERS,  	KC_SPACE,      CKC_MO_LAYER_SYSTEM,
                 KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, 	XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX
    ),
[LAYER_NAVIGATION] = LAYOUT_corne_hlc(
        _______,  QK_MOUSE_WHEEL_LEFT,    QK_MOUSE_WHEEL_RIGHT,    QK_MOUSE_BUTTON_2,    QK_MOUSE_BUTTON_1,    QK_MOUSE_WHEEL_UP,    KC_HOME,   CKC_MAC_BACK,  CKC_MAC_FORWARD,  CKC_MAC_INTELLIJ_TOOLWINDOW_TAB_LEFT,          CKC_MAC_INTELLIJ_TOOLWINDOW_TAB_RIGHT,          SELECT_WORD_BACK,
    _______, CKC_CTRL,    CKC_SHIFT,    CKC_ALT,    CKC_CMD,  QK_MOUSE_WHEEL_DOWN,                                  KC_END,         KC_LEFT,        KC_RIGHT,       KC_DOWN,        KC_UP,          SELECT_WORD,
KC_LEFT_CTRL,          KC_LEFT_SHIFT,          KC_LEFT_ALT,          KC_LEFT_GUI,    CKC_MEH,   CKC_HYPER,                                          XXXXXXX,          CKC_MAC_PREVIOUS_TAB,CKC_MAC_NEXT_TAB,KC_PAGE_DOWN,        KC_PAGE_UP,     _______,
                                   _______, _______,    _______,  _______,  _______, _______,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
    ),
[LAYER_SPECIAL_CHARACTERS] = LAYOUT_corne_hlc(
    _______, KC_GRAVE,       KC_LEFT_BRACKET,        KC_LEFT_CURLY_BRACE,        KC_LEFT_PAREN,        KC_KP_ASTERISK,                                 KC_PERCENT,        KC_RIGHT_PAREN,        KC_RIGHT_CURLY_BRACE,        KC_RIGHT_BRACKET,        KC_TILDE,        XXXXXXX,
    _______, KC_DOUBLE_QUOTE,        KC_EXCLAIM,        KC_KP_EQUAL,    KC_KP_MINUS,    KC_HASH,                                        KC_DOLLAR, CKC_CMD,  CKC_ALT,  CKC_SHIFT,  CKC_CTRL,  XXXXXXX,
    XXXXXXX, KC_QUOTE,       KC_AT,          KC_KP_PLUS,     KC_UNDERSCORE,        KC_CIRCUMFLEX,                                        CKC_HYPER,   CKC_MEH, KC_AMPERSAND,        KC_PIPE,        KC_BACKSLASH,        XXXXXXX,
                                   _______, _______,    _______,  _______,  _______, _______,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
[LAYER_NUMPAD] = LAYOUT_corne_hlc(
    _______, XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,                                          KC_0,        KC_1,        KC_2,        KC_3,        KC_KP_DOT, KC_KP_ASTERISK,
    _______, CKC_CTRL,    CKC_SHIFT,    CKC_ALT,    CKC_CMD,  XXXXXXX,                                           KC_KP_PLUS,     KC_4,        KC_5,        KC_6,        KC_KP_COMMA,    KC_KP_SLASH,
    XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX, CKC_MEH,          CKC_HYPER,                                          KC_KP_MINUS,    KC_7,        KC_8,        KC_9,        KC_KP_EQUAL,          XXXXXXX,
                                   _______, _______,    _______,  _______,  _______, _______,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
    ),
[LAYER_FUNCTION_KEYS] = LAYOUT_corne_hlc(
    _______, XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,                                          XXXXXXX,        KC_F1,        KC_F2,        KC_F3,        KC_F10, XXXXXXX,
    _______,  CKC_CTRL,    CKC_SHIFT,    CKC_ALT,    CKC_CMD,  XXXXXXX,                                          XXXXXXX,     KC_F4,        KC_F5,        KC_F6,        KC_F11,    XXXXXXX,
    XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          CKC_MEH,          CKC_HYPER,                                          XXXXXXX,    KC_F7,        KC_F8,        KC_F9,        KC_F12,          XXXXXXX,
                                   _______, _______,    _______,  _______,  _______, _______,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
    ),
[LAYER_SYSTEM] = LAYOUT_corne_hlc(
    CKC_MOUSE_JIGGLE,          KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_MEDIA_STOP,  KC_MEDIA_PLAY_PAUSE,XXXXXXX,                                XXXXXXX,          CKC_MAC_SCREENSHOT,          CKC_MAC_SCREENSHOT_AREA,          XXXXXXX,          XXXXXXX,          XXXXXXX,
    XXXXXXX,         KC_BRIGHTNESS_DOWN,KC_BRIGHTNESS_UP,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,                                          QK_RGB_MATRIX_TOGGLE,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX,
    XXXXXXX,          CKC_MAC_SLEEP_DISPLAY, CKC_MAC_DO_NOT_DISTURB,       CKC_MAC_SLEEP,CKC_MAC_LOCK, XXXXXXX,                                 LUMINO,          QK_RGB_MATRIX_MODE_PREVIOUS,          QK_RGB_MATRIX_MODE_NEXT,          QK_RGB_MATRIX_HUE_DOWN,          QK_RGB_MATRIX_HUE_UP,          XXXXXXX,
                                   _______, _______,    _______,  _______,  XXXXXXX, XXXXXXX,
                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)};

// #if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
// const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
// [LAYER_BASE] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(QK_MOUSE_WHEEL_DOWN, QK_MOUSE_WHEEL_UP), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},
// [LAYER_NAVIGATION] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},
// [LAYER_SPECIAL_CHARACTERS] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},
// [LAYER_NUMPAD] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},
// [LAYER_FUNCTION_KEYS] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},
// [LAYER_SYSTEM] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)}};
// #endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case CKC_MO_LAYER_SYSTEM:
       return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case CKC_MO_LAYER_NAVIGATION:
    case CKC_MO_LAYER_SPECIAL_CHARACTERS:
    case CKC_MO_LAYER_NUMPAD:
    case CKC_MO_LAYER_FUNCTION_KEYS:
    case CKC_MO_LAYER_SYSTEM:
    case CKC_SHIFT:
    case CKC_CTRL:
    case CKC_ALT:
    case CKC_CMD:
    case CKC_MEH:
	case CKC_HYPER:
        return true;
    default:
        return false;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
	if (index != 1) { // only rotary encoder on position 1 is relevant
		return false;
	}
    uint8_t mods = get_mods() | get_oneshot_mods();
    switch (get_highest_layer(layer_state)) {
        case LAYER_BASE:
		case LAYER_NAVIGATION:
		case LAYER_SPECIAL_CHARACTERS:
		case LAYER_NUMPAD:
		case LAYER_FUNCTION_KEYS:
            if (mods & MOD_MASK_SHIFT) {
                if (clockwise) {
                    tap_code(QK_MOUSE_WHEEL_RIGHT);
                } else {
                    tap_code(QK_MOUSE_WHEEL_LEFT);
                }
            } else {
                if (clockwise) {
                    tap_code(QK_MOUSE_WHEEL_DOWN);
                } else {
                    tap_code(QK_MOUSE_WHEEL_UP);
                }
            }
            break;
        case LAYER_SYSTEM:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
    }
    return false;
}

oneshot_state os_shift_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	const char *key_name = get_keycode_string(keycode);
	dprintf("kc: %s\n", key_name);

	if (keycode == CKC_MEH || keycode == CKC_HYPER) {
    	update_oneshot(
        &os_shift_state, KC_LEFT_SHIFT, CKC_SHIFT, CKC_SHIFT, record
    );
	} else {
	    update_oneshot(
        &os_shift_state, KC_LEFT_SHIFT, CKC_SHIFT, keycode, record
    );
	}

	if (keycode == CKC_MEH || keycode == CKC_HYPER) {
    	update_oneshot(
        &os_ctrl_state, KC_LEFT_CTRL, CKC_CTRL, CKC_CTRL, record
    );
	} else {
	    update_oneshot(
        &os_ctrl_state, KC_LEFT_CTRL, CKC_CTRL, keycode, record
    );
	}

	if (keycode == CKC_MEH || keycode == CKC_HYPER) {
    	update_oneshot(
        &os_alt_state, KC_LEFT_ALT, CKC_ALT, CKC_ALT, record
    );
	} else {
	    update_oneshot(
        &os_alt_state, KC_LEFT_ALT, CKC_ALT, keycode, record
    );
	}

	if (keycode == CKC_HYPER) {
    	update_oneshot(
        &os_cmd_state, KC_LEFT_GUI, CKC_CMD, CKC_CMD, record
    );
	} else {
	    update_oneshot(
        &os_cmd_state, KC_LEFT_GUI, CKC_CMD, keycode, record
    );
	}

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
	case CKC_MAC_LOCK:
	  lumino_sleep_soon();
	  return true;
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

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}
