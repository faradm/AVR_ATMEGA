#include <stdbool.h>
#include <util/delay.h>
#include <avr/common.h>
#include <avr/interrupt.h>
void dallas_write_one();
void dallas_write_zero();
bool dallas_read_bit();
bool dallas_detect_presence();
void dallas_write_byte(uint8_t byte);
uint8_t dallas_read_byte();