#ifndef TIMER1_H
#define TIMER1_H

#pragma once

#define MAJOR_TIMER1_VER 0
#define MINOR_TIMER1_VER 1
#define PATCH_TIMER1_VER 0

#include <stdint.h>

void timer1_init(uint8_t mode, uint8_t output, uint8_t prescaler);

void timer1_set_counter(uint16_t counter);

void timer1_enable_interrupt_overflow();

void timer1_disable_interrupt_overflow();

void timer1_enable_interrupt_compa();

void timer1_enable_interrupt_compb();

void timer1_enable_interrupt_compb();

void timer1_disable_interrupt_compb();

void timer1_set_output_compare_register_a(uint16_t match_value);

void timer1_set_output_compare_register_b(uint16_t match_value);

#endif