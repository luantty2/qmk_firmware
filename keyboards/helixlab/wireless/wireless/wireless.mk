ifeq ($(strip $(BLUETOOTH_ENABLE)$(BLUETOOTH_DRIVER)),yescustom)
     WIRELESS_DIR = wireless
     SRC += \
          $(WIRELESS_DIR)/bk3632_spi.c \
		  $(WIRELESS_DIR)/wireless.c \

     VPATH += $(TOP_DIR)/keyboards/helixlab/wireless/$(WIRELESS_DIR)
endif
