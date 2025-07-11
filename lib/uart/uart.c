#include "uart.h"
#include <avr/io.h>

void init_uart(uint32_t baudrate, uint8_t stop_bits, uint8_t data_bits, uint8_t parity) {

    uint16_t ubrr = (F_CPU / (16UL * baudrate)) - 1;
    uint8_t ucsrc = 0;

    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)(ubrr);

    /* Enable RX and TX */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    /* Set stop bit */
    if (stop_bits == 2)
        ucsrc |= (1 << USBS0);  // 2 stop bit
    else
        ucsrc &= ~(1 << USBS0); // 1 stop bit (default)

    /* Set length world */
    switch (data_bits) {
        case 5: 
        break;
        case 6: 
            ucsrc |= (1 << UCSZ00); 
        break;
        case 7: 
            ucsrc |= (1 << UCSZ01);
        break;
        case 8: 
            ucsrc |= (1 << UCSZ01) | (1 << UCSZ00); 
        break;
        default: 
        break;
    }

    /* Parity bit */
    switch (parity) {
        case 0: 
        break;
        case 1: ucsrc |= (1 << UPM01) | (1 << UPM00);
        break;
        case 2: ucsrc |= (1 << UPM01);
        break;
        default: break;
    }

    UCSR0C = ucsrc;

    if (data_bits == 9)
        UCSR0B |= (1 << UCSZ02);
    else
        UCSR0B &= ~(1 << UCSZ02);

    return;
}

void send_char_uart(char data) {

    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;

    return;
}

void send_string_uart(char *data, uint8_t len_data) {

    for(uint8_t i = 0; i< len_data; i++) {
        send_char_uart(*data);
    }

    return;
}

/* Receive data from uart */
char receive_uart() {

    while (!(UCSR0A & (1 << RXC0)));

    return UDR0;
}

/* Enable interrupt tx */
void enable_interrupt_tx() {

    UCSR0B = (1 << TXEN0) | (1 << UDRIE0);

    return;
}

/* Enable interrupt rx */
void enable_interrupt_rx() {

    UCSR0B = (1 << RXEN0)  | (1 << TXEN0)  |  // Ricezione e trasmissione
             (1 << RXCIE0) | (1 << UDRIE0);   // Abilita interrupt RX e TX (UDR vuoto)

    return;
}