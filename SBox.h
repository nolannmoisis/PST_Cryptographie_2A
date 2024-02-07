#ifndef _SBOX_H_
#define _SBOX_H_

#include "settings.h"
#include "Mini AES.h"

extern const int S_BOX_SIZE;

/// @brief Fonction Remplissant une matrice
/// @param  
/// @return La matrice des DP de la S-box
byte **SBox_DifferentialProbability(void);

void DP_FilePrint(byte **DP, char *filePath);

void DP_Delete(byte **DP);

byte **SBox_LinearProbability(void);


#endif
