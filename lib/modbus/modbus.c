#include <stdint.h>
#include <stdlib.h>

#include "modbus.h"

/*
 | Address slave (1 byte) | Functional code (1 byte) | Data (N byte) | CRC16 (2 byte) |
*/

static uint16_t calc_crc16_msg(uint8_t *data, uint32_t length) {

    uint16_t crc = 0xFFFF;

    for (uint32_t i = 0; i < length; i++) {

        crc ^= (uint16_t)data[i];
        for (uint8_t bit = 0; bit < 8; bit++)  {
            if (crc & 0x0001) {
                crc = (crc >> 1) ^ 0x8005;
            } else {
                crc >>= 1;
            }
        }
    }

    return crc;
}

static void write_uint16_be(uint8_t *buf, uint16_t val) {

    buf[0] = (val >> 8) & 0xFF;
    buf[1] = val & 0xFF;

    return;
}

/* Read coil register */
uint8_t *build_read_coil_register(uint8_t address, uint16_t start_coil_registers, uint16_t num_coil_registers) {

    uint8_t *msg = (uint8_t *)calloc(8, sizeof(uint8_t));
    if(!msg)
        return NULL;

    msg[0] = address;
    msg[1] = READ_COIL_STATUS_REGISTER;

    write_uint16_be(&msg[2], start_coil_registers);
    write_uint16_be(&msg[4], num_coil_registers);

    uint16_t crc16 = calc_crc16_msg(msg, 8 - sizeof(uint16_t));

    write_uint16_be(&msg[6], crc16);

    return msg;
}