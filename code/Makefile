# Name of the application
APPLICATION = desk_light_automation

BOARD ?= native

RIOTBASE ?= $(CURDIR)/../../../RIOT

CFLAGS += -DEVELHELP

# Change this to 0 to show compiler invocation lines by default
QUIET ?= 1

WIFI_SSID ?= "your_wifi_name"
WIFI_PASS ?= "your_wifi_password"

DEFAULT_MQTT_CLIENT_ID ?= "broker"
DEFAULT_MQTT_USER ?= ""
DEFAULT_MQTT_PWD ?= ""

CFLAGS += -DDEFAULT_MQTT_CLIENT_ID=\"$(DEFAULT_MQTT_CLIENT_ID)\"
CFLAGS += -DDEFAULT_MQTT_USER=\"$(DEFAULT_MQTT_USER)\"
CFLAGS += -DDEFAULT_MQTT_PWD=\"$(DEFAULT_MQTT_PWD)\"

# Modules to include
USEMODULE += analog_util
USEMODULE += netdev_default
USEMODULE += periph_gpio
USEMODULE += periph_gpio_irq
USEMODULE += xtimer
USEMODULE += esp_wifi
USEMODULE += fmt
USEPKG += paho-mqtt

FEATURES_REQUIRED += periph_gpio periph_adc periph_i2c

# paho-mqtt depends on TCP support, choose the stack you want
LWIP_IPV4 ?= 0

ifneq (0,$(LWIP_IPV4))
  USEMODULE += ipv4_addr
  USEMODULE += lwip_arp
  USEMODULE += lwip_ipv4
  USEMODULE += lwip_dhcp_auto
  CFLAGS += -DETHARP_SUPPORT_STATIC_ENTRIES=1
  LWIP_IPV6 ?= 0
else
  LWIP_IPV6 ?= 1
endif

ifneq (0,$(LWIP_IPV6))
  USEMODULE += ipv6_addr
  USEMODULE += lwip_ipv6_autoconfig
endif

USEMODULE += lwip_netdev
USEMODULE += lwip

USEMODULE += sock_async_event
USEMODULE += sock_ip
USEMODULE += sock_udp
USEMODULE += sock_tcp

USEMODULE += ztimer

include $(RIOTBASE)/Makefile.include

ifneq (,$(filter arch_esp,$(FEATURES_USED)))
  CFLAGS += -DESP_WIFI_SSID=\"$(WIFI_SSID)\"
  CFLAGS += -DESP_WIFI_PASS=\"$(WIFI_PASS)\"
endif