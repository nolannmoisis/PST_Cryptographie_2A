#ifndef _SBOX_H_
#define _SBOX_H_

#pragma region Inclue
#include "settings.h"
#pragma endregion

#pragma region Constant
/// @brief La S-Box correspondant à la permutation pour le chiffrement
extern const byte subBytesTab[16];
/// @brief Taille de la S_Box
extern const int S_BOX_SIZE;
#pragma endregion

#pragma region Function
/// @brief Fonction Remplissant une matrice
/// @return La matrice des DP de la S-Box
byte **SBox_DifferentialProbability(void);

/// @brief Lecture et affichage du fichier
/// @param DP La matrice des DP de la S-Box
/// @param filePath Chaine de caractere du fichier pour la lecture
void DP_FilePrint(byte **DP, char *filePath);

/// @brief Destruction de la matrice des DP
/// @param DP La matrice des DP de la S-Box
void DP_Delete(byte **DP);

/// @brief Lecture et affichage du fichier
/// @param LP La matrice des LP de la S-Box
/// @param filePath Chaine de caractere du fichier pour la lecture
void LP_FilePrint(byte **LP, char *filePath);

/// @brief Fait le produit scalaire de deux nombres
/// @param a Nombre a
/// @param b Nombre b
/// @return Le resultat du produit scalaire
int scalar(int a, int b);

/// @brief Fonction remplissant une matrice
/// @return La matrice des LP de la S-Box
byte **SBox_LinearProbability(void);

/// @brief Destruction de la matrice des LP
/// @param LP La matrice des LP de la S-Box
void LP_Delete(byte **LP);
#pragma endregion

#endif
