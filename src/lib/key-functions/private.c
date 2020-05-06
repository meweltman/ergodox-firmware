/* ----------------------------------------------------------------------------
 * key functions : private : code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include <math.h>
#include "../../lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "../../lib/usb/usage-page/keyboard.h"
#include "../../keyboard/layout.h"
#include "../../keyboard/matrix.h"
#include "../../main.h"
#include "./public.h"

/*
 * MediaCodeLookupTable is used to translate from enumeration in keyboard.h to
 *  consumer key scan code in usb_keyboard.h
 */
static const uint16_t _media_code_lookup_table[] = {
	TRANSPORT_PLAY_PAUSE, /* MEDIAKEY_PLAY_PAUSE */
	TRANSPORT_STOP, /* MEDIAKEY_STOP */
	TRANSPORT_PREV_TRACK, /* MEDIAKEY_PREV_TRACK */
	TRANSPORT_NEXT_TRACK, /* MEDIAKEY_NEXT_TRACK */
	AUDIO_MUTE, /* MEDIAKEY_AUDIO_MUTE */
	AUDIO_VOL_UP, /* MEDIAKEY_AUDIO_VOL_UP */
	AUDIO_VOL_DOWN, /* MEDIAKEY_AUDIO_VOL_DOWN */
};

// ----------------------------------------------------------------------------

/*
 * Generate a normal keypress or keyrelease
 *
 * Arguments
 * - press: whether to generate a keypress (true) or keyrelease (false)
 * - keycode: the keycode to use
 *
 * Note
 * - Because of the way USB does things, what this actually does is either add
 *   or remove 'keycode' from the list of currently pressed keys, to be sent at
 *   the end of the current cycle (see main.c)
 */
void _kbfun_press_release(bool press, uint8_t keycode) {
	// no-op
	if (keycode == 0)
		return;

	// modifier keys
	switch (keycode) {
		case KEY_LeftControl:  (press)
				       ? (keyboard_modifier_keys |=  (1<<0))
				       : (keyboard_modifier_keys &= ~(1<<0));
				       return;
		case KEY_LeftShift:    (press)
				       ? (keyboard_modifier_keys |=  (1<<1))
				       : (keyboard_modifier_keys &= ~(1<<1));
				       return;
		case KEY_LeftAlt:      (press)
				       ? (keyboard_modifier_keys |=  (1<<2))
				       : (keyboard_modifier_keys &= ~(1<<2));
				       return;
		case KEY_LeftGUI:      (press)
				       ? (keyboard_modifier_keys |=  (1<<3))
				       : (keyboard_modifier_keys &= ~(1<<3));
				       return;
		case KEY_RightControl: (press)
				       ? (keyboard_modifier_keys |=  (1<<4))
				       : (keyboard_modifier_keys &= ~(1<<4));
				       return;
		case KEY_RightShift:   (press)
				       ? (keyboard_modifier_keys |=  (1<<5))
				       : (keyboard_modifier_keys &= ~(1<<5));
				       return;
		case KEY_RightAlt:     (press)
				       ? (keyboard_modifier_keys |=  (1<<6))
				       : (keyboard_modifier_keys &= ~(1<<6));
				       return;
		case KEY_RightGUI:     (press)
				       ? (keyboard_modifier_keys |=  (1<<7))
				       : (keyboard_modifier_keys &= ~(1<<7));
				       return;
	}

	// all others
	for (uint8_t i=0; i<6; i++) {
		if (press) {
			if (keyboard_keys[i] == 0) {
				keyboard_keys[i] = keycode;
				return;
			}
		} else {
			if (keyboard_keys[i] == keycode) {
				keyboard_keys[i] = 0;
				return;
			}
		}
	}
}

/*
 * Is the given keycode pressed?
 */
bool _kbfun_is_pressed(uint8_t keycode) {
	// modifier keys
	switch (keycode) {
		case KEY_LeftControl:  if (keyboard_modifier_keys & (1<<0))
					       return true;
		case KEY_LeftShift:    if (keyboard_modifier_keys & (1<<1))
					       return true;
		case KEY_LeftAlt:      if (keyboard_modifier_keys & (1<<2))
					       return true;
		case KEY_LeftGUI:      if (keyboard_modifier_keys & (1<<3))
					       return true;
		case KEY_RightControl: if (keyboard_modifier_keys & (1<<4))
					       return true;
		case KEY_RightShift:   if (keyboard_modifier_keys & (1<<5))
					       return true;
		case KEY_RightAlt:     if (keyboard_modifier_keys & (1<<6))
					       return true;
		case KEY_RightGUI:     if (keyboard_modifier_keys & (1<<7))
					       return true;
	}

	// all others
	for (uint8_t i=0; i<6; i++)
		if (keyboard_keys[i] == keycode)
			return true;

	return false;
}

void _kbfun_mediakey_press_release(bool press, uint8_t keycode) {
	uint16_t mediakey_code = _media_code_lookup_table[keycode];
	if (press) {
		consumer_key = mediakey_code;
	} else {
		// Only one key can be pressed at a time so only clear the keypress for
		//  active key (most recently pressed)
		if (mediakey_code == consumer_key) {
			consumer_key = 0;
		}
	}
}

void _kbfun_mousebutton_press_release(bool press, uint8_t buttoncode) {
	if (press) {
		mouse_buttons |= buttoncode;
	} else {
		mouse_buttons &= ~buttoncode;
	}
}

uint8_t _move_scalar = 40,
		_scroll_scalar = 15,
		_input_scalar = 100,
		_dead_zone = 3,
		_mouse_modifier = 0;

void _kbfun_mouse_modifier_press_release(bool press, uint8_t modifiercode) {
	if (press) {
		_mouse_modifier |= modifiercode;
	} else {
		_mouse_modifier &= ~modifiercode;
	}
}

bool modifierEnabled(uint8_t modifier) {
	return (_mouse_modifier & modifier) == modifier;
}

bool scrollX() {
	return modifierEnabled(MOUSE_SCROLL_X);
}

bool scrollY() {
	return modifierEnabled(MOUSE_SCROLL_Y);
}

bool slow() {
	return modifierEnabled(MOUSE_SLOW);
}

int8_t _map_mouse_input_value(int16_t in) {
	return floor(in/1023.0f * _input_scalar * 2) - _input_scalar;
}

int8_t _map_mouse_move(int8_t in) {
	uint8_t scalar = scrollX() || scrollY() ? _scroll_scalar : _move_scalar;
	if (slow()) {
		scalar = scalar / 4;
	}
	return floor((in/(_input_scalar * 1.0f) * scalar));
}

void _kbfun_mouse_move(uint16_t yin, uint16_t xin) {
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

	if (fabs(x) < _dead_zone) {
		x = 0;
	}
	if (fabs(y) < _dead_zone) {
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


	if (scrollX() || scrollY()) {
		_delay_ms(100);
		if (scrollX()) {
			mouse_position[3] = movex;
		}
		if (scrollY()) {
			mouse_position[2] = movey;
		}
		return;
	}

	mouse_position[0] = movex;
	mouse_position[1] = movey * -1;
}
