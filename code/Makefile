# Name of the application
APPLICATION = desk_light_automation

BOARD ?= native

RIOTBASE ?= $(CURDIR)/../../../RIOT

CFLAGS += -DEVELHELP

# Change this to 0 to show compiler invocation lines by default
QUIET ?= 1

WIFI_SSID ?= "TIM-26374786"
WIFI_PASS ?= "C7AkkbPh2NH9X7mCTAap2Y2Y"

# Use := instead of ?= for consistency
DEFAULT_MQTT_CLIENT_ID ?= "client_id"
DEFAULT_MQTT_USER ?= "username"
DEFAULT_MQTT_PWD ?= "password"

CFLAGS += -DDEFAULT_MQTT_CLIENT_ID=\"$(DEFAULT_MQTT_CLIENT_ID)\"
CFLAGS += -DDEFAULT_MQTT_USER=\"$(DEFAULT_MQTT_USER)\"
CFLAGS += -DDEFAULT_MQTT_PWD=\"$(DEFAULT_MQTT_PWD)\"

# Modules to include
USEMODULE += analog_util
USEMODULE += netdev_default
USEMODULE += srf04
USEMODULE += rgbled
USEMODULE += periph_gpio
USEMODULE += periph_gpio_irq
USEMODULE += xtimer

USEMODULE += fmt
USEPKG += paho-mqtt

FEATURES_REQUIRED += periph_gpio periph_adc periph_i2c

include Makefile.lwip

USEMODULE += sock_async_event
USEMODULE += sock_ip
USEMODULE += sock_udp
USEMODULE += sock_tcp

USEMODULE += ztimer

include $(RIOTBASE)/Makefile.include

ifneq (,$(filter arch_esp,$(FEATURES_USED)))
  CFLAGS += -DWIFI_SSID=\"$(WIFI_SSID)\"
  CFLAGS += -DWIFI_PASS=\"$(WIFI_PASS)\"
endif