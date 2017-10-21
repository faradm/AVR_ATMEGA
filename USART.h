#define BAUD 9600
#define MYUBRR ((F_CPU)/(BAUD*16UL)-1)
#include <avr/io.h>
void usart_init();
void usart_char_transmit(uint8_t data);
void usart_string_transmit(uint8_t data[]);
uint8_t usart_char_recieve();
uint8_t usart_number_receive();