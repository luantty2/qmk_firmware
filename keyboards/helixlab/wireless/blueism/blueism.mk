ifeq ($(strip $(BLUETOOTH_ENABLE)$(BLUETOOTH_DRIVER)),yescustom)
     BLUEISM_DIR = blueism
     SRC += \
          $(BLUEISM_DIR)/blueism.c \
		  $(BLUEISM_DIR)/wireless_sys.c \
		  $(BLUEISM_DIR)/ringbuffer.c \

	QUANTUM_LIB_SRC += uart.c

    VPATH += $(TOP_DIR)/keyboards/helixlab/wireless/$(BLUEISM_DIR)
endif
