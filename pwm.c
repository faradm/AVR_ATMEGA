/* PWM Demo with serial control over three LEDs */

// ------- Preamble -------- //
#include <avr/io.h> /* Defines pins, ports, etc */
#include <util/delay.h> /* Functions to waste time */
#include "USART.h"
#define LED_DDR DDRA
#define LED_PORT PORTA
#define PULSE_MIN 1000
#define PULSE_MID 1500
#define PULSE_MAX 2000
static inline void servo_timer_init(void)
{
	TCCR1A |= (1 << COM1A1);
	TCCR1A |= (1 << WGM11); 
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	TCCR1B |= ( 1 << CS11);
	ICR1 = 20000;
	DDRD = ( 1 << PORTD5);
}
void drive_servo(uint16_t servo_pulse_length)
{
	OCR1A = servo_pulse_length;
	DDRD |= (1 << PORTD5);
	_delay_ms(1000);
	usart_string_transmit("Releasing...\r\n");
	while (TCNT1 < 3000);
	DDRD &= ~(1 << PORTD5);
}
int main(void)
{
	usart_init();
	servo_timer_init();
	while(1)
	{
		usart_string_transmit("enter number in milies\r\n");
		drive_servo(usart_number_receive());
	}
}
