#ifndef UART_H
#define UART_H

#pragma once

#include <stdint.h>

#define UART_BAUDRATE_1200   1200
#define UART_BAUDRATE_2400   2400
#define UART_BAUDRATE_4800   4800
#define UART_BAUDRATE_9600   9600
#define UART_BAUDRATE_19200  19200
#define UART_BAUDRATE_38400  38400
#define UART_BAUDRATE_57600  57600 // Baudrate time 8.68 µs
#define UART_BAUDRATE_115200 115200

#define UART_PARITY_EVEN 0
#define UART_PARITY_ODD  1
#define UART_PARITY_NONE 2

#define UART_1_BIT_STOP 0
#define UART_2_BIT_STOP 1

#define UART_5_WORD_LENGTH 5
#define UART_6_WORD_LENGTH 6
#define UART_7_WORD_LENGTH 7
#define UART_8_WORD_LENGTH 8

void init_uart(uint32_t baudrate, uint8_t stop_bits, uint8_t data_bits, uint8_t parity);

void send_char_uart(char data);

void send_string_uart(char *data, uint8_t len_data);

char receive_uart();

void enable_interrupt_tx();

void enable_interrupt_rx();

#endif