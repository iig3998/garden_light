#ifndef GPIO_H
#define GPIO_H

#pragma once

// https://www.jotrin.it/technology/details/pin-configuration-of-arduino-nano

void set_gpio_output(volatile uint8_t *ddr, uint8_t gpio);

void set_gpio_input(volatile uint8_t *ddr, uint8_t gpio);

void set_gpio_high_level(volatile uint8_t *port, uint8_t gpio);

void set_gpio_low_level(volatile uint8_t *port, uint8_t gpio);

void toggle_gpio(volatile uint8_t *port, uint8_t gpio);

uint8_t read_gpio_input(volatile uint8_t *port, uint8_t gpio);

#endif