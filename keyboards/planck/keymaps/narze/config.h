#pragma once

/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/
#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

#undef TAPPING_TERM
#define TAPPING_TERM 100

#define COMBO_TERM 20
#define COMBO_COUNT 1

#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD

#define SUPER_DUPER_SOUND S__NOTE(_B1)

#define MOUSEKEY_DELAY 100
