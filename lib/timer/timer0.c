#include <avr/io.h>

/* Prescaler value  */
#define TIMER0_PRESCALER_1    1
#define TIMER0_PRESCALER_8    8
#define TIMER0_PRESCALER_64   64
#define TIMER0_PRESCALER_256  256
#define TIMER0_PRESCALER_1024 1024

/* Timer mode */
#define TIMER0_NORMAL_MODE            0x00
#define TIMER0_PWM_PHASE_MODE         0x01
#define TIMER0_CTC_MODE               0x02
#define TIMER0_FAST_PWM_MODE          0x03
#define TIMER0_RESERVED_MODE          0x04 /* Not used */
#define TIMER0_CTC_MODE               0x05
#define TIMER0_PWM_PHASE_CORRECT_MODE 0x06
#define TIMER0_FAST_PWM_TOP_MODE      0x07

/* Init timer 0 */
void timer0_init(uint8_t mode, uint8_t output, uint16_t prescaler) {

    /* Clear timer register */
    TCCR0A = 0x00;

    switch(mode) {
        case TIMER0_NORMAL_MODE: /* Normal mode */
            TCCR0A = 0x00;
            TCCR0B &= ~(1 << WGM02);
        break;
        case TIMER0_PWM_PHASE_CORRECT_MODE: /* Phase Correct PWM and clear output on compare match */
            DDRD |= (1 << PD6); /* Output compare A (alternative PD6 for output compare B) */
            TCCR0A |= (1 << WGM00);
            TCCR0A |= (1 << COM0A1);
        break;
        case TIMER0_CTC_MODE: /* CTC mode */
            TCCR0A |= (1 << WGM01);
            TCCR0B &= ~(1 << WGM02);
        break;
        case TIMER0_FAST_PWM_MODE: /* Fast PWM with output OC0A and clear output on compare match */
            DDRD |= (1 << PD6);
            TCCR0A = (1 << WGM00);
            TCCR0A |= (1 << COM0A1);
        break;
    }

    TCCR0B = 0x00;

    switch(prescaler) {
        case 1:
            TCCR0B |= (1 << CS00); /* f_timer = 16 MHz */
        break;
        case 8:
            TCCR0B |= (1 << CS01); /* f_timer = 2 MHz */
        break;
        case 64:
            TCCR0B |= (1 << CS01) | (1 << CS00); /* f_timer = 250 kHz */
        break;
        case 256:
            TCCR0B |= (1 << CS02); /* f_timer = 62.5 kHz */
        break;
        case 1024:
            TCCR0B |= (1 << CS02) | (1 << CS00); /* f_timer = 15.625 kHz */
        break;
    }

    /* Reset the timer counter */
    TCNT0 = 0x00;

    return;
}

/* Set counter timer 0 (start different value) */
void timer0_set_counter(uint8_t counter) {

    TCNT0 = counter;

    return;
}

/* Enable interrupt overflow */
void timer0_enable_interrupt_overflow() {

    TIMSK0 |= (1 << TOIE0);

    return;
}

/* Enable interrupt overflow */
void timer0_disable_interrupt_overflow() {

    TIMSK0 &= ~(1 << TOIE0);

    return;
}

/* Enable interrupt compa */
void timer0_enable_interrupt_compa() {

    return;
}

/* Disable interrupt overflow */
void timer0_disable_interrupt_compa() {

    return;
}

/* Enable interrupt compb */
void timer0_enable_interrupt_compb() {

    return;
}

/* Enable interrupt overflow */
void timer0_disable_interrupt_compb() {

    return;
}

/* Set output compare register a */
void set_output_compare_register_a(uint8_t match_value) {

    OCR0A = match_value;

    return;
}

/* Set output compare register b */
void set_output_compare_register_b(uint8_t match_value) {

    OCR0B = match_value;

    return;
}