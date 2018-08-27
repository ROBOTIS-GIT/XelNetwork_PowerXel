/*
 * test_vcp.c
 *
 *  Created on: 2018. 2. 13.
 *      Author: kei
 */

#include "ap.h"

#include "test_def.h"

//-- Internal Variables
//

//-- External Variables
//

//-- Internal Functions
//

//-- External Functions
//

#if _TEST_ENABLE_CURRENT
static void testAdcVolCurr(void);
#endif

void testMain(void)
{

#if _TEST_ENABLE_CURRENT
  testAdcVolCurr();
#endif
}


#if _TEST_ENABLE_CURRENT
static void testAdcVolCurr(void)
{
  bool ret = true;
  uint32_t pre_time;
  uint8_t ch;
  uint16_t adc_value;
  static dxl_t dxl_cmd;
  dxl_error_t dxl_ret = DXL_RET_OK;
  dxlcmd_resp_t  resp;
  uint32_t tx_data;

  dxlInit(&dxl_cmd, DXL_PACKET_VER_2_0);

  ret = dxlOpenPort(&dxl_cmd, _DEF_DXL1, 115200);
  if (ret == true)
  {
    dxlportPrintf(_DEF_DXL1, "open is OK Ver2.0, _DEF_DXL1");
  }
  else
  {
    dxlportPrintf(_DEF_DXL1, "open is FAIL, _DEF_DXL1");
  }

  pre_time = millis();

  while (1)
  {

    if (millis() - pre_time >= 500)
    {
      pre_time = millis();

      ledToggle(0);

      for (ch = 0; ch < _HW_DEF_ADC_CH_MAX; ch++)
      {
        adcSetup(ch);
      }

      if (ret == false)
      {
        dxlportPrintf(_DEF_DXL1, "ADC communication Fail...\r\n");
      }
      else
      {
        adc_value = adcRead(0);
        dxlportPrintf(_DEF_DXL1, "%d : %d - %d.%d V, ", 1, (int) adc_value,
            (int) (adcConvVoltage(0, adc_value) / 100),
            (int) (adcConvVoltage(0, adc_value) % 100));
        while(dxlportIsTxDone(_DEF_DXL1) == false);

        adc_value = adcRead(1);
        dxlportPrintf(_DEF_DXL1, "%d : %d - %d          .%d mA \r\n", 2, (int) adc_value,
            (int) (currentRead0_1mA(1)),
            (int) (currentRead0_1mA(1)));
      }
    }
  }

}

#endif
