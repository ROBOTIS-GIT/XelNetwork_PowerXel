/*
 * dxl_ctable.cpp
 *
 *  Created on: 2017. 7. 18.
 *      Author: baram
 */



#include "ap.h"
#include "util.h"




void updateVersion(uint32_t addr, uint8_t mode, uint16_t update_addr, uint8_t *p_data, uint16_t update_length);
void updateDxlId(uint32_t addr, uint8_t mode, uint16_t update_addr, uint8_t *p_data, uint16_t update_length);
void updateDxlBaud(uint32_t addr, uint8_t mode, uint16_t update_addr, uint8_t *p_data, uint16_t update_length);
void updateMillis(uint32_t addr, uint8_t mode, uint16_t update_addr, uint8_t *p_data, uint16_t update_length);
void updateVoltage(uint32_t addr, uint8_t mode, uint16_t update_addr, uint8_t *p_data, uint16_t update_length);
void updateCurrent(uint32_t addr, uint8_t mode, uint16_t update_addr, uint8_t *p_data, uint16_t update_length);




ctable_attribute_t ctable_power[] =
{
//addr                            len  count
  { P_CONST_MODEL_NUMBER,           2,     1, _ATTR_RD           ,  DXL_MODEL_NUMBER, _UPDATE_NONE    , _DEF_TYPE_U16,    NULL },
  { P_CONST_MODEL_INFO,             4,     1, _ATTR_RD           ,                 0, _UPDATE_NONE    , _DEF_TYPE_U32,    NULL },
  { P_CONST_FW_VERSION,             1,     1, _ATTR_RD           ,                 1, _UPDATE_NONE    , _DEF_TYPE_U08,    updateVersion },
  { P_EEP_ID,                       1,     1, _ATTR_RD | _ATTR_WR,       DXL_INIT_ID, _UPDATE_STARTUP , _DEF_TYPE_U08,    updateDxlId },
  { P_EEP_DXL_BAUDRATE,             1,     1, _ATTR_RD | _ATTR_WR,     DXL_INIT_BAUD, _UPDATE_STARTUP , _DEF_TYPE_U08,    updateDxlBaud },
  { P_MILLIS,                       4,     1, _ATTR_RD           ,                 0, _UPDATE_NONE    , _DEF_TYPE_U32,    updateMillis },
  { P_VOLTAGE,                      4,     1, _ATTR_RD           ,                 0, _UPDATE_NONE    , _DEF_TYPE_U32,    updateVoltage },
  { P_CURRENT,                      4,     1, _ATTR_RD           ,                 0, _UPDATE_NONE    , _DEF_TYPE_U32,    updateCurrent },







  { 0xFFFF,  1, 0, 0, 0, 0, 0, NULL }
};








void dxlCtableInit(void)
{
  if (eepromReadByte(EEP_ADDR_CHECK_AA) != 0xAA || eepromReadByte(EEP_ADDR_CHECK_55) != 0x55)
  {
    eepromWriteByte(EEP_ADDR_CHECK_AA, 0xAA);
    eepromWriteByte(EEP_ADDR_CHECK_55, 0x55);

    eepromWriteByte(EEP_ADDR_ID, DXL_INIT_ID);
    eepromWriteByte(EEP_ADDR_BAUD, DXL_INIT_BAUD);
  }

  ctableInit(&p_ap->ctable, NULL, 1024, ctable_power);
}

void updateVersion(uint32_t addr, uint8_t mode, uint16_t update_addr, uint8_t *p_data, uint16_t update_length)
{
  if (mode == _UPDATE_RD)
  {
    switch(addr)
    {
      case P_CONST_FW_VERSION:
        p_data[0] = p_ap->firmware_version;
        break;
    }
  }

  if (mode == _UPDATE_WR)
  {
    switch(addr)
    {
      case P_CONST_FW_VERSION:
        p_data[0] = p_ap->firmware_version;
        break;
    }
  }
}

void updateDxlId(uint32_t addr, uint8_t mode, uint16_t update_addr, uint8_t *p_data, uint16_t update_length)
{
  if (mode == _UPDATE_INIT)
  {
    if (addr == P_EEP_ID)
    {
      mode = _UPDATE_WR;
    }
  }

  if (mode == _UPDATE_STARTUP)
  {
    if (addr == P_EEP_ID)
    {
      p_data[0] = eepromReadByte(EEP_ADDR_ID);
      p_ap->p_dxl_motor->id = p_data[0];
      dxlSetId(&p_ap->p_dxl_motor->node, p_ap->p_dxl_motor->id);
    }
  }

  if (mode == _UPDATE_RD)
  {
    if (addr == P_EEP_ID)
    {
      p_data[0] = eepromReadByte(EEP_ADDR_ID);
      p_ap->p_dxl_motor->id = p_data[0];
      dxlSetId(&p_ap->p_dxl_motor->node, p_ap->p_dxl_motor->id);
    }
  }

  if (mode == _UPDATE_WR)
  {
    if (addr == P_EEP_ID)
    {
      eepromWriteByte(EEP_ADDR_ID, p_data[0]);
      p_ap->p_dxl_motor->id = p_data[0];
      dxlSetId(&p_ap->p_dxl_motor->node, p_ap->p_dxl_motor->id);
    }
  }
}

static uint32_t getDxlBaud(uint8_t baud_index)
{
  uint32_t baud = 0;


  switch(baud_index)
  {
    case _DEF_DXL_BAUD_9600:
      baud = 9600;
      break;

    case _DEF_DXL_BAUD_57600:
      baud = 57600;
      break;

    case _DEF_DXL_BAUD_115200:
      baud = 115200;
      break;

    case _DEF_DXL_BAUD_1000000:
      baud = 1000000;
      break;

    case _DEF_DXL_BAUD_2000000:
      baud = 2000000;
      break;

    case _DEF_DXL_BAUD_3000000:
      baud = 3000000;
      break;

    case _DEF_DXL_BAUD_4000000:
      baud = 4000000;
      break;

    case _DEF_DXL_BAUD_4500000:
      baud = 4500000;
      break;

    default:
      baud = 1000000;
      break;
  }

  return baud;
}

void updateDxlBaud(uint32_t addr, uint8_t mode, uint16_t update_addr, uint8_t *p_data, uint16_t update_length)
{
  uint32_t baud = 0;

  if (mode == _UPDATE_INIT)
  {
    mode = _UPDATE_WR;
  }

  if (mode == _UPDATE_STARTUP)
  {
    p_data[0] = eepromReadByte(EEP_ADDR_BAUD);
    baud = getDxlBaud(p_data[0]);

    if (baud > 0)
    {
      eepromWriteByte(EEP_ADDR_BAUD, p_data[0]);

      p_ap->p_dxl_motor->baud = baud;
      dxlOpenPort(&p_ap->p_dxl_motor->node, p_ap->p_dxl_motor->ch, p_ap->p_dxl_motor->baud);
    }
  }

  if (mode == _UPDATE_RD)
  {
    p_data[0] = eepromReadByte(EEP_ADDR_BAUD);
  }

  if (mode == _UPDATE_WR)
  {
    baud = getDxlBaud(p_data[0]);

    if (baud > 0)
    {
      eepromWriteByte(EEP_ADDR_BAUD, p_data[0]);

      p_ap->p_dxl_motor->baud = baud;
      dxlOpenPort(&p_ap->p_dxl_motor->node, p_ap->p_dxl_motor->ch, p_ap->p_dxl_motor->baud);
    }
  }
}

void updateMillis(uint32_t addr, uint8_t mode, uint16_t update_addr, uint8_t *p_data, uint16_t update_length)
{
  data_t value;


  if (mode == _UPDATE_RD)
  {
    value.u32Data = millis();
    memcpy(p_data, &value.u8Data[update_addr], update_length);
  }
}

void updateVoltage(uint32_t addr, uint8_t mode, uint16_t update_addr, uint8_t *p_data, uint16_t update_length)
{
  data_t value;

  adcSetup(0);

  if (mode == _UPDATE_RD)
  {
    value.u32Data = adcConvVoltage(0, adcRead(0));
    memcpy(p_data, &value.u8Data[update_addr], update_length);

  }
}

void updateCurrent(uint32_t addr, uint8_t mode, uint16_t update_addr, uint8_t *p_data, uint16_t update_length)
{
  data_t value;

  adcSetup(1);

  if (mode == _UPDATE_RD)
  {
    value.u32Data = (currentRead0_1mA(1)/100);
    memcpy(p_data, &value.u8Data[update_addr], update_length);
  }
}