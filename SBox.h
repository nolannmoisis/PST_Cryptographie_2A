#ifndef _SBOX_H_
#define _SBOX_H_

#include "settings.h"
#include "Mini AES.h"

extern const int S_BOX_SIZE;

/// @brief Fonction Remplissant une matrice
/// @param  
/// @return La matrice des DP de la S-box
byte **SBox_DifferentialProbability(void);

/// @brief 
/// @param DP 
/// @param filePath 
void DP_FilePrint(byte **DP, char *filePath);

/// @brief 
/// @param DP 
void DP_Delete(byte **DP);

/// @brief 
/// @param a 
/// @param b 
/// @return 
int scalar(int a, int b);

/// @brief 
/// @param  
/// @return 
byte **SBox_LinearProbability(void);

#endif
