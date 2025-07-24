#include <avr/io.h>

#include "uart.h"

/* Set asynchronous usart mode */
void set_asynchronous_usart_mode() {

    UCSR0C &= ~((1 << UMSEL01) | (1 << UMSEL00));

    return;
}

/* Set synchronous usart mode */
void set_synchronous_usart_mode() {

    UCSR0C |= (1 << UMSEL00);

    return;
}

/* Init uart */
void init_uart(uint8_t stop_bits, uint8_t parity, uint8_t data_bits) {

    uint16_t ubrr = (F_CPU / (16UL * BAUDRATE)) - 1;
    uint8_t ucsrc = 0;

    UBRR0H = (uint8_t)((ubrr >> 8) & 0x0F);
    UBRR0L = (uint8_t)((ubrr) & 0xFF);

    /* Enable RX and TX */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    /* Set stop bit */
    switch(stop_bits) {
        case 2:
            /* 2 stop bits */
            ucsrc |= (1 << USBS0);
        break;
        case 1:
            /* 1 stop bit */
            ucsrc &= ~(1 << USBS0);
        break;
    }

    /* Set length world */
    switch(data_bits) {
        case UART_5_WORD_LENGTH:
            ucsrc &= ~((1 << UCSZ00) | (1 << UCSZ01) | (1 << UCSZ00));
        break;
        case UART_6_WORD_LENGTH:
            ucsrc |= (1 << UCSZ00); 
        break;
        case UART_7_WORD_LENGTH:
            ucsrc |= (1 << UCSZ01);
        break;
        case UART_8_WORD_LENGTH:
            ucsrc |= (1 << UCSZ01) | (1 << UCSZ00); 
        break;
        default:
        break;
    }

    /* Parity bit */
    switch (parity) {
        case 0:
            /* Disable parity bits */
            ucsrc &= ~((1 << UPM01) | (1 << UPM00));
        break;
        case 1:
            /* Even parity */
            ucsrc |= (1 << UPM01) | (1 << UPM00);
        break;
        case 2:
            /* Odd parity */
            ucsrc |= (1 << UPM01);
        break;
        default:
        break;
    }

    UCSR0C = ucsrc;

    if (data_bits == 9)
        UCSR0B |= (1 << UCSZ02);
    else
        UCSR0B &= ~(1 << UCSZ02);

    return;
}

/* Send char uart */
void send_char_uart(char data) {

    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;

    return;
}

/* Send string uart */
void send_string_uart(char *data, uint8_t len_data) {

    for(uint8_t i = 0; i < len_data; i++) {
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