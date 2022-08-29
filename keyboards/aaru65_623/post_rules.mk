ifeq ($(strip $(FADER_ENABLE)$(MIDI_ENABLE)),yesyes)
	OPT_DEFS += -DFADER_ENABLE
	SRC += \
		ms1100.c \
		fader.c
endif

ifeq ($(strip $(RGB_INDICATOR_ENABLE)),yes)
	CIE1931_CURVE = yes
	OPT_DEFS += -DRGB_INDICATOR_ENABLE
	SRC += \
		aw2023.c \
		rgb_indicator.c
endif

SRC += debug_custom.c