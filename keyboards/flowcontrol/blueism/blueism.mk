ifeq ($(strip $(BLUETOOTH_ENABLE)$(BLUETOOTH_DRIVER)),yescustom)
     BLUEISM_DIR = blueism
     SRC += \
          $(BLUEISM_DIR)/blueism.c \
          $(BLUEISM_DIR)/wireless_sys.c \
          $(BLUEISM_DIR)/ringbuffer.c \

	 UART_DRIVER_REQUIRED = yes

    #  OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
	 NO_USB_STARTUP_CHECK = yes

     VPATH += $(TOP_DIR)/keyboards/flowcontrol/$(BLUEISM_DIR)
endif
