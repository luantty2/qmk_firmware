ifeq ($(strip $(BLUETOOTH_ENABLE)$(BLUETOOTH_DRIVER)),yescustom)
     WIRELESS_DIR = wireless
     SRC += \
          $(WIRELESS_DIR)/bk3632_spi.c \
		  $(WIRELESS_DIR)/tri_mode_sys.c \

	QUANTUM_LIB_SRC += spi_master.c

     VPATH += $(TOP_DIR)/keyboards/helixlab/beken_wireless/$(WIRELESS_DIR)
endif
