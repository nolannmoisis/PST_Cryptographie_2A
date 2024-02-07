#ifndef _SBOX_H_
#define _SBOX_H_

#include "settings.h"
#include "Mini AES.h"

const int S_BOX_SIZE = 16;

/// @brief Fonction Remplissant une matrice
/// @param  
/// @return La matrice des DP de la S-box
byte **SBox_DifferentialProbability(void);

byte **SBox_LinearProbability(void);


#endif
