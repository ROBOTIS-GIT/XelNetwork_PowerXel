/*
 * current.h
 *
 *  Created on: 2018. 3. 29.
 *      Author: D.ggavy
 */

#ifndef SRC_AP_CURRENT_CURRENT_H_
#define SRC_AP_CURRENT_CURRENT_H_

#ifdef __cplusplus
 extern "C" {
#endif



#include "ap.h"

typedef struct Power
{
   double voltage;
   double current;
}Power_t;



uint16_t currentRead0_1mA(uint8_t ch);


#ifdef __cplusplus
 }
#endif



#endif /* SRC_AP_CURRENT_CURRENT_H_ */
