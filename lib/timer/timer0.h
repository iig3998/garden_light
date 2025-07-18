#ifndef TIMER0_H
#define TIMER0_H

#include <stdint.h>

#define OUTPUT_A 0
#define OUTPUT_B 1

void timer0_init(uint8_t mode, uint8_t output, uint16_t prescaler);

void timer0_set_counter(uint8_t counter);

void timer0_enable_interrupt_overflow();

void timer0_disable_interrupt_overflow();

void timer0_enable_interrupt_compa();

void timer0_enable_interrupt_compb();

void timer0_enable_interrupt_compb();

void timer0_disable_interrupt_compb();

void set_output_compare_register_a(uint8_t match_value);

void set_output_compare_register_b(uint8_t match_value);

#endif