#ifndef _SBOX_H_
#define _SBOX_H_

#include "settings.h"
#include "Mini AES.h"

byte **SBox_DifferentialProbability(void);

byte **SBox_LinearProbability(void);


#endif
