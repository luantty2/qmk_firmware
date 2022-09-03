# This file intentionally left blank
# RGBLIGHT_ENABLE = yes
# WS2812_DRIVER = spi

ENCODER_ENABLE = yes
EEPROM_DRIVER = spi
QUANTUM_LIB_SRC += \
				i2c_master.c \
				color.c

DFU_SUFFIX_ARGS = -p FFFF -v FFFF