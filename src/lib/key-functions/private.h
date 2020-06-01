/* ----------------------------------------------------------------------------
 * key functions : private : exports
 *
 * Things to be used only by keyfunctions.  Exported so layouts can use these
 * functions to help define their own, if they like.
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef LIB__KEY_FUNCTIONS__INTERNAL_h
	#define LIB__KEY_FUNCTIONS__INTERNAL_h

	#include <stdbool.h>
	#include <stdint.h>
	#include "../../keyboard/matrix.h"

	#define SCROLL_X_ENABLED ((_get_mouse_modifier() & MOUSE_SCROLL_X) == MOUSE_SCROLL_X)
	#define SCROLL_Y_ENABLED ((_get_mouse_modifier() & MOUSE_SCROLL_Y) == MOUSE_SCROLL_Y)
	#define SLOW_MOUSE_ENABLED ((_get_mouse_modifier() & MOUSE_SLOW) == MOUSE_SLOW)

	// --------------------------------------------------------------------

	void _kbfun_press_release     (bool press, uint8_t keycode);
	bool _kbfun_is_pressed        (uint8_t keycode);
	void _kbfun_mediakey_press_release (bool press, uint8_t keycode);
	uint8_t _get_mouse_modifier();

#endif
