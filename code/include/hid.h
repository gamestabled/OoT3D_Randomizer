/*
 * From n3rdswithgame, who may or may not have originally written this
 */

#ifndef HID_H
#define HID_H

#include <stdint.h>

typedef union {
    uint32_t val;
    struct {
        uint32_t a : 1;        // 1
        uint32_t b : 1;        // 2
        uint32_t sel : 1;      // 3
        uint32_t strt : 1;     // 4
        uint32_t d_right : 1;  // 5
        uint32_t d_left : 1;   // 6
        uint32_t d_up : 1;     // 7
        uint32_t d_down : 1;   // 8
        uint32_t r : 1;        // 9
        uint32_t l : 1;        // 10
        uint32_t x : 1;        // 11
        uint32_t y : 1;        // 12
        uint32_t gpio : 2;     // 14
        uint32_t padding : 14; // 28
        uint32_t c_right : 1;  // 29
        uint32_t c_left : 1;   // 30
        uint32_t c_up : 1;     // 31
        uint32_t c_down : 1;   // 32
    };
} btn_t;

typedef union {
    uint32_t val;
    struct {
        int16_t x;
        int16_t y;
    };
} cp_t;

typedef struct {
    btn_t curr;
    btn_t pressed;
    btn_t released;
    cp_t cp;
} pad_t;

struct hid_pad_t {
    uint64_t timestamp;      // 0
    uint64_t timestamp_last; // 8
    uint32_t index;          // 10
    uint32_t pad_14[2];      // 14
    btn_t btn_raw;           // 1c
    cp_t cp_raw;             // 20
    uint8_t pad_24;          // 24
    pad_t pads[8];
};

struct touch_input_t {
    int16_t x;
    int16_t y;
};

typedef struct {
    struct touch_input_t touch;
    uint32_t updated;
} touch_t;

struct hid_touch_t {
    uint64_t timestamp;      // 0
    uint64_t timestamp_last; // 8
    uint32_t index;          // 10
    uint32_t pad_14;         // 14
    touch_t raw;
    touch_t touches[8];
};

typedef struct {
    struct hid_pad_t pad;
    struct hid_touch_t touch;
} hid_mem_t;

typedef struct {
    uint32_t field_00;
    struct hid_pad_t* hid_pad;
    uint32_t field_08;
    struct hid_touch_t* hid_touch;
    uint32_t field_10;
    uint32_t* hid_accl; // need to add
    uint32_t field_18;
    uint32_t field_1c;
    uint32_t* hid_gyro; // need to add
    uint32_t field_24;
    uint32_t* hid_debug;            // might add
    uint32_t mappable_mem_chunk[4]; // need to add
    uint32_t bool_3c;
    uint32_t hid_handle;
    uint32_t bool_44;
} hid_ctx_t;

#define BUTTON_A (1 << 0)
#define BUTTON_B (1 << 1)
#define BUTTON_SELECT (1 << 2)
#define BUTTON_START (1 << 3)
#define BUTTON_RIGHT (1 << 4)
#define BUTTON_LEFT (1 << 5)
#define BUTTON_UP (1 << 6)
#define BUTTON_DOWN (1 << 7)
#define BUTTON_R1 (1 << 8)
#define BUTTON_L1 (1 << 9)
#define BUTTON_X (1 << 10)
#define BUTTON_Y (1 << 11)
#define CPAD_RIGHT (1 << 28)
#define CPAD_LEFT (1 << 29)
#define CPAD_UP (1 << 30)
#define CPAD_DOWN (1 << 31)

// Generic catch-all directions
#define PAD_RIGHT (BUTTON_RIGHT | CPAD_RIGHT)
#define PAD_LEFT (BUTTON_LEFT | CPAD_LEFT)
#define PAD_UP (BUTTON_UP | CPAD_UP)
#define PAD_DOWN (BUTTON_DOWN | CPAD_DOWN)

#endif // HID_H
