# This file intentionally left blank
CUSTOM_MATRIX = lite
# QUANTUM_LIB_SRC+= spi_master.c
BOARD = BLACKPILL_STM32_F411
DEBOUNCE_TYPE = asym_eager_defer_pk

VPATH += drivers/gpio
SRC += sn74x165.c spi_master.c