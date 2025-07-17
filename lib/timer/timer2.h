#ifndef TIMER2_H
#define TIMER2_H

#pragma once

#define MAJOR_TIMER2_VER 0
#define MINOR_TIMER2_VER 1
#define PATCH_TIMER2_VER 0

#include <stdint.h>

void timer2_init(uint8_t mode, uint8_t output, uint8_t prescaler);

void timer2_set_counter(uint8_t counter);

void timer2_enable_interrupt_overflow();

void timer2_disable_interrupt_overflow();

void timer2_enable_interrupt_compa();

void timer2_enable_interrupt_compb();

void timer2_enable_interrupt_compb();

void timer2_disable_interrupt_compb();

void timer2_set_output_compare_register_a(uint8_t match_value);

void timer2_set_output_compare_register_b(uint8_t match_value);

#endif