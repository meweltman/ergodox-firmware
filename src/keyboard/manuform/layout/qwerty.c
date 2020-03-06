/* ----------------------------------------------------------------------------
 * ergoDOX layout : QWERTY (modified from the Kinesis layout)
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdint.h>
#include <stddef.h>
#include <avr/pgmspace.h>
#include "../../../lib/data-types/misc.h"
#include "../../../lib/usb/usage-page/keyboard--short-names.h"
#include "../../../lib/key-functions/public.h"
#include "../matrix.h"
#include "../layout.h"

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

const uint8_t PROGMEM _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {

	KB_MATRIX_LAYER(  // layout: layer 0: default
// unused
0,
// left hand
_esc,    _1, _2,     _3,     _4,    _5,
_tab,    _Q, _W,     _E,     _R,    _T,
_shiftL, _A, _S,     _D,     _F,    _G,
_guiL,   _Z, _X,     _C,     _V,    _B,
             _grave, _equal, _bs,   _ctrlL,
                             1,     _altL,
                             _home, _end,
// right hand
_6,      _7,       _8,        _9,        _0,         _dash,
_Y,      _U,       _I,        _O,        _P,         _backslash,
_H,      _J,       _K,        _L,        _semicolon, _quote,
_N,      _M,       _comma,    _period,   _slash,     _shiftR,
_enter,  _space,   _bracketL, _bracketR,
_arrowU, _arrowD,
_arrowL, _arrowR),


	KB_MATRIX_LAYER(  // layout: layer 1: function and symbol keys
// unused
0,
// left hand
0,      _F1,    _F2,    _F3,    _F4,    _F5,
0,      0,      0,      0,      0,      0,
0,      0,      0,      0,      0,      0,
0,      0,      0,      0,      0,      0,
                0,      0,      0,      0,
                                1,      2,
                                0,      0,
// right hand
_F6,             _F7,           _F8,            _F9,             _F10,     _power,
0,              0,              0,              0,               0,        0,
0,              _mouseLeft,     _mouseMiddle,   _mouseRight,     0,        0,
0,              0,              0,              0,               0,        0,
_prevTrack,     _volDown,       _volUp,         _nextTrack,
_play,  0,
0,      0 ),


	KB_MATRIX_LAYER(  // layout: layer 2: keyboard functions
// unused
0,
// left hand
  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,
		  0,  2,
		  0,  0,
// right hand
0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,
0,  0,  0,  0,
0,  0,
0,  0 ),

};

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// aliases

// basic
#define  kprrel  &kbfun_press_release
#define  mprrel  &kbfun_mediakey_press_release
#define  mouseb  &mouse_button_press_release
#define  ktog    &kbfun_toggle
#define  ktrans  &kbfun_transparent
// --- layer push/pop functions
#define  lpush1   &kbfun_layer_push_1
#define  lpush2   &kbfun_layer_push_2
#define  lpush3   &kbfun_layer_push_3
#define  lpush4   &kbfun_layer_push_4
#define  lpush5   &kbfun_layer_push_5
#define  lpush6   &kbfun_layer_push_6
#define  lpush7   &kbfun_layer_push_7
#define  lpush8   &kbfun_layer_push_8
#define  lpush9   &kbfun_layer_push_9
#define  lpush10  &kbfun_layer_push_10
#define  lpop1    &kbfun_layer_pop_1
#define  lpop2    &kbfun_layer_pop_2
#define  lpop3    &kbfun_layer_pop_3
#define  lpop4    &kbfun_layer_pop_4
#define  lpop5    &kbfun_layer_pop_5
#define  lpop6    &kbfun_layer_pop_6
#define  lpop7    &kbfun_layer_pop_7
#define  lpop8    &kbfun_layer_pop_8
#define  lpop9    &kbfun_layer_pop_9
#define  lpop10   &kbfun_layer_pop_10
// ---

// device
#define  dbtldr  &kbfun_jump_to_bootloader

// special
#define  sshprr   &kbfun_shift_press_release
#define  s2kcap   &kbfun_2_keys_capslock_press_release
#define  slpunum  &kbfun_layer_push_numpad
#define  slponum  &kbfun_layer_pop_numpad

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

const void_funptr_t PROGMEM _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {

	KB_MATRIX_LAYER(  // press: layer 0: default
// unused
NULL,
// left hand
kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
sshprr, kprrel, kprrel, kprrel, kprrel, kprrel,
kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
                kprrel, kprrel, kprrel, kprrel,
                                lpush1, kprrel,
                                kprrel, kprrel,
// right hand
kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
kprrel, kprrel, kprrel, kprrel, kprrel, sshprr,
kprrel, kprrel, kprrel, kprrel,
kprrel, kprrel,
kprrel, kprrel ),


	KB_MATRIX_LAYER(  // press: layer 1: function and symbol keys
// unused
NULL,
// left hand
  NULL, kprrel, kprrel, kprrel, kprrel, kprrel,
ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
                ktrans, ktrans, ktrans, ktrans,
                                lpop1 , lpush2,
                                ktrans, ktrans,
// right hand
kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
ktrans, mouseb, mouseb, mouseb, ktrans, ktrans,
ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
mprrel, mprrel, mprrel, mprrel,
mprrel, ktrans,
ktrans, ktrans ),


	KB_MATRIX_LAYER(  // press: layer 2: keyboard functions
// unused
NULL,
// left hand
NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
                NULL,   NULL,   NULL,   NULL,
                                NULL,  lpop2,
                                NULL,   NULL,
// right hand
NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
NULL,   NULL,   NULL,   NULL,
NULL,   NULL,
NULL,   NULL ),

};

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

const void_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {

	KB_MATRIX_LAYER(  // release: layer 0: default
// unused
NULL,
// left hand
kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
sshprr, kprrel, kprrel, kprrel, kprrel, kprrel,
kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
                kprrel, kprrel, kprrel, kprrel,
                                lpop1 , kprrel,
                                kprrel, kprrel,
// right hand
kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
kprrel, kprrel, kprrel, kprrel, kprrel, sshprr,
kprrel, kprrel, kprrel, kprrel,
kprrel, kprrel,
kprrel, kprrel ),


	KB_MATRIX_LAYER(  // release: layer 1: function and symbol keys
// unused
NULL,
// left hand
  NULL, kprrel, kprrel, kprrel, kprrel, kprrel,
ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
                ktrans, ktrans, ktrans, ktrans,
                                lpop1 ,   NULL,
                                ktrans, ktrans,
// right hand
kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
ktrans, mouseb, mouseb, mouseb, ktrans, ktrans,
ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
mprrel, mprrel, mprrel, mprrel,
mprrel, ktrans,
ktrans, ktrans ),


	KB_MATRIX_LAYER(  // release: layer 2: keyboard functions
// unused
NULL,
// left hand
NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
                NULL,   NULL,   NULL,   NULL,
                                NULL,  lpop2,
                                NULL,   NULL,
// right hand
NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
NULL,   NULL,   NULL,   NULL,
NULL,   NULL,
NULL,   NULL ),
// ktrans, ktrans, kprrel ) };

// This following part causes problems for compiling
// Deleting some NULLS here probably shouldn't harm functionality since this seems to be
// some kind of gap-closer
	KB_MATRIX_LAYER(  // release: layer 3: nothing (just making sure unused
			  // functions don't get compiled out)
// unused
NULL,
// other
 kprrel, lpush8,  lpop8,   NULL,   NULL,   NULL,   NULL,
   ktog, lpush9,  lpop9,   NULL,   NULL,   NULL,   NULL,
 ktrans,lpush10, lpop10,   NULL,   NULL,   NULL,   NULL,
 lpush1,  lpop1,   NULL,   NULL,   NULL,   NULL,   NULL,
 lpush2,  lpop2, dbtldr,   NULL,   NULL,   NULL,   NULL,
 lpush3,  lpop3,   NULL,   NULL,   NULL,   NULL,   NULL,
 lpush4,  lpop4, s2kcap,   NULL,   NULL,   NULL,   NULL,
 lpush5,  lpop5,slpunum,   NULL,   NULL,   NULL,   NULL,
 lpush6,  lpop6,slponum,   NULL,   NULL,
 lpush7,  lpop7,   NULL )

};
