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
#     components/siwx917_soc/wifi_inc/
#     components/protocol/wifi/inc/
#     components/service/network_manager/inc/
#     ../gecko/common/inc/
#     ${ZEPHYR_BASE}/include/zephyr/portability

    # TODO: don't hardcode board!!
    components/si91x_support/brd4338a
)

zephyr_include_directories_ifdef(CONFIG_WIFI_SIWG917
    components/protocol/wifi/inc
    components/siwx917_soc/inc

    components/siwx917_soc/core/config
    components/siwx917_soc/wifi_inc
    components/service/network_manager/inc
    components/si91x/sl_net/inc
    components/si91x/socket_utility/inc
    ../gecko/platform/common/inc
    ../gecko/common/inc
    ${ZEPHYR_BASE}/include/zephyr/portability
)

zephyr_sources(
    components/siwx917_soc/core/chip/src/system_si91x.c
    components/siwx917_soc/drivers/ipmu/ipmu_apis.c
    components/siwx917_soc/drivers/ipmu/rsi_system_config_9117.c
    components/siwx917_soc/drivers/peripheral_drivers/src/rsi_egpio.c
    components/siwx917_soc/drivers/systemlevel/src/rsi_ipmu.c
    components/siwx917_soc/drivers/systemlevel/src/rsi_pll.c
    components/siwx917_soc/drivers/systemlevel/src/rsi_power_save.c
    components/siwx917_soc/drivers/systemlevel/src/rsi_ulpss_clk.c
    components/si91x_support/src/sl_utility.c
    components/si91x/memory/malloc_buffers.c
    components/si91x/platforms/siwx917_soc/siwx917_soc_ncp_host.c
    components/si91x/threading/sli_si91x_multithreaded.c
    components/si91x/src/sl_rsi_utility.c
    components/siwx917_soc/rsi_hal_mcu_m4_rom.c
#     components/siwx917_soc/sl_si91x_bus.c
#     components/siwx917_soc/sli_siwx917_soc.c
    components/siwx917_soc/sl_platform_wireless.c
    components/siwx917_soc/sl_platform.c
#     components/siwx917_soc/rsi_hal_mcu_m4_ram.c
    components/siwx917_soc/rsi_hal_mcu_m4_rom.c
    components/si91x/sl_net/protocols/icmp/sl_net_ping.c
)

zephyr_sources_ifdef(CONFIG_WIFI_SIWG917
    #components/siwx917_soc/boards/brd4325x/src/syscalls.c
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

zephyr_compile_definitions(
    # defines as provided by SimplicityStudio
    CHIP_917
    CHIP_917B0
    COMMON_FLASH_EN
    ENABLE_IPMU_APIS
    FLASH_BASED_EXECUTION_ENABLE
    ROM_BYPASS
    RSI_M4_INTERFACE
    SI917
    TA_DEEP_SLEEP_COMMON_FLASH
    SI917_RADIO_BOARD
    SI917_RADIO_BOARD_V2
    SL_BOARD_NAME="BRD4338A"
    SL_BOARD_REV="A00"
    RSI_WITH_OS
    SI91X_DEVICE
    #     SL_COMPONENT_CATALOG_PRESENT

    # this is needed to prevent error_t duplication
    __error_t_defined
    )

zephyr_compile_definitions_ifdef(CONFIG_WIFI_SIWG917
    SI91X_NETWORK_OFFLOAD_ENABLED
SL_NET_COMPONENT_INCLUDED
SL_WIFI_COMPONENT_INCLUDED
)
