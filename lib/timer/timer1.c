#include "timer1.h"

#include <avr/io.h>

/* Prescaler value  */
#define TIMER0_PRESCALER_1    1
#define TIMER0_PRESCALER_8    8
#define TIMER0_PRESCALER_64   64
#define TIMER0_PRESCALER_256  256
#define TIMER0_PRESCALER_1024 1024

void timer1_init(uint8_t mode, uint8_t output, uint16_t prescaler) {

    /* Clear timer register */
    TCCR1A = 0x00;

    switch(mode) {
        case TIMER1_NORMAL_MODE:
            TCCR1A = 0x00;
            TCCR1B &= ~(1 << WGM02);
        break;
        case TIMER1_CTC_MODE:
            TCCR1A |= (1 << WGM01);
            TCCR1B &= ~(1 << WGM02);
        break;
        default:
        break;
    }

    TCCR1B = 0x00;

    switch(prescaler) {
        case 0:
            TCCR1B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); /* No source clock */
        break;
        case 1:
            TCCR1B |= (1 << CS00); /* f_timer = 16 MHz */
        break;
        case 8:
            TCCR1B |= (1 << CS01); /* f_timer = 2 MHz */
        break;
        case 64:
            TCCR1B |= (1 << CS01) | (1 << CS00); /* f_timer = 250 kHz */
        break;
        case 256:
            TCCR1B |= (1 << CS02); /* f_timer = 62.5 kHz */
        break;
        case 1024:
            TCCR1B |= (1 << CS02) | (1 << CS00); /* f_timer = 15.625 kHz */
        break;
        default:
        break;
    }

    /* Reset counter */
    TCNT1H = 0x00;
    TCNT1L = 0x00;

    TCCR1C = 0x00;

    return;
}

/* Start timer 1 */
void timer1_start(uint16_t prescaler) {

    switch(prescaler) {
        case 0:
            TCCR1B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); /* No source clock */
        break; 
        case 1:
            TCCR1B |= (1 << CS00); /* f_timer = 16 MHz */
        break;
        case 8:
            TCCR1B |= (1 << CS01); /* f_timer = 2 MHz */
        break;
        case 64:
            TCCR1B |= (1 << CS01) | (1 << CS00); /* f_timer = 250 kHz */
        break;
        case 256:
            TCCR1B |= (1 << CS02); /* f_timer = 62.5 kHz */
        break;
        case 1024:
            TCCR1B |= (1 << CS02) | (1 << CS00); /* f_timer = 15.625 kHz */
        break;
        default:
        break;
    }

    return;
}

/* reset counter timer 1 */
void timer1_reset_counter() {

    /* Reset counter */
    TCNT1H = 0x00;
    TCNT1L = 0x00;

    return;
}

/* Stop timer 1 */
void timer1_stop() {

    /* Stop timer 1*/
    TCCR1B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));

    return;
}

void timer1_set_ctc_compare_match(uint16_t ctc_compare_match) {

    OCR1A = ctc_compare_match;

    return;
}

void timer1_enable_ctca_interrupt() {

    TIMSK1 |= (1 << OCIE1A);

    return;
}

void timer1_disable_ctca_interrupt() {

    TIMSK1 &= ~(1 << OCIE1A);

    return;
}

void timer1_disable_ctcb_interrupt() {

    TIMSK1 &= ~(1 << OCIE1B);

    return;
}