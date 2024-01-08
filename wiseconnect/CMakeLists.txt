# Copyright (c) 2023 Antmicro <www.antmicro.com>
#
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(
  components/si91x_support/inc
  components/siwx917_soc/drivers/cmsis_driver
  components/siwx917_soc/drivers/cmsis_driver/CMSIS/Driver/Include
  components/siwx917_soc/drivers/cmsis_driver/config
  components/siwx917_soc/drivers/peripheral_drivers/inc
  components/siwx917_soc/drivers/rom_driver/inc
  components/siwx917_soc/drivers/systemlevel/inc
  components/siwx917_soc/inc
  components/si91x/inc/
  components/si91x_support/inc
  ../gecko/common/inc

  # TODO: files from those dirs should be included only if WiFi is enabled,
  # but HAL code includes them uncoditionally
  components/protocol/wifi/inc
  components/service/network_manager/inc
  components/siwx917_soc/wifi_inc
  components/siwx917_soc/drivers/unified_api/inc
  components/siwx917_soc/drivers/unified_api/config

  # TODO: don't hardcode board!!
  components/si91x_support/brd4338a
)

zephyr_sources(
  components/siwx917_soc/core/chip/src/system_si91x.c
  components/siwx917_soc/drivers/ipmu/ipmu_apis.c
  components/siwx917_soc/drivers/ipmu/rsi_system_config_9117.c
  components/siwx917_soc/drivers/peripheral_drivers/src/rsi_egpio.c
  components/siwx917_soc/drivers/peripheral_drivers/src/rsi_gspi.c
  components/siwx917_soc/drivers/systemlevel/src/rsi_ipmu.c
  components/siwx917_soc/drivers/systemlevel/src/rsi_pll.c
  components/siwx917_soc/drivers/systemlevel/src/rsi_power_save.c
  components/siwx917_soc/drivers/systemlevel/src/rsi_ulpss_clk.c
  components/si91x/memory/malloc_buffers.c
  components/siwx917_soc/rsi_hal_mcu_m4_rom.c
  #components/si91x/platforms/siwx917_soc/siwx917_soc_ncp_host.c
  components/si91x_support/src/sl_utility.c
  #components/si91x/threading/sli_si91x_multithreaded.c
  components/si91x/src/sl_rsi_utility.c
  components/siwx917_soc/drivers/unified_api/src/sl_si91x_gspi.c
  components/siwx917_soc/drivers/cmsis_driver/GSPI.c
  components/siwx917_soc/drivers/cmsis_driver/UDMA.c
  components/siwx917_soc/drivers/peripheral_drivers/src/clock_update.c
  components/siwx917_soc/drivers/peripheral_drivers/src/rsi_udma_wrapper.c
  components/siwx917_soc/drivers/peripheral_drivers/src/rsi_udma.c
  components/siwx917_soc/sl_platform.c
  components/siwx917_soc/sl_platform_wireless.c
)

zephyr_compile_definitions(
  # defines as provided by SimplicityStudio
  CHIP_917
  CHIP_917B0
  COMMON_FLASH_EN
  ENABLE_IPMU_APIS
  RSI_M4_INTERFACE
  SI917
  SLI_SI917
  ROM_BYPASS
  GSPI_MULTI_SLAVE
  # this is needed to prevent error_t duplication
  __error_t_defined
)

zephyr_include_directories_ifdef(CONFIG_WIFI_SIWG917
  components/siwx917_soc/inc

  components/siwx917_soc/core/config
  components/si91x/sl_net/inc
  components/si91x/socket_utility/inc
  ../gecko/platform/common/inc
  ${ZEPHYR_BASE}/include/zephyr/portability
)

zephyr_sources_ifdef(CONFIG_WIFI_SIWG917
  components/siwx917_soc/sl_si91x_bus.c
  components/siwx917_soc/sli_siwx917_soc.c
  components/siwx917_soc/rsi_hal_mcu_m4_ram.c

  components/protocol/wifi/si91x/sl_wifi.c
  components/si91x/sl_net/src/sl_net_si91x_integration_handler.c
  components/si91x/src/sl_si91x_driver.c
  components/si91x/src/sl_si91x_callback_framework.c
  components/si91x/sl_net/src/sl_net_rsi_utility.c
  components/service/network_manager/src/sl_net.c
  components/si91x/sl_net/src/sl_si91x_net_internal_stack.c
  components/service/network_manager/src/sl_net_basic_profiles.c
  components/protocol/wifi/src/sl_wifi_callback_framework.c
  components/si91x/sl_net/src/sl_net_si91x.c
  components/service/network_manager/src/sl_net_basic_credentials.c
  components/si91x/socket/sl_si91x_socket.c
  components/si91x/socket_utility/src/sl_si91x_socket_utility.c
)

zephyr_compile_definitions_ifdef(CONFIG_WIFI_SIWG917
  SI91X_NETWORK_OFFLOAD_ENABLED
  SI91X_SOCKET_FEATURE
  SL_NET_COMPONENT_INCLUDED
  SL_WIFI_COMPONENT_INCLUDED
)

zephyr_include_directories_ifdef(CONFIG_BT_SIWG917
  components/siwx917_soc/wifi_inc
  components/si91x_support/brd4338a
  components/si91x/inc
  components/si91x/ble/inc
  components/protocol/wifi/inc
  components/service/network_manager/inc
  ../gecko/common/inc
  ${ZEPHYR_BASE}/include/zephyr/portability
)

zephyr_sources_ifdef(CONFIG_BT_SIWG917
  components/siwx917_soc/sl_si91x_bus.c
  components/siwx917_soc/sli_siwx917_soc.c
  components/siwx917_soc/rsi_hal_mcu_m4_ram.c
  components/si91x/ble/src/rsi_ble_gap_apis.c
  components/si91x/ble/src/rsi_bt_ble.c
  components/si91x/ble/src/rsi_bt_common_apis.c
  components/si91x/ble/src/rsi_common_apis.c
  components/si91x/ble/src/rsi_utils.c
  components/si91x/src/sl_si91x_driver.c
  components/protocol/wifi/si91x/sl_wifi.c
  )

zephyr_compile_definitions_ifdef(CONFIG_BT_SIWG917
  SL_WIFI_COMPONENT_INCLUDED
  BLE_ENABLE
  RSI_LITTLE_ENDIAN
# Only for testing purposes, to be deleted
  RSI_DEBUG_PRINTS
)
