#include "USART.h"
void usart_init()
{
	UBRRH = (uint8_t)(MYUBRR>>8);
	UBRRL = (uint8_t)(MYUBRR);
	UCSRB = (1 << TXEN) | (1 << RXEN);
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}
uint8_t usart_char_receive()
{
	while(!(UCSRA & (1 << RXC)));
	return UDR;
}

void usart_char_transmit(uint8_t data)
{
	while(!(UCSRA & (1 << UDRE)));
	UDR = data;
}
void usart_string_transmit(uint8_t data[])
{
	int i = 0;
	while(data[i])
	{
		usart_char_transmit(data[i]);
		i++;
	}
}
uint8_t usart_number_receive()//################TODO: TO BE EDITED###########
{
	// Gets a numerical 0-255 from the serial port.
	// Converts from string to number.
	uint8_t i = 0;
	char hundreds = '0';
	char tens = '0';
	char ones = '0';
	char thisChar = '0';
	do {                                                   /* shift over */
		hundreds = tens;
		tens = ones;
		ones = thisChar;
		thisChar = usart_char_receive();                   /* get a new character */
		i++;                                    /* echo */
		} while (i < 3);                     /* until type return */
		return (100 * (hundreds - '0') + 10 * (tens - '0') + ones - '0');
}