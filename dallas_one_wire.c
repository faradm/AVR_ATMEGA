#include "dallas_definition.h"
#include "dallas_one_wire.h"
bool dallas_detect_presence()
{
	uint8_t bus_state;
	uint8_t sreg = SREG;//save current interrupt state
	cli();//disable interrupts
	_delay_us(DALLAS_DELAY_G);
	DALLAS_PORT |= (1 << DALLAS_PP_NUM);
	DALLAS_DDR |= (1 << DALLAS_PP_NUM);
	DALLAS_PORT &= ~(1 << DALLAS_PP_NUM);
	_delay_us(DALLAS_DELAY_H);
	DALLAS_DDR &= ~(1 << DALLAS_PP_NUM);
	_delay_us(DALLAS_DELAY_I);
	bus_state = DALLAS_PIN;
	_delay_us(DALLAS_DELAY_J);
	SREG = sreg;//Restore interrupts
	return ((bus_state&( 1 << DALLAS_PP_NUM)) == 1) ? 1 : 0;
}
bool dallas_read_bit()
{
	uint8_t sreg = SREG;
	bool bus_state;
	cli();
	DALLAS_PORT |= (1 << DALLAS_PP_NUM);
	DALLAS_DDR |= (1<<DALLAS_PP_NUM);
	DALLAS_PORT &= ~(1<<DALLAS_PP_NUM);
	_delay_us(DALLAS_DELAY_A);
	DALLAS_DDR &= ~(1<<DALLAS_PP_NUM);
	_delay_us(DALLAS_DELAY_E);
	bus_state = DALLAS_PIN & ( 1 << DALLAS_PP_NUM);
	_delay_us(DALLAS_DELAY_F);
	SREG = sreg;
	return bus_state;
}
void dallas_write_zero()
{
	uint8_t sreg = SREG;
	cli();
	DALLAS_PORT |= (1 << DALLAS_PP_NUM);
	DALLAS_DDR |= (1<<DALLAS_PP_NUM);
	DALLAS_PORT &= ~(1<<DALLAS_PP_NUM);
	_delay_us(DALLAS_DELAY_C);
	DALLAS_DDR &= ~(1<<DALLAS_PP_NUM);
	_delay_us(DALLAS_DELAY_D);
	SREG = sreg;
}
void dallas_write_one()
{
	uint8_t sreg = SREG;
	cli();
	DALLAS_PORT |= (1 << DALLAS_PP_NUM);
	DALLAS_DDR |= (1<<DALLAS_PP_NUM);
	DALLAS_PORT &= ~(1<<DALLAS_PP_NUM);
	_delay_us(DALLAS_DELAY_A);
	DALLAS_DDR &= ~(1<<DALLAS_PP_NUM);
	_delay_us(DALLAS_DELAY_B);
	SREG = sreg;	
}
void dallas_write_byte(uint8_t byte)
{
	for(int i = 0; i < 8; i++)
	{
		if((byte & ( 1 << i)) == 1)
			dallas_write_one();
		else
			dallas_write_zero();
	}
}
uint8_t dallas_read_byte()
{
	uint8_t data = 0x00;
	uint8_t mask = 0x01;
	while(mask)
	{
		if (dallas_read_bit())
			data |= mask;
		mask <<= 1;
	}
	return data;
}