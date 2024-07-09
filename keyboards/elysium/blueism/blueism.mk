ifeq ($(strip $(BLUETOOTH_ENABLE)$(BLUETOOTH_DRIVER)),yescustom)
     BLUEISM_DIR = blueism
     SRC += \
          $(BLUEISM_DIR)/blueism.c \
          $(BLUEISM_DIR)/wireless_sys.c \
          $(BLUEISM_DIR)/ringbuffer.c \
          $(BLUEISM_DIR)/max1704x.c \
          $(BLUEISM_DIR)/hid_leds.c \
          $(BLUEISM_DIR)/lpm_stm32l43x.c \
		  $(BLUEISM_DIR)/battery.c \

	 UART_DRIVER_REQUIRED = yes

    #  OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
	 NO_USB_STARTUP_CHECK = yes

     VPATH += $(TOP_DIR)/keyboards/elysium/$(BLUEISM_DIR)
endif
