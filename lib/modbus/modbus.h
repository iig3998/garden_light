#ifndef MODBUS_H
#define MODBUS_H

#pragma once

#include <stdint.h>

/* Address register */
#define COIL_REGISTER           0x0001
#define DISCRETE_INPUT_REGISTER	0x1001
#define INPUT_REGISTER	        0x3001
#define HOLDING_REGISTER        0x4001

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

#endif