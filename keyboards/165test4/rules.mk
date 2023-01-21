# This file intentionally left blank
CUSTOM_MATRIX = lite
QUANTUM_LIB_SRC+= spi_master.c
# BOARD = BLACKPILL_STM32_F411
DEBOUNCE_TYPE = sym_eager_pk

EEPROM_DRIVER = transient

    # MCU_LDSCRIPT = STM32F103xC
    # # FIRMWARE_FORMAT = uf2
    # # UF2_FAMILY = STM32F1
    # BOARD=at32f403


# MCU_FAMILY = STM32
# MCU_SERIES = STM32F1xx

# # Linker script to use
# # - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
# #   or <this_dir>/ld/
# MCU_LDSCRIPT = STM32F103xC_tinyuf2

# # Startup code to use
# #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
# MCU_STARTUP = stm32f1xx

# # Board: it should exist either in <chibios>/os/hal/boards/
# #  or <this_dir>/boards
# BOARD = at32f403

# # Cortex version
# MCU  = cortex-m4

# # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
# ARMV = 7

  # Cortex version
  MCU = cortex-m4

  # ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
  ARMV = 7

  ## chip/board settings
  # - the next two should match the directories in
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
  #   OR
  #   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
  MCU_FAMILY = STM32
  MCU_SERIES = STM32F1xx

  # Linker script to use
  # - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
  #   or <keyboard_dir>/ld/
  MCU_LDSCRIPT = STM32F103xC

  # Startup code to use
  #  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
  MCU_STARTUP = stm32f1xx

  # Board: it should exist either in <chibios>/os/hal/boards/,
  # <keyboard_dir>/boards/, or drivers/boards/
  BOARD ?= at32f403

  USE_FPU ?= no

  STM32_BOOTLOADER_ADDRESS ?= 0x1FFFB000
