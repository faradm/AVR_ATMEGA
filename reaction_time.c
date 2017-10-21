#include <avr/io.h>
#include <stdio.h>
#include "USART.h"
#include <util/delay.h>
#include "scale16.h"
#define SPEAKER_DDR DDRB
#define SPEAKER_PORT PORTB
#define SPEAKER_PP_NUM PORTB3
static inline void init_timer0()
{
	TCCR0 |= (1 << WGM01) | ( 1 << COM00) | (1 << CS02);
}
static inline void play_note(uint8_t wavelength, uint8_t duration)
{
	OCR0 = wavelength;
	SPEAKER_DDR |= ( 1 << SPEAKER_PP_NUM);
	while(duration)
	{
		_delay_ms(1);
		duration--;
	}
	SPEAKER_DDR &= ~(1 << SPEAKER_PP_NUM);
}
int mainn()
{
	init_timer0();
	while(1)
	{
		play_note(C2, 1000);
		_delay_ms(500);
		play_note(E2, 1000);
		_delay_ms(500);
		play_note(G2, 1000);
		_delay_ms(500);
		play_note(E3, 1000);
		_delay_ms(500);
	}
}