/*
 * Copyright (c) 2022 Antmicro <www.antmicro.com>
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#include <sl_bt_ll_zephyr.h>

K_SEM_DEFINE(slz_ll_sem, 0, 1);

static atomic_t sli_btctrl_events;

bool sli_pending_btctrl_events(void)
{
	return false;
}

void BTLE_LL_EventRaise(uint32_t events)
{
	atomic_or(&sli_btctrl_events, events);
	k_sem_give(&slz_ll_sem);
}

void slz_ll_thread_func(void)
{
	while (true) {
		k_sem_take(&slz_ll_sem, K_FOREVER);
		uint32_t events = atomic_clear(&sli_btctrl_events);
		BTLE_LL_Process(events);
	}
}

void sl_bt_controller_init()
{
	/* No extra initialization procedure required */
}

uint32_t hci_common_transport_transmit(uint8_t *data, int16_t len)
{
	struct net_buf * buf;

	switch (data[0]) {
		case h4_event:
			uint8_t evt = data[1];
			buf = bt_buf_get_evt(evt, false, K_FOREVER);
			net_buf_add_mem(buf, data + 1, len - 1);
			uint8_t flags = bt_hci_evt_get_flags(evt);

			if (flags & BT_HCI_EVT_FLAG_RECV_PRIO) {
				bt_recv_prio(buf);
			} else {
				bt_recv(buf);
			}

			break;
		case h4_acl:
			buf = bt_buf_get_rx(BT_BUF_ACL_IN, K_FOREVER);
			net_buf_add_mem(buf, data + 1, len - 1);
			bt_recv(buf);
			break;
		default:
			break;
	}

	sl_btctrl_hci_transmit_complete(0);
	return 0;
}
