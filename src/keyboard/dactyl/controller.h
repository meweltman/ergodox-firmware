/* ----------------------------------------------------------------------------
 * ergoDOX : controller specific exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef KEYBOARD__DACTYL__CONTROLLER_h
	#define KEYBOARD__DACTYL__CONTROLLER_h

	#include <stdbool.h>
	#include <stdint.h>
	#include "./matrix.h"

	// --------------------------------------------------------------------

	/*
	 * empty led macros for this keyboard since I didn't add any leds
	 */

	#define kb_led_state_power_on()
	#define kb_led_delay_usb_init()
	#define kb_led_state_ready()
	#define kb_led_num_on()
	#define kb_led_num_off()
	#define kb_led_caps_on()
	#define kb_led_caps_off()
	#define kb_led_scroll_on()
	#define kb_led_scroll_off()
	#define kb_led_compose_on()
	#define kb_led_compose_off()
	#define kb_led_kana_on()
	#define kb_led_kana_off()

	// --------------------------------------------------------------------

	uint8_t kb_init(void);
	uint8_t kb_update_matrix(bool matrix[KB_ROWS][KB_COLUMNS]);
	uint8_t kb_read_trackball(uint16_t result[4], uint16_t cycles);
	void kb_trackball_white(void);
#endif
