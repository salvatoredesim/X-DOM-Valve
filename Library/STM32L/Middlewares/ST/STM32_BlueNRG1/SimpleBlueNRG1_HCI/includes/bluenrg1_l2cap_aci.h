#ifndef __BLUENRG1_L2CAP_ACI_H__
#define __BLUENRG1_L2CAP_ACI_H__


/**
  ******************************************************************************
  * @file    bluenrg1_l2cap_aci.h
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
  * @brief Send an L2CAP connection parameter update request from the slave to the master.
An @ref aci_l2cap_connection_update_resp_event event will be raised when the master will respond to the 
request (accepts or rejects).
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Conn_Interval_Min N = 0xXXXX    Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Interval_Max N = 0xXXXX    Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Slave_latency Slave latency for the connection in number of connection events.
Range: 0x0000 to 0x01F3
  * @param Timeout_Multiplier Defines connection timeout parameter in the following manner: Timeout Multiplier * 10ms.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_l2cap_connection_parameter_update_req(uint16_t Connection_Handle,
                                                     uint16_t Conn_Interval_Min,
                                                     uint16_t Conn_Interval_Max,
                                                     uint16_t Slave_latency,
                                                     uint16_t Timeout_Multiplier);
/**
  * @brief Accept or reject a connection update. This command should be sent in response
to a @ref aci_l2cap_connection_update_req_event event from the controller. The accept parameter has to be
set if the connection parameters given in the event are acceptable.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Conn_Interval_Min N = 0xXXXX    Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Interval_Max N = 0xXXXX    Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Slave_latency Slave latency for the connection in number of connection events.
Range: 0x0000 to 0x01F3
  * @param Timeout_Multiplier Defines connection timeout parameter in the following manner: Timeout Multiplier * 10ms.
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @param Identifier Identifier received in ACI_L2CAP_Connection_Update_Req event.
  * @param Accept 0x00: The connection update parameters are not acceptable.
0x01: The connection update parameters are acceptable.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_l2cap_connection_parameter_update_resp(uint16_t Connection_Handle,
                                                      uint16_t Conn_Interval_Min,
                                                      uint16_t Conn_Interval_Max,
                                                      uint16_t Slave_latency,
                                                      uint16_t Timeout_Multiplier,
                                                      uint16_t Minimum_CE_Length,
                                                      uint16_t Maximum_CE_Length,
                                                      uint8_t Identifier,
                                                      uint8_t Accept);
/**
     * @}
     */
    #endif /* __BLUENRG1_L2CAP_ACI_H__*/
