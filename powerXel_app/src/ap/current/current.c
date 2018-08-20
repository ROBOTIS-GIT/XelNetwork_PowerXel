/*
 * current.c
 *
 *  Created on: 2018. 3. 29.
 *      Author: D.ggavy
 */

#include "current.h"

#define ACS_OFFSET 410
#define _MV_PER_AMP 132

uint16_t currentRead0_1mA(uint8_t ch)
{
  uint32_t adc_value = 0;
  uint32_t adc_voltage;

  adc_value = adcRead(ch);

  if(adc_value - ACS_OFFSET < 0)
  {
    adc_value = ACS_OFFSET;
  }

  adc_voltage = (adc_value - ACS_OFFSET) *3300 /4096;


  adc_value = (adc_voltage *1000 /_MV_PER_AMP);

  return (uint16_t) adc_value;
}
