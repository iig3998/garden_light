#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <assert.h>

#include "gpio.h"
#include "uart.h"
#include "timer1.h"
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
    timer1_stop();

    if (idx_count <= SIZE_MODBUS_MESSAGE){
        modbus_msg[idx_count++] = UDR0;
    } else {
        memset(modbus_msg, 0, sizeof(modbus_msg));
        idx_count = 0;
    }

    /* Restart timer */
    timer1_reset_counter();

    /* Restart timer */
    timer1_start();

    sei();

    return;
}

/* Interrupt service routine TIMER1*/
ISR(TIMER1_COMPA_vect) {

    cli();

    world_ready = true;

    /* Stop and clear timer */
    timer1_stop();
    timer1_reset_counter();

    sei();

    return;
}

/* Manage coil register */
void mgmt_coil_register(uint8_t *modbus_msg) {

    if ((((modbus_msg[4] << 8) | modbus_msg[5]) >= ADDRESS_COIL_REGISTER_0) && (((modbus_msg[4] << 8) | modbus_msg[5]) <= ADDRESS_COIL_REGISTER_3)) {

        switch ((uint16_t)((modbus_msg[2] << 8) | modbus_msg[3])) {
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

/* Get modbus timeout */
static uint16_t get_timeout_modbus() {

    float timeout = (1 / (float)BAUDRATE ) * (WORD_LENGHT + 1 + BIT_PARITY + BIT_STOP) * 3.5;
    float t_clock = 1 / (float)F_CPU;

    printf("Timeout: %f\r\n", timeout);
    printf("T clock: %f\r\n", t_clock);

    printf("%u\r\n", (uint16_t)(timeout/t_clock));

    return (uint16_t)(timeout/t_clock);
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
    init_uart(UART_2_BIT_STOP, UART_PARITY_NONE, UART_8_WORD_LENGTH);

    /* Enable rx */
    rs485_enable_rx();

    /* Read modbus address slave */
    address_slave = read_address_slave();

    /* Stop timer1 */
    timer1_stop();

    /* Reset counter timer1 */
    timer1_reset_counter();

    /* Enable gloabl interrupt */
    sei();

    /* Enable interrupt rx */
    enable_interrupt_rx();

    while(1) {

        if(world_ready) {

            /* Valid only coil registers */
            crc16 = (modbus_msg[7] << 8)| modbus_msg[6];
            if ((modbus_msg[0] == address_slave) && (modbus_msg[1] == WRITE_SINGLE_COIL) && (crc16 == calc_crc16_msg(modbus_msg, idx_count - 1 - 2))) {
                mgmt_coil_register(modbus_msg);
                idx_count = 0;

                /* Send response */
                send_string_uart(modbus_msg, sizeof(modbus_msg));
            }
            world_ready = false;
        }

        _delay_ms(5);
    }

    return 0;
}
