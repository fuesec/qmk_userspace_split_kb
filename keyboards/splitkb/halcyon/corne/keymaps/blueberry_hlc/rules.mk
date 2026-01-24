# rotary encoder
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes
# for double key press etc.
TAP_DANCE_ENABLE = yes
# e.g. shift + backspace -> forward delete
KEY_OVERRIDE_ENABLE = yes
CAPS_WORD_ENABLE = yes
MOUSE_ENABLE = yes
# mouse wiggler
DEFERRED_EXEC_ENABLE = yes
# for select word module
OS_DETECTION_ENABLE = yes
SPACE_CADET_ENABLE = no
CONSOLE_ENABLE=no

SRC += custom_oneshot.c

# This adds module functionality to your keyboard (files found in users/halcyon_modules)
USER_NAME := halcyon_modules
