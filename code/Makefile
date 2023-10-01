# name of the application
APPLICATION = desk_light_automation

BOARD ?= native

RIOTBASE ?= $(CURDIR)/../../../RIOT

CFLAG += -DEVELHELP

# change this to 0 show compiler invocation lines by default

QUIET ?= 1

WIFI_SSID ?= "wifi name"
WIFI_PASS ?= "wifi password"

ifneq(,$(DEFAULT_MQTT_CLIENT_ID))
  CFLAGS += -DDEFAULT_MQTT_CLIENT_ID=\"$(DEFAULT_MQTT_CLIENT_ID)\"
endif
ifneq(,$(DEFAULT_MQTT_USER))
  CFLAGS += -DDEFAULT_MQTT_USER=\"$(DEFAULT_MQTT_USER)\"
endif
ifneq (,$(DEFAULT_MQTT_PWD))
  CLAGS += -DDEFAULT_MQTT_PWD=\"$(DEFAULT_MQTT_PWD)\"
endif


# modules to include

USEMODULE += analog_uil
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