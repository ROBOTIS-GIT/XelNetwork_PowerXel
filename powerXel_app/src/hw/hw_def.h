/*
 *  hw_def.h
 *
 *  Created on: 2016. 5. 14.
 *      Author: Baram
 */





#ifndef HW_DEF_H
#define HW_DEF_H

#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

#include "def.h"
#include "error_code.h"


#ifndef BOOL
#define BOOL uint8_t
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef bool
#define bool uint8_t
#endif

#ifndef true
#define true  1
#endif

#ifndef false
#define false 0
#endif



#define _USE_HW_LED
#define _USE_HW_BUTTON
#define _USE_HW_ADC
#define _USE_HW_TIMER
#define _USE_HW_UART
#define _USE_HW_RESET
#define _USE_HW_TIMER
#define _USE_HW_SW_TIMER
#define _USE_HW_EEPROM
#define _USE_HW_FLASH

#define _USE_HW_DXLPORT
#define _USE_HW_DXLCMD
#define _USE_HW_DXL

#define _USE_HW_CTABLE


#define _HW_DEF_CMDIF_LIST_MAX                32

#define _HW_DEF_DXLCMD_MAX_NODE               32
#define _HW_DEF_DXLCMD_MAX_NODE_BUFFER_SIZE   32
#define _HW_DEF_DXLCMD_BUFFER_MAX             1024
#define _HW_DEF_DXL_MAX_BUFFER                (1024+10)

#define _HW_DEF_LED_CH_MAX                    1
#define _HW_DEF_BUTTON_CH_MAX                 1
#define _HW_DEF_ADC_CH_MAX                    2
#define _HW_DEF_UART_CH_MAX                   1
#define _HW_DEF_DXLPORT_CH_MAX                1
#define _HW_DEF_TIMER_CH_MAX                  1



#endif

