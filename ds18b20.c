#include "dallas_one_wire.h"
#include "dallas_definition.h"
#include "ds18b20.h"
bool ds_init()
{
	return dallas_detect_presence();
}
/*void ds_search_rom()
{
	//send search command
	uint8_t read_bus;
	read_bus 
}*/
void ds_skip_rom()
{
	dallas_write_byte(DS_SKIP_ROM);
}
void ds_convert()//NON_PARASITE, NOTE: Only returns after conversion is complete.
{
	dallas_write_byte(DS_CONVERT);
	while(!dallas_read_bit());
}
void ds_write_scratchpad(uint8_t th_register, uint8_t tl_register, uint8_t configuration_register)
{
	dallas_write_byte(DS_WRITE_SCRATCHPAD);
	dallas_write_byte(th_register);
	dallas_write_byte(tl_register);
	dallas_write_byte(configuration_register);
}

uint8_t data[9];
uint8_t* ds_read_scratchpad()
{
	dallas_write_byte(DS_READ_SCRATCHPAD);
	for(int i = 0; i < 9; i++)
	{
		data[i] = dallas_read_byte();
	}
	return data;
}
void ds_copy_scratchpad()//NON_PARASITE
{
	dallas_write_byte(DS_COPY_SCRATCHPAD);
}
void ds_recall_ee()//NOTE: Only returns after recall completed
{
	dallas_write_byte(DS_RECALL_EE);
	while(!dallas_read_bit());
}
bool ds_is_parasite()
{
	return !dallas_read_bit();
}