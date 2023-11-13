#ifndef _MINI_AES_H_
#define _MINI_AES_H_

//inclusion des settings
#include"settings.h"

/// @brief Permet de transformer unsigned char en terme byte
typedef unsigned char byte;

/// @brief La S-Box correspondant à la permutation pour le chiffrement
extern const byte subBytesTab[16];
/// @brief La S-Box correspondant à la permutation pour le déchiffrement
extern const byte subBytesReverseTab[16];
/// @brief La S-Box correspondant au constant pour les calculs des clefs rondes
/*ki
    if(i == 0)  ki = 1
    else if (k(i-1) < 0x8)  ki = k(i-1) * 2
    else ki = ( 2 * k(i-1) ) ^ 0x13(00010011)*/
extern const byte constKey[16];

/// @brief Matrice des multiplications dans les corps fini case[3][2] est la multiplication de 0x3*0x3
extern const byte matrixMultiplication[16][3];
/// @brief Tableau du MixColums
extern const byte matrixMixColumns[4];

/// @brief Structure décrivant un message
typedef struct Message_s
{
    /// @brief La taille du message
    unsigned int size;

    /// @brief Le tableau comportant tout les termes héxadécimaux
    byte *tab;
} Message;

/// @brief Permet la vérification de l'existance du message
/// @param message Le message à vérifier
void checkMessage(Message *message);

/// @brief Consiste à appliquer une substitution à chacun des coefficients de la matrice (chiffrement)
/// @param message Le message que nous devons substituer
void subBytes(Message *message);

/// @brief Consiste à appliquer une substitution à chacun des coefficients de la matrice (déchiffrement)
/// @param message Le message que nous devons substituer
void subBytesReverse(Message *message);

/// @brief Effectue des décalages circulaires sur les lignes de la matrice (chiffrement)
/// @param message Le message que nous devons décaler circulairement
void shiftRows(Message *message);

/// @brief Effectue des décalages circulaires sur les lignes de la matrice (déchiffrement)
/// @param message Le message que nous devons décaler circulairement
void shiftRowsReverse(Message *message);

/// @brief Transforme chaque colonne en la multipliant par la matrice (chiffrement)
/// @param message Le message que nous devons transformer
void mixColumns(Message *message);

/// @brief Transforme chaque colonne en la multipliant par la matrice (déchiffrement)
/// @param message Le message que nous devons transformer
void mixColumnsReverse(Message *message);

/// @brief La fonction créer un tableau de clef ronde avec pour maximum 15 différente
/// @param initKey La clef initiale utilisé pour faire les autres clefs rondes
/// @param roundCount Le nombre de clef ronde à faire (<= 15)
/// @return Le tableau des clefs rondes
Message **createRoundKeys(Message *initKey, int roundCount);

/// @brief Ajoute terme à terme à l'état interne la clé de ronde
/// @param message Le message à chiffré
/// @param roundKey La clé de ronde
void addRoundKey(Message *message, Message *roundKey);

/// @brief La fonction permettant de chiffré en fonction du nombre de round
/// @param message Le message à chiffré
/// @param roundKey La clé de ronde
/// @param round Le nombre de ronde à faire
void encrypt(Message *message, Message **roundKey, int round);

/// @brief 
/// @param message 
/// @param roundKey 
/// @param round 
void decrypt(Message *message, Message **roundKey, int round);

/// @brief Permet de créer le message
/// @param path Le chemin vers l'instance du message à chiffré
/// @return Pointeur vers le message
Message *messageCreate(char *path);

/// @brief Permet de détruire le message
/// @param message Le message à détruire
void messageDestroy(Message** message);

/// @brief Permet de détruire les clefs rondes
/// @param roundCount nombre de tour effectuer
/// @param roundKeys Le tableau de clef round
void roundKeysDestroy(Message **roundKeys, int roundCount);

/// @brief Permet d'afficher le message
/// @param message Le messa à afficher
void messagePrint(Message* message);

#endif

