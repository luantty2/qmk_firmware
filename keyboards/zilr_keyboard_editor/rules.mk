ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes
QUANTUM_LIB_SRC += \
				i2c_master.c \
				color.c

DFU_SUFFIX_ARGS = -p FFFF -v FFFF