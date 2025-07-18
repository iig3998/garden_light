#ifndef MODBUS_H
#define MODBUS_H

#pragma once

#include <stdint.h>

#define MAJOR_MODBUS_VER 0
#define MINOR_MODBUS_VER 1
#define PATCH_MODBUS_VER 0

/* Address coil register */
#define ADDRESS_COIL_REGISTER_0         0x0000
#define ADDRESS_COIL_REGISTER_1         0x0001
#define ADDRESS_COIL_REGISTER_2         0x0002
#define ADDRESS_COIL_REGISTER_3         0x0003
#define COIL_ON                         0xFF00
#define COIL_OFF                        0x0000

#define ADDRESS_DISCRETE_INPUT_REGISTER	0x1001
#define ADDRESS_INPUT_REGISTER	        0x3001
#define ADDRESS_HOLDING_REGISTER        0x4001

/* Functional code */
#define READ_COIL_STATUS_REGISTER    0x01
#define READ_INPUT_STATUS            0x02 
#define READ_HOLDING_REGISTER        0x03 
#define READ_INPUT_REGISTERS         0x04
#define WRITE_SINGLE_COIL            0x05

#define PRESET_SINGLE_REGISTER       0x06
#define READ_STATUS_DIAGNOSTICS      0x07
#define FORCE_MULTIPLE_COILS_BITS    0x0F
#define PRESET_MULTIPLE_REGISTERS    0x10
#define REPORT_SERVER_ID_DIAGNOSTICS 0x11
#define READ_FILE_RECORD             0x14
#define WRITE_FILE_RECORD            0x15
#define MASK_WRITE_REGISTER          0x16
#define READ_WRITE_MULTIPLE          0x17
#define READ_DEVICE_IDENTIFICATION   0x2B

/*
 - Coil register
 - Discrete input
 - Input register
 - Holding register
*/

uint8_t *build_read_coil_register(uint8_t address, uint16_t start_coil_registers, uint16_t num_coil_registers);

uint16_t calc_crc16_msg(uint8_t *data, uint32_t length);

#endif