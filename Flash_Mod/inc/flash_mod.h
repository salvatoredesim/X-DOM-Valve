#ifndef _FLASH_MOD_H_
#define _FLASH_MOD_H_

#include "BlueNRG1_flash.h"
#include "valve_registers.h"
#include "osal.h"

/* Read a byte from flash memory */
uint8_t FLASH_MOD_ReadByte(uint32_t address);

/* Read a complete 4 byte word from flash memory */
uint32_t FLASH_MOD_ReadWord(uint32_t address);

/* Write a byte in flash memory */
void FLASH_MOD_WriteByte(uint32_t address, uint8_t byte_wr);

/* Write a burst of data */
void FLASH_MOD_WriteCharBurst(uint32_t start_address, char* data, uint16_t size);

void FLASH_MOD_WriteByteBurst(uint32_t start_address, uint8_t* data, uint16_t size);

#endif
