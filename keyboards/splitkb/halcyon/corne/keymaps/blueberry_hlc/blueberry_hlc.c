#include QMK_KEYBOARD_H
#include "version.h"
#include "i18n.h"
#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  MAC_DND,
  CMD_TAB,
  CLEAR_OSM_MOD_LEFT,
  CLEAR_OSM_MOD_RIGHT,
  SWAP_BASE_LAYER_COLOR,
};

enum color_index {
  PINK = 0,
  BLUE,
  YELLOW,
  COLOR_COUNT
};

const uint8_t PROGMEM color_array[COLOR_COUNT][3] = {
  [PINK] = {224, 255, 255}, // #ff00bf
  [BLUE] = {167, 255, 255}, // #0112ff
  [YELLOW] = {37,255,255}, // #ffde00
};

static uint8_t current_color_index = 0;

#define TARGET_LAYER 0

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_voyager(
    KC_NO,          KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_NO,          
    KC_ESCAPE,      KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSPC,        
    KC_TAB,         KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_ENTER,       
    TD(DANCE_0),    KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       CW_TOGG,
                                                    MO(1),          MO(2),                                          MO(3),          KC_SPACE
  ),
  [1] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_MS_ACCEL0,   KC_MS_ACCEL1,   KC_MS_ACCEL2,   KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_MS_WH_LEFT,  KC_MS_WH_RIGHT, KC_MS_BTN2,     KC_MS_BTN1,     KC_MS_WH_UP,                                    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    CMD_TAB,     KC_MS_UP,       KC_MS_DOWN,     KC_MS_LEFT,     KC_MS_RIGHT,    KC_MS_WH_DOWN,                                  KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_NO,          KC_MAC_UNDO,    KC_MAC_CUT,     KC_MAC_COPY,    KC_MAC_PASTE,   KC_MS_BTN3,                                     KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
                                                    KC_TRANSPARENT, KC_NO,                                          KC_NO,          KC_TRANSPARENT
  ),
  [2] = LAYOUT_voyager(
    CLEAR_OSM_MOD_LEFT, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LEFT_CTRL,   KC_LEFT_SHIFT,  KC_LEFT_ALT,    KC_LEFT_GUI,    KC_NO,                                          KC_HOME,        LGUI(KC_LBRC),  LGUI(KC_RBRC),  KC_NO,          KC_NO,          KC_TRANSPARENT, 
    KC_TRANSPARENT, OSM(MOD_LCTL),  OSM(MOD_LSFT),  OSM(MOD_LALT),  OSM(MOD_LGUI),  OSM(MOD_HYPR),                                  KC_END,         KC_LEFT,        KC_RIGHT,       KC_DOWN,        KC_UP,          KC_TRANSPARENT, 
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          OSM(MOD_MEH),   KC_NO,                                          KC_NO,          LGUI(LSFT(KC_LBRC)),LGUI(LSFT(KC_RBRC)),KC_PGDN,        KC_PAGE_UP,     KC_NO,          
                                                    KC_NO,          KC_TRANSPARENT,                                 MO(4),          KC_TRANSPARENT
  ),
  [3] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         CLEAR_OSM_MOD_RIGHT,
    KC_TRANSPARENT, KC_GRAVE,       KC_LBRC,        KC_LCBR,        KC_LPRN,        KC_KP_ASTERISK,                                 KC_PERC,        KC_RPRN,        KC_RCBR,        KC_RBRC,        KC_TILD,        KC_F11,
    KC_TRANSPARENT, KC_DQUO,        KC_EXLM,        KC_KP_EQUAL,    KC_KP_MINUS,    KC_HASH,                                        OSM(MOD_HYPR),  OSM(MOD_RGUI),  OSM(MOD_RALT),  OSM(MOD_RSFT),  OSM(MOD_RCTL),  KC_F12,
    KC_TRANSPARENT, KC_QUOTE,       KC_AT,          KC_KP_PLUS,     KC_UNDS,        KC_CIRC,                                        KC_NO,          OSM(MOD_MEH),   KC_AMPR,        KC_PIPE,        KC_BSLS,        KC_F13,
                                                    KC_NO,          MO(4),                                          KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [4] = LAYOUT_voyager(
    KC_NO,          LCTL(LSFT(KC_MEDIA_EJECT)),MAC_DND,        LALT(LGUI(KC_MEDIA_EJECT)),LGUI(LCTL(KC_Q)),LGUI(LSFT(KC_3)),                                KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          QK_BOOT,
    KC_NO,          KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_MEDIA_STOP,  KC_MEDIA_PLAY_PAUSE,LGUI(LSFT(KC_4)),                                KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    SWAP_BASE_LAYER_COLOR,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    TD(DANCE_1),          KC_BRIGHTNESS_DOWN,KC_BRIGHTNESS_UP,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,                                  KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [5] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_KP_0,        KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_KP_ASTERISK, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_KP_PLUS,     KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_KP_SLASH,    KC_TRANSPARENT,
    TO(0),          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_KP_MINUS,    KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_NO,          KC_NO,
                                                    KC_NO,          KC_NO,                                          KC_NO,          KC_TRANSPARENT
  ),
};



extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();

  user_config.raw = eeconfig_read_user();
  current_color_index = user_config.color_index;
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255} },

    [1] = { {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255}, {122,252,255} },

    [2] = { {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {81,239,252}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239} },

    [3] = { {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {0,248,239}, {81,239,252}, {81,239,252}, {0,248,239}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252}, {81,239,252} },

    [4] = { {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255} },

};

static void set_shift_keys_color(void) {
    if (is_caps_word_on()) {
      rgb_matrix_set_color( 49, RGB_WHITE);
    }
}

void set_layer_color(int layer) {
  if (layer == TARGET_LAYER) {
    HSV hsv = {
      .h = pgm_read_byte(&color_array[current_color_index][0]),
      .s = pgm_read_byte(&color_array[current_color_index][1]),
      .v = pgm_read_byte(&color_array[current_color_index][2]),
    };
    RGB rgb = hsv_to_rgb( hsv );
    float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
    rgb_matrix_set_color_all( f * rgb.r, f * rgb.g, f * rgb.b );
    set_shift_keys_color();
    return;
  }
  if (layer == 4) {
    rgb_matrix_set_color_all(RGB_WHITE);
    set_shift_keys_color();
    return;
  }
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
  set_shift_keys_color();
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
      return false;
  }
  if (keyboard_config.disable_layer_led) { return false; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CMD_TAB:
      if (record->event.pressed) {
        // CMD + TAB
        tap_code16(G(KC_TAB));
      }
      break;
    case MAC_DND:
      HSS(0x9B);
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case CLEAR_OSM_MOD_LEFT:
      if (record->event.pressed) {
        clear_oneshot_mods();
      }
      return false;
    case CLEAR_OSM_MOD_RIGHT:
      if (record->event.pressed) {
        clear_oneshot_mods();
      }
      return false;
    case SWAP_BASE_LAYER_COLOR:
      if (record->event.pressed) {
        current_color_index = (current_color_index + 1) % COLOR_COUNT;
        user_config.color_index = current_color_index;
      }
      return false; // Skip all further processing of this key
  }
  return true; // Process all other keycodes normally
}


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

const key_override_t *key_overrides_list[] = {
  &delete_key_override,
  &delete_word_key_override,
  NULL
};

const key_override_t **key_overrides = (const key_override_t **)key_overrides_list;

void housekeeping_task_user(void) {
  if (!is_transport_connected()) { // keyboard half is disconnected
//    layer_move(1);
  }
}

void eeconfig_init_user(void) {  // EEPROM is getting reset
  user_config.raw = 0;
  current_color_index = 0;
  user_config.color_index = current_color_index;
  eeconfig_update_user(user_config.raw);
}

void caps_word_set_user(bool active) {
  if (active) {
    set_shift_keys_color();
  } else {
    set_layer_color(0);
  }
}