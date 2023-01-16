

BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
NKRO_ENABLE = yes           # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
BACKLIGHT_DRIVER = software
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
AUDIO_ENABLE = yes

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

COMBO_ENABLE = yes

# Fix unresponsive planck after some time
NO_SUSPEND_POWER_DOWN = yes

ifeq ($(strip $(KEYBOARD)), planck/light)
	# Don't redefine for Planck Light
else
	NO_USB_STARTUP_CHECK = yes
endif


ifeq ($(strip $(KEYBOARD)), planck/rev4)
	MOUSEKEY_ENABLE = no
	MIDI_ENABLE = no
	COMMAND_ENABLE = no
else
	MOUSEKEY_ENABLE = yes
	MIDI_ENABLE = yes
	COMMAND_ENABLE = yes
endif
