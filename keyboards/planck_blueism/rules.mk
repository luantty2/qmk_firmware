BLUETOOTH_ENABLE = yes
BLUETOOTH_DRIVER = custom
NO_USB_STARTUP_CHECK = no
# CUSTOM_MATRIX = lite

OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
# SRC += \
# 	matrix.c \

include keyboards/planck_blueism/blueism/blueism.mk
