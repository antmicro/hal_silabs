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

    # this is needed to prevent error_t duplication
    __error_t_defined
)
