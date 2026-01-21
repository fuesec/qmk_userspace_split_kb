/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright 2024 splitkb.com <support@splitkb.com> */

#pragma once

#undef ONESHOT_TIMEOUT
#define ONESHOT_TIMEOUT 2500

#undef RGB_MATRIX_TIMEOUT
#define RGB_MATRIX_TIMEOUT 180000

// #define USB_SUSPEND_WAKEUP_DELAY 0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 13

#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY 0

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 10

#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 6

#undef MOUSEKEY_WHEEL_INTERVAL
#define MOUSEKEY_WHEEL_INTERVAL 65

#define CAPS_WORD_IDLE_TIMEOUT 3000  // 3 seconds.
#define HSS(report) host_system_send(record->event.pressed ? report : 0); return false
#define HCS(report) host_consumer_send(record->event.pressed ? report : 0); return false

#define CIRQUE_PINNACLE_TAP_ENABLE
#define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE

