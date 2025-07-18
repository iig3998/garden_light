#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <assert.h>

#include "gpio.h"
#include "uart.h"
#include "modbus.h"

#define SIZE_MODBUS_MESSAGE 10

static bool world_ready = false;
static uint8_t modbus_msg[SIZE_MODBUS_MESSAGE] = {0x00};

/* Set coil register */
static void set_coil_register(uint8_t coil) {

    assert(coil >= 0 && coil <= 7);

    coil_register |= (1 << coil);

    return;
}

/* Clear coil register */
static void clear_coil_register(uint8_t coil) {

    assert(coil >= 0 && coil <= 7);

    coil_register &= ~(1 << coil);

    return;
}

/* Enable tx modbus */
void rs485_enable_tx(void) {

    set_gpio_high_level(&DDRD, 2);

    return;
}

/* Enable rx modbus */
void rs485_enable_rx(void) {

    set_gpio_low_level(&DDRD, 2);

    return;
}

/* ISR receiver uart */
ISR(USART_RX_vect) {

    static idx_count = 0;

    modbus_msg[idx_count++] = UDR0;

    return;
}

/* Main program */
int main() {

    /* Set gpio output */
    set_gpio_output(&DDRC, 3); // PC3
    set_gpio_output(&DDRC, 2); // PC2
    set_gpio_output(&DDRC, 1); // PC1
    set_gpio_output(&DDRC, 0); // PC0

    set_gpio_output(&DDRD, 2); // PD2

    /* Set low gpio output */
    set_gpio_low_level(&PORTC, 3);
    set_gpio_low_level(&PORTC, 2);
    set_gpio_low_level(&PORTC, 1);
    set_gpio_low_level(&PORTC, 0);

    set_gpio_output(&DDRD, 2); // Enable Modbus

    /* Init uart */
    init_uart(UART_BAUDRATE_115200, UART_2_BIT_STOP, UART_8_WORD_LENGTH, UART_PARITY_NONE);

    /* Enable rx */
    rs485_enable_rx();

    /* Enable gloabl interrupt */
    sei();

    /* Enable interrupt rx */
    enable_interrupt_rx();

    while(1) {

        _delay_ms(10);
    }

    return 0;
}
