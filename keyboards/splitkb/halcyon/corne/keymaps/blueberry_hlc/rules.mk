# rotary encoder
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = no
# for double key press etc.
TAP_DANCE_ENABLE = no
# e.g. shift + backspace -> forward delete
KEY_OVERRIDE_ENABLE = yes
CAPS_WORD_ENABLE = yes
MOUSE_ENABLE = yes
# mouse wiggler
DEFERRED_EXEC_ENABLE = yes
# for select word module
OS_DETECTION_ENABLE = yes
SPACE_CADET_ENABLE = no
# split-link debugging: flip back to no when done (see keymap.c split_link_debug_task)
CONSOLE_ENABLE = yes
DEBUG_MATRIX_SCAN_RATE_ENABLE = yes
KEYCODE_STRING_ENABLE = yes

# This adds module functionality to your keyboard (files found in users/halcyon_modules)
USER_NAME := halcyon_modules
