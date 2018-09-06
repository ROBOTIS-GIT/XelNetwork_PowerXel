/*
 * xels_db_access.cpp
 *
 *  Created on: 2018. 9. 4.
 *      Author: D.ggavy
 */


#include "hw.h"
#include "ap_def.h"
#include "xels/xels_struct.hpp"
#include "xels.h"


void xels_db_accessUpdatePower(xel_data_type_t* xel_data)
{
  data_t value;

  adcSetup(0);
  adcSetup(1);

  xel_data->POWER.voltage = adcConvVoltage(0, adcRead(0));
  xel_data->POWER.current = currentRead0_1mA(1)/100;
}


void xels_db_accessActivateLED(xel_data_type_t* xel_data)
{
  if (xel_data->BOOLEAN == 0)
  {
    ledOff(_DEF_LED1);
  }
  else
  {
    ledOn(_DEF_LED1);
  }
}
