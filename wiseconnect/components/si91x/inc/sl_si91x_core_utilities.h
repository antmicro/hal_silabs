/***************************************************************************/ /**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#pragma once
#include "sl_si91x_types.h"
#include "sl_wifi_device.h"
#include "sl_additional_status.h"

static sl_status_t saved_si91x_firmware_status = 0;

/******************************************************************************
 * A utility function to extract firmware status from RX packet.
 * The extracted firmware status can be given to convert_firmware_status() to get sl_status equivalent.
 * @param packet packet that contains the frame status which needs to be extracted.
 * @return  frame status
 *****************************************************************************/
static inline uint16_t get_si91x_frame_status(sl_si91x_packet_t *packet)
{
  return (uint16_t)(packet->desc[12] + (packet->desc[13] << 8));
}

/******************************************************************************
 * @brief
 *   A utility function that converts frame status sent by firmware to sl_status_t
 * @param[in] si91x_firmware_status
 *   si91x_firmware_status that needs to be converted to sl_status_t.
 * @return
 *   sl_status_t. See https://docs.silabs.com/gecko-platform/4.1/common/api/group-status for details.
 *****************************************************************************/
static inline sl_status_t convert_firmware_status(uint16_t si91x_firmware_status)
{
  if (si91x_firmware_status == SL_STATUS_OK) {
    return si91x_firmware_status;
  } else {
    // Setting 16th bit to indicate si91x firmware status
    saved_si91x_firmware_status = (si91x_firmware_status | BIT(16));
    return saved_si91x_firmware_status;
  }
}

/******************************************************************************
 * @brief 
 *   Get the saved firmware status value.
 * @return
 *   sl_status_t. See https://docs.silabs.com/gecko-platform/4.1/common/api/group-status for details.
 *****************************************************************************/
static inline sl_status_t get_saved_firmware_status(void)
{
  return saved_si91x_firmware_status;
}

/******************************************************************************
 * @brief
 *   A utility function that converts si91x_status_t to sl_status_t
 * @param[in] si91x_status
 *   si91x_status that needs to be converted to sl_status_t.
 * @return
 *   sl_status_t. See https://docs.silabs.com/gecko-platform/4.1/common/api/group-status for details.
 *****************************************************************************/
static inline sl_status_t convert_si91x_status_to_sl_status(si91x_status_t si91x_status)
{
  switch (si91x_status) {
    case RSI_ERROR_NONE:
      return SL_STATUS_OK;
    case RSI_ERROR_TIMEOUT:
      return SL_STATUS_TIMEOUT;
    case RSI_ERROR_INVALID_PARAM:
      return SL_STATUS_INVALID_PARAMETER;
    case RSI_ERROR_COMMAND_GIVEN_IN_WRONG_STATE:
      return SL_STATUS_INVALID_STATE;
    case RSI_ERROR_PKT_ALLOCATION_FAILURE:
      return SL_STATUS_ALLOCATION_FAILED;
    case RSI_ERROR_COMMAND_NOT_SUPPORTED:
      return SL_STATUS_NOT_SUPPORTED;
    case RSI_ERROR_INSUFFICIENT_BUFFER:
      return SL_STATUS_NO_MORE_RESOURCE;
    case RSI_ERROR_IN_OS_OPERATION:
      return SL_STATUS_OS_OPERATION_FAILURE;
    case RSI_ERROR_BOOTUP_OPTIONS_NOT_SAVED:
      return SL_STATUS_BOOTUP_OPTIONS_NOT_SAVED;
    case RSI_ERROR_BOOTLOADER_VERSION_NOT_MATCHING:
      return SL_STATUS_BOOTLOADER_VERSION_MISMATCH;
    case RSI_ERROR_WAITING_FOR_BOARD_READY:
      return SL_STATUS_WAITING_FOR_BOARD_READY;
    case RSI_ERROR_VALID_FIRMWARE_NOT_PRESENT:
      return SL_STATUS_VALID_FIRMWARE_NOT_PRESENT;
    case RSI_ERROR_INVALID_OPTION:
      return SL_STATUS_INVALID_OPTION;
    case RSI_ERROR_SPI_BUSY:
      return SL_STATUS_SPI_BUSY;
    case RSI_ERROR_CARD_READY_TIMEOUT:
      return SL_STATUS_CARD_READY_TIMEOUT;
    case RSI_ERROR_FW_LOAD_OR_UPGRADE_TIMEOUT:
      return SL_STATUS_FW_LOAD_OR_UPGRADE_TIMEOUT;
    default:
      return SL_STATUS_FAIL;
  }
}
