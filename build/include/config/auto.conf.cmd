deps_config := \
	/home/gennady/esp/esp-idf/components/app_trace/Kconfig \
	/home/gennady/esp/esp-idf/components/aws_iot/Kconfig \
	/home/gennady/esp/esp-idf/components/bt/Kconfig \
	/home/gennady/esp/esp-idf/components/driver/Kconfig \
	/home/gennady/esp/esp-idf/components/esp32/Kconfig \
	/home/gennady/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/gennady/esp/esp-idf/components/esp_http_client/Kconfig \
	/home/gennady/esp/esp-idf/components/ethernet/Kconfig \
	/home/gennady/esp/esp-idf/components/fatfs/Kconfig \
	/home/gennady/esp/esp-idf/components/freertos/Kconfig \
	/home/gennady/esp/esp-idf/components/heap/Kconfig \
	/home/gennady/esp/esp-idf/components/libsodium/Kconfig \
	/home/gennady/esp/esp-idf/components/log/Kconfig \
	/home/gennady/esp/esp-idf/components/lwip/Kconfig \
	/home/gennady/esp/esp-idf/components/mbedtls/Kconfig \
	/home/gennady/esp/esp-idf/components/nvs_flash/Kconfig \
	/home/gennady/esp/esp-idf/components/openssl/Kconfig \
	/home/gennady/esp/esp-idf/components/pthread/Kconfig \
	/home/gennady/esp/esp-idf/components/spi_flash/Kconfig \
	/home/gennady/esp/esp-idf/components/spiffs/Kconfig \
	/home/gennady/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/gennady/esp/esp-idf/components/vfs/Kconfig \
	/home/gennady/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/gennady/esp/esp32-exonum/components/arduino/Kconfig.projbuild \
	/home/gennady/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/gennady/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/gennady/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/gennady/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(IDF_CMAKE)" "n"
include/config/auto.conf: FORCE
endif

$(deps_config): ;
