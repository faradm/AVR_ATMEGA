#include "ADC.h"

void adc_init()
{
	//ADCH and ADCL store 10 bit after they have been converted to digital
	/*Once ADCL is read, ADC access to Data Registers is blocked. This means that if ADCL has been
	read, and a conversion completes before ADCH is read, neither register is updated and the result from the
	conversion is lost. When ADCH is read, ADC access to the ADCH and ADCL Registers is re-enabled*/
	ADMUX |= (1 << REFS0);//Reference voltage
	ADCSRA |= (1 << ADPS1) | (1 << ADPS2); 
	ADCSRA |= (1 << ADEN);//Enabling ADC
}
uint16_t adc_convert()
{
	ADCSRA |= (1 << ADSC);//Start ADC conversion
	while (!(ADCSRA & (1 << ADSC)));//Wait until conversion ends
	return ADC;
}