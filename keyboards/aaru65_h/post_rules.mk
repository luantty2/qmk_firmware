ifeq ($(strip $(FADER_ENABLE)$(MIDI_ENABLE)),yesyes)
	OPT_DEFS += -DFADER_ENABLE
	SRC += \
		ms1100.c \
		fader.c
endif

ifeq ($(strip $(RGB_MATRIX_ENABLE)),yes)
	SRC += \
		rgb_matrix_effects_custom.c
endif

SRC += debug_custom.c