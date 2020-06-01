/* ----------------------------------------------------------------------------
 * ergoDOX : controller : Teensy 2.0 specific exports : functions
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef KEYBOARD__DACTYL__CONTROLLER__TEENSY_2_0__FUNCTIONS_h
	#define KEYBOARD__DACTYL__CONTROLLER__TEENSY_2_0__FUNCTIONS_h

	#include <stdbool.h>
	#include <stdint.h>
	#include "../matrix.h"

	// --------------------------------------------------------------------

	uint8_t teensy_init(void);
	uint8_t teensy_update_matrix( bool matrix[KB_ROWS][KB_COLUMNS] );
	uint8_t teensy_read_trackball(uint16_t result[4], uint16_t cycles);
	void teensy_trackball_white_on();
	void teensy_trackball_white_off();
	void teensy_trackball_red_on();
	void teensy_trackball_red_off();
#endif
