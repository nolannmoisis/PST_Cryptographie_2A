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

/// @brief Ajoute terme à terme à l'état interne la clé de ronde
/// @param message Le message à chiffré
/// @param roundKey La clé de ronde
void addRoundKey(Message *message, Message *roundKey);

/// @brief La fonction permettant de chiffré en fonction du nombre de round
/// @param message Le message à chiffré
/// @param roundKey La clé de ronde
/// @param round Le nombre de ronde à faire
void encrypt(Message *message, Message *roundKey, int round);

/// @brief Permet de créer le message
/// @param path Le chemin vers l'instance du message à chiffré
/// @return Pointeur vers le message
Message *messageCreate(char *path);

/// @brief Permet de détruire le message
/// @param message Le message à détruire
void messageDestroy(Message** message);

/// @brief Permet d'afficher le message
/// @param message Le messa à afficher
void messagePrint(Message* message);

#endif

