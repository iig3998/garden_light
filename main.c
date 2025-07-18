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
static uint8_t idx_count = 0;
static uint8_t modbus_msg[SIZE_MODBUS_MESSAGE] = {0x00};

/* Enable tx modbus */
void rs485_enable_tx(void) {

    set_gpio_high_level(&DDRD, PIND2);

    return;
}

/* Enable rx modbus */
void rs485_enable_rx(void) {

    set_gpio_low_level(&DDRD, PIND2);

    return;
}

/* Read address slave */
uint8_t read_address_slave() {

    return  (read_gpio_input(&DDRB, PINB4) << 1) | read_gpio_input(&DDRB, PINB4);

}

/* ISR receiver uart */
ISR(USART_RX_vect) {

    cli();

    /* Stop timer */

    if (idx_count <= SIZE_MODBUS_MESSAGE){
        modbus_msg[idx_count++] = UDR0;

        /* Restart timer */
    }

    /* Restart timer */

    sei();

    return;
}

/* Interrupt service routine TIMER1*/
ISR(TIMER1_OVF_vect) {

    world_ready = true;

    /* Stop and clear timer */

    return;
}

/* Manage coil register */
void mgmt_coil_register(uint8_t *modbus_msg) {

    if ((((modbus_msg[4] << 8) | modbus_msg[5]) >= ADDRESS_COIL_REGISTER_0) && (((modbus_msg[4] << 8) | modbus_msg[5]) <= ADDRESS_COIL_REGISTER_3)) {

        switch (((modbus_msg[2] << 8) | modbus_msg[3])) {
            case COIL_ON:
                set_gpio_high_level(&PORTC, (modbus_msg[4] << 8) | modbus_msg[5]);
            break;
            case COIL_OFF:
                set_gpio_low_level(&PORTC, (modbus_msg[4] << 8) | modbus_msg[5]);
            break;
            default:
            break;
        }
    }

    return;
}

/* Main program */
int main() {

    uint8_t address_slave = 0x00;
    uint16_t crc16 = 0x00;

    /* Disable global interrupt */
    cli();

    /* Set gpio output */
    set_gpio_output(&DDRC, PINC3);
    set_gpio_output(&DDRC, PINC2);
    set_gpio_output(&DDRC, PINC1);
    set_gpio_output(&DDRC, PINC0);

    set_gpio_output(&DDRD, PIND2);

    /* GPIO for read address */
    set_gpio_input(&DDRB, PINB4);
    set_gpio_input(&DDRB, PINB5);

    /* Set low gpio output */
    set_gpio_low_level(&PORTC, PINC3);
    set_gpio_low_level(&PORTC, PINC2);
    set_gpio_low_level(&PORTC, PINC1);
    set_gpio_low_level(&PORTC, PINC0);

    /* Init uart */
    init_uart(UART_BAUDRATE_115200, UART_2_BIT_STOP, UART_8_WORD_LENGTH, UART_PARITY_NONE);

    /* Enable rx */
    rs485_enable_rx();

    /* Read modbus address slave */
    address_slave = read_address_slave();

    /* Enable gloabl interrupt */
    sei();

    /* Enable interrupt rx */
    enable_interrupt_rx();

    while(1) {

        if(world_ready) {

            crc16 = (modbus_msg[7] << 8)| modbus_msg[6];

            if ((modbus_msg[1] == WRITE_SINGLE_COIL) && (modbus_msg[0] == address_slave) && (crc16 == calc_crc16_msg(modbus_msg, idx_count - 1 - 2))) {
                mgmt_coil_register(modbus_msg);
                idx_count = 0;
            }
            world_ready = false;
        }

        _delay_ms(5);
    }

    return 0;
}
