deps_config := \
	/home/rso16/esp/esp-idf/components/app_trace/Kconfig \
	/home/rso16/esp/esp-idf/components/aws_iot/Kconfig \
	/home/rso16/esp/esp-idf/components/bt/Kconfig \
	/home/rso16/esp/esp-idf/components/driver/Kconfig \
	/home/rso16/esp/esp-idf/components/esp32/Kconfig \
	/home/rso16/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/rso16/esp/esp-idf/components/esp_event/Kconfig \
	/home/rso16/esp/esp-idf/components/esp_http_client/Kconfig \
	/home/rso16/esp/esp-idf/components/esp_http_server/Kconfig \
	/home/rso16/esp/esp-idf/components/ethernet/Kconfig \
	/home/rso16/esp/esp-idf/components/fatfs/Kconfig \
	/home/rso16/esp/esp-idf/components/freemodbus/Kconfig \
	/home/rso16/esp/esp-idf/components/freertos/Kconfig \
	/home/rso16/esp/esp-idf/components/heap/Kconfig \
	/home/rso16/esp/esp-idf/components/libsodium/Kconfig \
	/home/rso16/esp/esp-idf/components/log/Kconfig \
	/home/rso16/esp/esp-idf/components/lwip/Kconfig \
	/home/rso16/esp/esp-idf/components/mbedtls/Kconfig \
	/home/rso16/esp/esp-idf/components/mdns/Kconfig \
	/home/rso16/esp/esp-idf/components/mqtt/Kconfig \
	/home/rso16/esp/esp-idf/components/nvs_flash/Kconfig \
	/home/rso16/esp/esp-idf/components/openssl/Kconfig \
	/home/rso16/esp/esp-idf/components/pthread/Kconfig \
	/home/rso16/esp/esp-idf/components/spi_flash/Kconfig \
	/home/rso16/esp/esp-idf/components/spiffs/Kconfig \
	/home/rso16/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/rso16/esp/esp-idf/components/unity/Kconfig \
	/home/rso16/esp/esp-idf/components/vfs/Kconfig \
	/home/rso16/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/rso16/esp/esp-idf/components/app_update/Kconfig.projbuild \
	/home/rso16/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/rso16/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/rso16/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/rso16/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(IDF_TARGET)" "esp32"
include/config/auto.conf: FORCE
endif
ifneq "$(IDF_CMAKE)" "n"
include/config/auto.conf: FORCE
endif

$(deps_config): ;
