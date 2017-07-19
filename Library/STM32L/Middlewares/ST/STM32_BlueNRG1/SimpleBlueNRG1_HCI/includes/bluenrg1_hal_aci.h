#ifndef __BLUENRG1_HAL_ACI_H__
#define __BLUENRG1_HAL_ACI_H__


/**
  ******************************************************************************
  * @file    bluenrg1_hal_aci.h
  * @author  AMS - VMA RF Application team
  * @version V1.0.0
  * @date    21-Sept-2015
  * @brief   Header file for BlueNRG-1 Bluetooth Low Energy stack APIs
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  ******************************************************************************
  */
#include "bluenrg1_types.h"
/**
  * @brief This command writes a value to a low level configure data structure. It is useful to setup
directly some low level parameters for the system in the runtime.
  * @param Offset Offset of the element in the configuration data structure
which has to be written. The valid offsets are:

- 0x00: Bluetooth public address, Value length to be writtten: 6 bytes
- 0x06: DIV used to derive CSRK, Value length to be written: 2 bytes
- 0x08: Encryption root key used to derive LTK and CSRK, Value length to be written: 16 bytes
- 0x18: Identity root key used to derive LTK and CSRK, Value length to be written: 16 bytes
- 0x2C: Link layer without host (for certification purposes), Value length to be written: 1 byte   

- 0x2F: Disable watchdog (1=disable, 0=enable). Value length to be written: 1 byte
  * @param Length Length of data to be written
  * @param Value Data to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_write_config_data(uint8_t Offset,
                                     uint8_t Length,
                                     uint8_t Value[]);
/**
  * @brief This command requests the value in the low level configure data structure.
The number of read bytes changes for different Offset. 
  * @param Offset Offset of the element in the configuration data structure
which has to be read. The valid offsets are:

* 0x00: Bluetooth public address, Value length returned: 6 bytes
* 0x06: DIV used to derive CSRK, Value length returned: 2 bytes
* 0x08: Encryption root key used to derive LTK and CSRK, Value length returned: 16 bytes
* 0x18: Identity root key used to derive LTK and CSRK, Value length returned: 16 bytes
* 0x2C: Link layer without host (for certification purposes), Value length returned: 1 byte

* 0x2F: Disable watchdog (1=disabled, 0=enablee). Value length returned: 1 byte
* 0x80: Static random address. Value length returned: 6 bytes (read-only)
  * @param[out] Data_Length Length of Data in octets
  * @param[out] Data Data field associated with Offset parameter
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_read_config_data(uint8_t Offset,
                                    uint8_t *Data_Length,
                                    uint8_t Data[]);
/**
  * @brief This command sets the TX power level of the device. By controlling the
EN_HIGH_POWER and the PA_LEVEL, the combination of the 2 determines the output
power level (dBm). 
When the system starts up or reboots, the default TX power level will be used, which is the
maximum value of 8 dBm. Once this command is given, the output power will be changed
instantly, regardless if there is Bluetooth communication going on or not. For example, for
debugging purpose, the device can be set to advertise all the time. And use this
command to observe the signal strength changing.
The system will keep the last received TX power level from the command, i.e. the 2nd
command overwrites the previous TX power level. The new TX power level remains until
another Set TX Power command, or the system reboots.
  * @param En_High_Power Enable High Power mode
  * @param PA_Level PA Level.
If En_High_Power=0 
0 = -18 dBm,
1 = -15 dBm,
2 = -12 dBm,
3 = -9 dBm,
4 = -6 dBm,
5 = -2 dBm,
6 =  0 dBm,
7 =  5 dBm.
If En_High_Power=1 
0 = -14 dBm,
1 = -11 dBm,
2 = -8 dBm,
3 = -5 dBm,
4 = -2 dBm,
5 =  2 dBm,
6 =  4 dBm,
7 =  8 dBm
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_set_tx_power_level(uint8_t En_High_Power,
                                      uint8_t PA_Level);
/**
  * @brief Put the device in standby mode.
Normally the BlueNRG will automatically enter sleep mode to save power. This command puts the 
device into the Standby mode instead of the sleep mode. The difference is that, in sleep mode, 
the device can still wake up itself with the internal timer. But in standby mode, this timer is 
disabled. So the only possibility to wake up the device is by external signals, e.g. a HCI command 
sent via SPI bus. 
Based on the measurement, the current consumption under sleep mode is ~2 uA. And this
value is ~1.5 uA in standby mode.
The command is only accepted when there is no other Bluetooth activity. 
Otherwise an error code ERR_COMMAND_DISALLOWED will be returned.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_device_standby(void);
/**
  * @brief This command returns the number of packets sent in Direct Test Mode.
When the Direct TX test is started, a 32-bit counter is used to count how many packets have been transmitted. 
This command can be used to check how many packets have been sent during the Direct TX test.
The counter starts from 0 and counts upwards. The counter can wrap and start from 0 again. 
The counter is not cleared until the next Direct TX test starts. 
  * @param[out] Number_Of_Packets Number of packets sent during the last Direct TX test.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_le_tx_test_packet_number(uint32_t *Number_Of_Packets);
/**
  * @brief This command starts a carrier frequency, i.e. a tone, on a specific channel. The frequency
sine wave at the specific channel may be used for debugging purpose only. The channel ID
is a parameter from 0x00 to 0x27 for the 40 BLE channels, e.g. 0x00 for 2.402 GHz, 0x01
for 2.404 GHz etc.
This command should not be used when normal Bluetooth activities are ongoing.
The tone should be stopped by @ref aci_hal_tone_stop command.
  * @param RF_Channel BLE Channel ID, from 0x00 to 0x27 meaning (2.402 + 2*0xXX) GHz
Device will continuously emit 0s, that means that the tone
will be at the channel center frequency less the maximum
frequency deviation (250kHz).
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_tone_start(uint8_t RF_Channel);
/**
  * @brief This command is used to stop the previously started @ref aci_hal_tone_start command.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_tone_stop(void);
/**
  * @brief This command is only implemented together with the normal application. The updater does
not support this command. If this command is called, the system reboots and enters updater
mode.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_updater_start(void);
/**
  * @brief This command reboots the system. This command does not set the BLUE flag, which must
be done by another command.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_updater_reboot(void);
/**
  * @brief This command returns the version of the Updater.
  * @param[out] Version Not available
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_get_updater_version(uint8_t *Version);
/**
  * @brief Return the maximum buffer size. This value limits the size of the data blocks that could be
used on the command @ref aci_hal_updater_prog_data_blk.
  * @param[out] Buffer_Size Not available
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_get_updater_bufsize(uint8_t *Buffer_Size);
/**
  * @brief This command erases the BLUE flag in the Flash. After this operation, the updater cannot
jump to the firmware until the BLUE flag is set to a valid value with ACI_HAL_UPDATER_RESET_BLUE_FLAG.
This command is strongly recommended when the updater wants to upgrade the firmware
application.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_updater_erase_blue_flag(void);
/**
  * @brief Reset the BLUE flag to its proper value. This command must be called when the firmware
upgrade is finished. So that after reboot, the update may jump to the firmware application.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_updater_reset_blue_flag(void);
/**
  * @brief This command erases one sector of the Flash memory. One sector is 2 KB. After erasing,
the sector will be all 0xFF.
  * @param Address Not available
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_updater_erase_sector(uint32_t Address);
/**
  * @brief This command writes a block of data to the Flash, starting from the given base address.
  * @param Address Not available
  * @param Data_Length Length of Data in octets
  * @param Data Not available
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_updater_prog_data_blk(uint32_t Address,
                                         uint16_t Data_Length,
                                         uint8_t Data[]);
/**
  * @brief This command reads a block of data from the Flash, starting from the given base address.
For it is only allowed to read from the IFR flash. So the Base Address must be bigger than 0x10020000.
  * @param Address Not available
  * @param Data_Length Not available
  * @param[out] Data Not available
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_updater_read_data_blk(uint32_t Address,
                                         uint16_t Data_Length,
                                         uint8_t Data[]);
/**
  * @brief It calculates the CRC32 of one or more Flash sectors. One Flash sector is 2 KB
  * @param Address Not available
  * @param Num_Of_Sectors Not available
  * @param[out] crc Not available
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_updater_calc_crc(uint32_t Address,
                                    uint8_t Num_Of_Sectors,
                                    uint32_t *crc);
/**
  * @brief TBD
  * @param[out] HW_Version Not available
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_updater_hw_version(uint8_t *HW_Version);
/**
  * @brief This command set the bitmask associated to @ref aci_hal_end_of_radio_activity_event. Only the radio acitivities enabled in the mask
will be reported to application by @ref aci_hal_end_of_radio_activity_event
  * @param Radio_Activity_Mask Bitmask of radio events
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_set_radio_activity_mask(uint16_t Radio_Activity_Mask);
/**
  * @brief This command returns the status of the 8 Bluetooth low energy links managed by the device
  * @param[out] Link_Status Array of link status (8 links). Each link status is 1 byte.
0x00:Idle,
0x01:Advertising,
0x02:Connected in slave role,
0x03:Scanning,
0x04:Reserved,
0x05:Connected in master role,
0x06:TX test mode,
0x07:RX test mode
  * @param[out] Link_Connection_Handle Array of connection handles (2 bytes) for 8 links.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_get_link_status(uint8_t Link_Status[8],
                                   uint16_t Link_Connection_Handle[16 / 2]);
/**
  * @brief This command returns the build number associated with the firmware version currently running
  * @param[out] Build_Number Build number of the firmware.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_get_fw_build_number(uint16_t *Build_Number);
/**
  * @brief This command returns information about the Anchor Period to help application in selecting 
                      slot timings when operating in multi-link scenarios.
  * @param[out] Anchor_Period Current anchor period.
T = N * 0.625 ms.
  * @param[out] Max_Free_Slot Maximum available time that can be allocated for a new slot.
T = N * 0.625 ms.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_get_anchor_period(uint32_t *Anchor_Period,
                                     uint32_t *Max_Free_Slot);
/**
     * @}
     */
    #endif /* __BLUENRG1_HAL_ACI_H__*/
