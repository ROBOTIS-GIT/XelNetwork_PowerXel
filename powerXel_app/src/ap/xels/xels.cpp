/*
 * xels.cpp
 *
 *  Created on: 2018. 8. 24.
 *      Author: HanCheol Cho
 */




#include "xels.h"
#include "dxl/dxl.h"
#include "current/current.h"



static XelNetwork::XelHeader_t xel_header = {
      XelNetwork::DataType::POWER,
      1,
      "power",
      XelNetwork::SEND,
      128,
      8
  };

static xel_data_type_t xel_data;



void xelsInitCallback(uint8_t ch);



void xelsInit(void)
{
  XelNetwork::XelHeader_t *p_xel_header;


  p_xel_header = &xel_header;

  p_xel_header->data_type            = XelNetwork::DataType::POWER;
  p_xel_header->data_get_interval_hz = 1;
  p_xel_header->data_direction       = XelNetwork::SEND;
  p_xel_header->data_addr            = 128;
  p_xel_header->data_length          = xelsGetDataTypeLength(p_xel_header->data_type);

  strcpy(p_xel_header->data_name, "power");

  xelsInitCallback(0);
}

XelNetwork::XelHeader_t * xelsGetHeader(uint8_t ch)
{
  return &xel_header;
}

uint8_t xelsGetDataTypeLength(uint8_t data_type)
{
  uint8_t ret = 0;


  switch(data_type)
  {
    case XelNetwork::BOOLEAN:
    case XelNetwork::CHAR:
    case XelNetwork::INT8:
    case XelNetwork::UINT8:
      ret = 1;
      break;
    case XelNetwork::INT16:
    case XelNetwork::UINT16:
      ret = 2;
      break;
    case XelNetwork::INT32:
    case XelNetwork::UINT32:
    case XelNetwork::FLOAT32:
      ret = 4;
      break;
    case XelNetwork::INT64:
    case XelNetwork::UINT64:
    case XelNetwork::FLOAT64:
    case XelNetwork::POWER:
      ret = 8;
      break;
    default:
      ret = 4;
      break;
  }

  return ret;
}

void xelsInitCallback(uint8_t ch)
{
  XelNetwork::XelHeader_t *p_xel_header;
  uint8_t data_type;

  p_xel_header = xelsGetHeader(ch);

  data_type = p_xel_header->data_type;
  switch(data_type)
  {
    default:
      break;
  }
}

void xelsReadCallback(uint8_t ch, uint16_t addr, uint8_t *p_data, uint16_t length)
{
  XelNetwork::XelHeader_t *p_xel_header;
  uint8_t data_type;

  p_xel_header = xelsGetHeader(ch);

  data_type = p_xel_header->data_type;
  switch(data_type)
  {
    case XelNetwork::MILLIS:
      xel_data.MILLIS = millis();
      break;

    case XelNetwork::POWER:
      xel_data.POWER.voltage = (uint32_t)adcConvVoltage(0, adcRead(0));
      xel_data.POWER.current = (uint32_t)currentRead0_1mA(1)/100;
      break;
  }

  memcpy(p_data, &xel_data.u8Data[addr], length);
}

void xelsWriteCallback(uint8_t ch, uint16_t addr, uint8_t *p_data, uint16_t length)
{
  XelNetwork::XelHeader_t *p_xel_header;
  uint8_t data_type;


  p_xel_header = xelsGetHeader(ch);
  memcpy(&xel_data.u8Data[addr], p_data, length);


  data_type = p_xel_header->data_type;
  switch(data_type)
  {
    case XelNetwork::BOOLEAN:
      if (xel_data.BOOLEAN == 0)
      {
        ledOff(_DEF_LED1);
      }
      else
      {
        ledOn(_DEF_LED1);
      }
      break;
  }
}

