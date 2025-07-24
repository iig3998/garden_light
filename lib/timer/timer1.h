#ifndef TIMER1_H
#define TIMER1_H

#pragma once

#define MAJOR_TIMER1_VER 0
#define MINOR_TIMER1_VER 1
#define PATCH_TIMER1_VER 0

#include <stdint.h>

/* Prescaler value  */
#define TIMER0_PRESCALER_1    1
#define TIMER0_PRESCALER_8    8
#define TIMER0_PRESCALER_64   64
#define TIMER0_PRESCALER_256  256
#define TIMER0_PRESCALER_1024 1024

/* Timer mode */
#define TIMER1_NORMAL_MODE                      0x00 // Normal mode
#define TIMER1_CTC_MODE                         0x01 // Clear to comapre match mode
#define TIMER1_FAST_PWM_MODE                    0x02 // Fast PWM mode
#define TIMER1_PHASE_CORRECT_PWM_MODE           0x03 // Phase correct pwm
#define TIMER1_PHASE_FREQUENCY_CORRECT_PWM_MODE 0x04 // Phase frequency correct pwm mode

void timer1_init(uint8_t mode, uint8_t output, uint16_t prescaler);

void timer1_set_counter(uint16_t counter);

void timer1_start();

void timer1_reset_counter();

void timer1_stop();

void timer1_enable_interrupt_overflow();

void timer1_disable_interrupt_overflow();

void timer1_enable_interrupt_compa();

void timer1_enable_interrupt_compb();

void timer1_enable_interrupt_compb();

void timer1_disable_interrupt_compb();

void timer1_set_output_compare_register_a(uint16_t match_value);

void timer1_set_output_compare_register_b(uint16_t match_value);

#endif