
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

uint16_t _scale_dir(uint16_t value) {
    if (SCROLL_X_ENABLED || SCROLL_Y_ENABLED) {
        if (value == 1) return 8;
        if (value == 2) return 20;
        if (value == 3) return 40;
        if (value == 4) return 80;
        return 127;
    }
    if (value == 1) return 3;
    if (value == 2) return 9;
    if (value == 3) return 25;
    if (value == 4) return 50;
    if (value == 5) return 100;
    return 127; 
}

// ----------------------------------------------------------------------------
void trackball_move(uint16_t up, uint16_t down, uint16_t left, uint16_t right) {
    int8_t movex = 0, movey = 0;

    mouse_position[0] = 0;
    mouse_position[1] = 0;
    mouse_position[2] = 0;
    mouse_position[3] = 0;

    if (main_layers_peek(0) == 0) {
        return;
    }
    
    if (left > 0)
    {
        movey = -_scale_dir(left);
    }
    if (right > 0)
    {
        movey = _scale_dir(right);
    }
    if (up > 0)
    {
        movex = _scale_dir(up);
    }
    if (down > 0)
    {
        movex = -_scale_dir(down);
    }

    if (SCROLL_X_ENABLED || SCROLL_Y_ENABLED) {
        _delay_ms(100);
        if (SCROLL_X_ENABLED) {
            mouse_position[3] = movex;
        }
        if (SCROLL_Y_ENABLED) {
            mouse_position[2] = -movey;
        }
        return;
    }

    mouse_position[0] = movex;
    mouse_position[1] = movey;
}

