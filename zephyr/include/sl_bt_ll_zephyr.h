/*
 * Copyright (c) 2022 Antmicro <www.antmicro.com>
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <stdbool.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/bluetooth/hci_driver.h>
#include <sl_hci_common_transport.h>

enum h4_packet {
	h4_command = 1,
	h4_acl     = 2,
	h4_sco     = 3,
	h4_event   = 4
};

void BTLE_LL_Process(uint32_t events);
void BTLE_LL_EventRaise(uint32_t events);
bool sli_pending_btctrl_events(void);
void slz_ll_thread_func(void);
uint32_t hci_common_transport_transmit(uint8_t *data, int16_t len);
