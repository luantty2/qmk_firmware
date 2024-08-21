ifeq ($(strip $(FADER_ENABLE)$(MIDI_ENABLE)),yesyes)
	OPT_DEFS += -DFADER_ENABLE
	SRC += \
		ads1100.c \
		fader.c
endif

ifeq ($(strip $(GELIX_ENABLE)),yes)
	OPT_DEFS += -DGELIX_ENABLE
	SRC += \
	      gelix.c
endif
