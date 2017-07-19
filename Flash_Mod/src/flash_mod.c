#include "flash_mod.h"

#ifndef DEBUG
#define DEBUG 1
#endif

#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif


const uint32_t memory_size = (MAX_ROLE_SIZE + (ADDRESS_ROLE - ADDRESS_START_CFG_MEMORY));
uint8_t old_memory[memory_size];

void FLASH_MOD_Read_Conf_Memory_Area(){
	
	/* Erase the temp memory */
	Osal_MemSet(old_memory,0x00,memory_size);
	
	uint16_t i = 0;
	uint32_t start_address = ADDRESS_START_CFG_MEMORY;
	
	/* Start copying data */
	while(i < memory_size){
				old_memory[i] = FLASH_MOD_ReadByte(start_address+i);
				i++;
	}
}

/* TODO: To implement for code compressions */
void FLASH_MOD_ProgramWord(uint32_t address, uint32_t data){
			
}

void FLASH_MOD_Rewrite_Memory(){
	
				/* Calculating bytes to write in 32 bit form */
				uint32_t start_address = ADDRESS_START_CFG_MEMORY;
				uint16_t size_words = memory_size / 4;
				uint8_t spare_words = memory_size % 4;
	
				/* Rewriting data in 4-byte words */
				uint16_t i = 0;
				uint32_t wr_word;
				while(i < size_words){
						wr_word = 0x00000000;
						uint8_t byte1 = old_memory[(i*4)];
						uint8_t byte2 = old_memory[(i*4)+1];
						uint8_t byte3 = old_memory[(i*4)+2];
						uint8_t byte4 = old_memory[(i*4)+3];
						wr_word = (byte4 << 24) | (byte3 << 16) | (byte2 << 8) | byte1;
						FLASH_ProgramWord(start_address+(i*4),wr_word);
						i++;
				}
				
				/* If there are spare words, calculate and rewrite it */
				if(spare_words > 0){
						int j = 0;
						uint32_t spare = 0;
						wr_word = 0x00000000;
						while(j < spare_words){
								spare = old_memory[(i*4)+j];
								spare = spare << (24 - (j*8));
								wr_word = wr_word | spare;	
								j++;
						}						
						FLASH_ProgramWord(start_address+((i+1)*4),wr_word);
				}
}

uint8_t FLASH_MOD_ReadByte(uint32_t address){
	return *((uint8_t*) address);
}

uint32_t FLASH_MOD_ReadWord(uint32_t address){
	return FLASH_ReadWord(address);
}

void FLASH_MOD_WriteByte(uint32_t address, uint8_t byte_wr){
	
		/* Initially read all the config data */
		FLASH_MOD_Read_Conf_Memory_Area();
	
		/* Erase Memory <- Da problemi */ 
		//FLASH_EraseAddress(ADDRESS_START_CFG_MEMORY);
	
		/* Calculate the byte to substitute */
		uint16_t index_byte = address - ADDRESS_START_CFG_MEMORY;
		old_memory[index_byte] = byte_wr;
	
		/* Rewrite modified memory */
		FLASH_MOD_Rewrite_Memory();
		
}

void FLASH_MOD_WriteCharBurst(uint32_t start_address, char* data, uint16_t size){
	int i = 0;
	while(i < size){
		FLASH_MOD_WriteByte(start_address+i,(uint8_t) *(data+i));
		i++;
	}
}

void FLASH_MOD_WriteByteBurst(uint32_t start_address, uint8_t* data, uint16_t size){
	int i = 0;
	while(i < size){
		FLASH_MOD_WriteByte(start_address+i, *(data+i));
		i++;
	}
}

