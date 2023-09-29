# name of the application
APPLICATION = smart_desk_light

BOARD ?= native

RIOTBASE ?= $(CURDIR)/../../../RIOT

CFLAG += -DEVELHELP

# change this to 0 show compiler invocation lines by default

QUIET ?= 1

# modules to include

USEMODULE += srf04
USEMODULE += rgbled
USEMODULE += periph_gpio
USEMODULE += periph_gpio_irq
USEMODULE += xtimer


FEATURES_REQUIRED = periph_gpio
FEATURES_REQUIRED = periph_adc


include $(RIOTBASE)/Makefile.include
