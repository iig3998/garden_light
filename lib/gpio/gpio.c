#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <avr/io.h>

#include "gpio.h"

/*
    PORTB (PB0 - PB7)
    PORTC (PC0 - PC6)
    PORTD (PD0 - PD7)
*/

/* Set gpio as output */
void set_gpio_output(volatile uint8_t *ddr, uint8_t gpio) {

    *ddr |= (1 << gpio);

    return;
}

/* Set gpio as input */
void set_gpio_input(volatile uint8_t *ddr, uint8_t gpio) {

    *ddr &= ~(1 << gpio);

    return;
}

/* Set gpio output high */
void set_gpio_high_level(volatile uint8_t *port, uint8_t gpio) {

    *port |= (1 << gpio);

    return;
}

/* Set gpio output low */
void set_gpio_low_level(volatile uint8_t *port, uint8_t gpio) {

    *port &= ~(1 << gpio);

    return;    
}

/**/
uint8_t read_gpio_input(volatile uint8_t *port, uint8_t gpio) {

    return ((*port & (1 << gpio)) != 0) ? 1 : 0;
}

/**/
void toggle_gpio(volatile uint8_t *port, uint8_t gpio) {

    return;
}