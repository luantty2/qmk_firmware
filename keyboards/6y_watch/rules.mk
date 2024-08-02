I2C_DRIVER_REQUIRED = yes
NO_USB_STARTUP_CHECK = yes
SRC += \
	ch455x.c \
	rtc.c \
	display.c \
	calendar.c \
	touch.c \
	vbus.c \
	lpm_stm32l43x.c \
	battery.c \
	max1704x.c \
	leds.c
