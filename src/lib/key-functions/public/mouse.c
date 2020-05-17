
#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include <math.h>
#include "../../../lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "../../../lib/usb/usage-page/keyboard.h"
#include "../../../keyboard/layout.h"
#include "../../../main.h"
#include "../public.h"
#include "../private.h"

// ----------------------------------------------------------------------------

// convenience macros
#define  LAYER      main_arg_layer
#define  ROW        main_arg_row
#define  COL        main_arg_col
#define  IS_PRESSED main_arg_is_pressed

#define MOVE_SCALAR 40
#define SCROLL_SCALAR 15
#define INPUT_SCALAR 100
#define DEAD_ZONE 3

uint8_t _mouse_modifier = 0;
#define SCROLL_X_ENABLED ((_mouse_modifier & MOUSE_SCROLL_X) == MOUSE_SCROLL_X)
#define SCROLL_Y_ENABLED ((_mouse_modifier & MOUSE_SCROLL_Y) == MOUSE_SCROLL_Y)
#define SLOW_MOUSE_ENABLED ((_mouse_modifier & MOUSE_SLOW) == MOUSE_SLOW)

void mouse_button_press_release(void) {
    uint8_t buttoncode = kb_layout_get(LAYER, ROW, COL);

    if (IS_PRESSED) {
        mouse_buttons |= buttoncode;
    } else {
        mouse_buttons &= ~buttoncode;
    }
}

void mouse_modifier_press_release(void) {
    uint8_t modifiercode = kb_layout_get(LAYER, ROW, COL);

    if (IS_PRESSED) {
        _mouse_modifier |= modifiercode;
    } else {
        _mouse_modifier &= ~modifiercode;
    }
}

int8_t _map_mouse_input_value(int16_t in) {
    return floor(in/1023.0f * INPUT_SCALAR * 2) - INPUT_SCALAR;
}

int8_t _map_mouse_move(int8_t in) {
    uint8_t scalar = SCROLL_X_ENABLED || SCROLL_Y_ENABLED ? SCROLL_SCALAR : MOVE_SCALAR;
    if (SLOW_MOUSE_ENABLED) {
        scalar = scalar / 4;
    }
    return floor((in/(INPUT_SCALAR * 1.0f) * scalar));
}

void mouse_move(uint16_t yin, uint16_t xin) {
    int8_t x, y, movex, movey;

    mouse_position[0] = 0;
    mouse_position[1] = 0;
    mouse_position[2] = 0;
    mouse_position[3] = 0;

    if (main_layers_peek(0) == 0) {
        return;
    }

    y = _map_mouse_input_value(yin + 25) * -1;
    x = _map_mouse_input_value(xin - 13) * -1;

    if (fabs(x) < DEAD_ZONE) {
        x = 0;
    }
    if (fabs(y) < DEAD_ZONE) {
        y = 0;
    }

    if (x == 0 && y == 0) {
        return;
    }
    
    double r = sqrt(pow(x, 2.0) + pow(y, 2.0));
    // small twist
    double a = atan2(y, x) - 0.8;
    x = floor(r * cos(a));
    y = floor(r * sin(a));
    
    movey = _map_mouse_move(y);
    movex = _map_mouse_move(x);


    if (SCROLL_X_ENABLED || SCROLL_Y_ENABLED) {
        _delay_ms(100);
        if (SCROLL_X_ENABLED) {
            mouse_position[3] = movex;
        }
        if (SCROLL_Y_ENABLED) {
            mouse_position[2] = movey;
        }
        return;
    }

    mouse_position[0] = movex;
    mouse_position[1] = movey * -1;
}
