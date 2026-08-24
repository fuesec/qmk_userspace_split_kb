#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#ifdef CONSOLE_ENABLE
#    include "split_util.h"
#    include "transactions.h"

// Split-link diagnostics.
//
// Rows 0-4 are the left (master) half, rows 5-9 the right (slave) half, so every
// key event can be attributed to a half. On top of that we poll the slave for its
// own uptime: if that value ever goes backwards, the right half rebooted (power /
// VBUS problem) rather than merely losing the UART link (data pin problem).
typedef struct __attribute__((packed)) {
    uint32_t uptime_ms;
} link_probe_t;

#    define LINK_PROBE_INTERVAL_MS 200
#    define LINK_HEARTBEAT_MS 1000

// Runs on the slave (right) half.
void user_link_probe_slave_handler(uint8_t in_size, const void *in, uint8_t out_size, void *out) {
    if (out_size == sizeof(link_probe_t)) {
        ((link_probe_t *)out)->uptime_ms = timer_read32();
    }
}

static void split_link_debug_task(void) {
    static bool     link_up       = true;
    static uint32_t probe_timer   = 0;
    static uint32_t beat_timer    = 0;
    static uint32_t down_since    = 0;
    static uint32_t slave_uptime  = 0;
    static uint16_t probe_fails   = 0;
    static uint16_t slave_reboots = 0;

    if (!is_keyboard_master()) return;

    // Edges of QMK's own connection state, timestamped to the millisecond.
    bool now_up = is_transport_connected();
    if (now_up != link_up) {
        uint32_t now = timer_read32();
        if (now_up) {
            uprintf("[SPLIT] UP t=%lu outage=%lums\n", (unsigned long)now, (unsigned long)(now - down_since));
        } else {
            down_since = now;
            uprintf("[SPLIT] DOWN t=%lu\n", (unsigned long)now);
        }
        link_up = now_up;
    }

    if (timer_elapsed32(probe_timer) < LINK_PROBE_INTERVAL_MS) return;
    probe_timer = timer_read32();

    link_probe_t probe = {0};
    if (!transaction_rpc_recv(USER_LINK_PROBE, sizeof(probe), &probe)) {
        probe_fails++;
        uprintf("[SPLIT] probe FAIL t=%lu fails=%u\n", (unsigned long)probe_timer, probe_fails);
        return;
    }

    if (probe.uptime_ms < slave_uptime) {
        slave_reboots++;
        uprintf("[SPLIT] SLAVE REBOOT t=%lu slave_uptime=%lu (was %lu) reboots=%u\n", (unsigned long)probe_timer, (unsigned long)probe.uptime_ms, (unsigned long)slave_uptime, slave_reboots);
    }
    slave_uptime = probe.uptime_ms;

    if (timer_elapsed32(beat_timer) >= LINK_HEARTBEAT_MS) {
        beat_timer = probe_timer;
        uprintf("[SPLIT] hb t=%lu slave=%lu skew=%ldms fails=%u reboots=%u\n", (unsigned long)probe_timer, (unsigned long)slave_uptime, (long)((int32_t)probe_timer - (int32_t)slave_uptime), probe_fails, slave_reboots);
    }
}

void housekeeping_task_user(void) {
    split_link_debug_task();
}
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
	CKC_MAC_BACK,
	CKC_MAC_FORWARD,
	CKC_MAC_PREVIOUS_TAB,
    CKC_MAC_NEXT_TAB,
};

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LAYER_BASE]               = LAYOUT_corne_hlc(
        KC_ESCAPE,           KC_Q,    KC_W,    KC_E,                       KC_R,                KC_T,                    KC_Y,                            KC_U,     KC_I,                KC_O,    KC_P,    KC_BSPC,
        KC_TAB,              KC_A,    KC_S,    KC_D,                       KC_F,                KC_G,                    KC_H,                            KC_J,     KC_K,                KC_L,    KC_SCLN, KC_ENTER,
        QK_CAPS_WORD_TOGGLE, KC_Z,    KC_X,    KC_C,                       KC_V,                KC_B,                    KC_N,                            KC_M,     KC_COMM,             KC_DOT,  KC_SLSH, QK_CAPS_WORD_TOGGLE,
                                               CKC_MO_LAYER_FUNCTION_KEYS, CKC_MO_LAYER_NUMPAD, CKC_MO_LAYER_NAVIGATION, CKC_MO_LAYER_SPECIAL_CHARACTERS, KC_SPACE, CKC_MO_LAYER_SYSTEM,
                             KC_MUTE, XXXXXXX, XXXXXXX,                    XXXXXXX,             XXXXXXX,                 XXXXXXX,                         XXXXXXX,  XXXXXXX,             XXXXXXX, XXXXXXX
    ),
[LAYER_NAVIGATION]         = LAYOUT_corne_hlc(
        _______,      QK_MOUSE_WHEEL_LEFT, QK_MOUSE_WHEEL_RIGHT, QK_MOUSE_BUTTON_2, QK_MOUSE_BUTTON_1, QK_MOUSE_WHEEL_UP,   KC_HOME, CKC_MAC_BACK,         CKC_MAC_FORWARD,  SELECT_LINE, SELECT_LINE_UP, SELECT_WORD_BACK,
        _______,      KC_LEFT_CTRL,            KC_LEFT_SHIFT,            KC_LEFT_ALT,           KC_LEFT_GUI,           QK_MOUSE_WHEEL_DOWN, KC_END,  KC_LEFT,              KC_RIGHT,         KC_DOWN,                              KC_UP,                                 SELECT_WORD,
        KC_LEFT_ALT, KC_LEFT_SHIFT,       KC_LEFT_ALT,          KC_LEFT_GUI,       KC_MEH,           KC_HYPR,           XXXXXXX, CKC_MAC_PREVIOUS_TAB, CKC_MAC_NEXT_TAB, KC_PAGE_DOWN,                         KC_PAGE_UP,                            _______,
                                                                 _______,           _______,           _______,             _______, _______,              _______,
                      _______,             _______,              _______,           _______,           _______,             _______, _______,              _______,          _______,                              _______
),
[LAYER_SPECIAL_CHARACTERS] = LAYOUT_corne_hlc(
        _______, KC_GRAVE,        KC_LEFT_BRACKET, KC_LEFT_CURLY_BRACE, KC_LEFT_PAREN, KC_KP_ASTERISK, KC_PERCENT, KC_RIGHT_PAREN, KC_RIGHT_CURLY_BRACE, KC_RIGHT_BRACKET, KC_TILDE,     XXXXXXX,
        _______, KC_DOUBLE_QUOTE, KC_EXCLAIM,      KC_KP_EQUAL,         KC_KP_MINUS,   KC_HASH,        KC_DOLLAR,  KC_LEFT_GUI,        KC_LEFT_ALT,              KC_LEFT_SHIFT,        KC_LEFT_CTRL,     XXXXXXX,
        XXXXXXX, KC_QUOTE,        KC_AT,           KC_KP_PLUS,          KC_UNDERSCORE, KC_CIRCUMFLEX,  KC_HYPR,  KC_MEH,        KC_AMPERSAND,         KC_PIPE,          KC_BACKSLASH, XXXXXXX,
                                                   _______,             _______,       _______,        _______,    _______,        _______,
                 _______,         _______,         _______,             _______,       _______,        _______,    _______,        _______,              _______,          _______
),
[LAYER_NUMPAD]             = LAYOUT_corne_hlc(
        _______, XXXXXXX,  XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,   KC_KP_MINUS,        KC_1,    KC_2,    KC_3,    KC_KP_COMMA,   KC_KP_SLASH,
        _______, KC_LEFT_CTRL, KC_LEFT_SHIFT, KC_LEFT_ALT, KC_LEFT_GUI, XXXXXXX,   KC_KP_PLUS,  KC_4,    KC_5,    KC_6,    KC_KP_DOT, KC_KP_ASTERISK,
        XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX, KC_MEH, KC_HYPR, KC_0, KC_7,    KC_8,    KC_9,    KC_KP_EQUAL, XXXXXXX,
                                      _______, _______, _______,   _______,     _______, _______,
                 _______,  _______,   _______, _______, _______,   _______,     _______, _______, _______, _______
),
[LAYER_FUNCTION_KEYS]      = LAYOUT_corne_hlc(
        _______, XXXXXXX,  XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F10, XXXXXXX,
        _______, KC_LEFT_CTRL, KC_LEFT_SHIFT, KC_LEFT_ALT, KC_LEFT_GUI, XXXXXXX,   XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11, XXXXXXX,
        XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX, KC_MEH, KC_HYPR, XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F12, XXXXXXX,
                                      _______, _______, _______,   _______, _______, _______,
                 _______,  _______,   _______, _______, _______,   _______, _______, _______, _______, _______
),
[LAYER_SYSTEM]             = LAYOUT_corne_hlc(
        _______, 				 KC_MEDIA_PREV_TRACK,   KC_MEDIA_NEXT_TRACK,    KC_MEDIA_STOP,     	KC_MEDIA_PLAY_PAUSE, 		XXXXXXX,       		XXXXXXX,              XXXXXXX,          		   XXXXXXX, 				XXXXXXX,                XXXXXXX,              QK_BOOTLOADER,
        CKC_MOUSE_JIGGLE,        KC_BRIGHTNESS_DOWN,    KC_BRIGHTNESS_UP,       KC_AUDIO_VOL_DOWN, 	KC_AUDIO_VOL_UP,     		KC_AUDIO_MUTE, 		QK_RGB_MATRIX_TOGGLE, XXXXXXX,                     XXXXXXX,                 XXXXXXX,                XXXXXXX,              XXXXXXX,
        CKC_MAC_SLEEP,           CKC_MAC_SLEEP_DISPLAY, CKC_MAC_DO_NOT_DISTURB, CKC_MAC_SCREENSHOT,	CKC_MAC_SCREENSHOT_AREA,    CKC_MAC_LOCK,       LUMINO,               QK_RGB_MATRIX_MODE_PREVIOUS, QK_RGB_MATRIX_MODE_NEXT, QK_RGB_MATRIX_HUE_DOWN, QK_RGB_MATRIX_HUE_UP, XXXXXXX,
                                                                         _______,           _______,             _______,       _______,              XXXXXXX,                     XXXXXXX,
                          _______,               _______,                _______,           _______,             _______,       _______,              _______,                     _______,                 _______,                _______
)};

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    // One compact line per key event. "half" is L/R so dropped or phantom events can
    // be attributed to a half at a glance: rows 0-4 are left, rows 5-9 are right.
    uprintf("[KEY] t=%lu half=%c row=%u col=%u %s %s\n", (unsigned long)timer_read32(), record->event.key.row < 5 ? 'L' : 'R', record->event.key.row, record->event.key.col, record->event.pressed ? "DOWN" : "UP  ", get_keycode_string(keycode));
#endif
	switch (keycode) {
        case CKC_MAC_BACK:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("["));
            }
            return false;
        case CKC_MAC_FORWARD:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("]"));
            }
            return false;
        case CKC_MAC_PREVIOUS_TAB:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LSFT("[")));
            }
            return false;
        case CKC_MAC_NEXT_TAB:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LSFT("]")));
            }
            return false;
    }

    if (record->event.pressed) {
        static deferred_token token  = INVALID_DEFERRED_TOKEN;
        static report_mouse_t report = {0};
        if (token) {
            // If jiggler is currently running, stop when any key is pressed.
            cancel_deferred_exec(token);
            token  = INVALID_DEFERRED_TOKEN;
            report = (report_mouse_t){}; // Clear the mouse.
            host_mouse_send(&report);
        } else if (keycode == CKC_MOUSE_JIGGLE) {
            uint32_t jiggler_callback(uint32_t trigger_time, void *cb_arg) {
                // Deltas to move in a circle of radius 20 pixels over 32 frames.
                static const int8_t deltas[32] = {0, -1, -2, -2, -3, -3, -4, -4, -4, -4, -3, -3, -2, -2, -1, 0, 0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 3, 3, 2, 2, 1, 0};
                static uint8_t      phase      = 0;
                // Get x delta from table and y delta by rotating a quarter cycle.
                report.x = deltas[phase];
                report.y = deltas[(phase + 8) & 31];
                phase    = (phase + 1) & 31;
                host_mouse_send(&report);
                return 16; // Call the callback every 16 ms.
            }

            token = defer_exec(1, jiggler_callback, NULL); // Schedule callback.
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

#ifdef KEY_OVERRIDE_ENABLE
const key_override_t delete_key_override = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT,                   // Trigger modifier
                                                                                   KC_BSPC,                          // Trigger key
                                                                                   KC_DEL,                           // Replacement key
                                                                                   ~0,                               // Activate on all layers
                                                                                   MOD_MASK_GUI,                     // Do not activate when
                                                                                   ko_option_no_reregister_trigger); // Specifies that the play key is not registered again after lifting "Trigger modifier"

const key_override_t delete_word_key_override = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT | MOD_MASK_ALT,    // Trigger modifier
                                                                                        KC_BSPC,                          // Trigger key
                                                                                        MO(KC_DEL),                       // Replacement key
                                                                                        ~0,                               // Activate on all layers
                                                                                        MOD_MASK_GUI,                     // Do not activate when
                                                                                        ko_option_no_reregister_trigger); // Specifies that the play key is not registered again after lifting "Trigger modifier"

const key_override_t *key_overrides[] = {&delete_key_override, &delete_word_key_override, NULL};
#endif

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
#ifdef CONSOLE_ENABLE
    transaction_register_rpc(USER_LINK_PROBE, user_link_probe_slave_handler);

    debug_enable = true;
    // debug_matrix dumps all 10 matrix rows on every change. That is enough console
    // traffic to perturb the very timing we are measuring, and process_record_user
    // below already reports each key with its row/col. Leave it off for split-link
    // hunting; turn it on only when chasing a matrix-level problem.
    debug_matrix   = false;
    debug_keyboard = false;
    // debug_mouse=true;
#endif
}

