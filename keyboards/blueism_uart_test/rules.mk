BLUETOOTH_ENABLE = yes
BLUETOOTH_DRIVER = custom
UART_DRIVER_REQUIRED = yes
# NO_USB_STARTUP_CHECK = yes

SRC += \
    blueism_uart.c \
    blueism_keycodes.c
