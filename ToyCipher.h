#ifndef _MINI_AES_H_
#define _MINI_AES_H_

//inclusion des settings
#include"settings.h"

extern const byte ToysubBytesTab[16];

byte **ToyCipherKey_create(unsigned short nb);
int ToyCipherKey_permutation(byte *tab);
void ToyCipherKey_delete(byte **key);
int ToyCipher_permutation(byte *tab);
void ToyCipher_subBytes(byte *tab);
int ToyCipherKey_RoundKey(byte **key);
byte **ToyCipher_GoodPair();
byte *ToyCipher_encrypt(unsigned short message, unsigned short key);

/// @brief Fonction renvoyant le ciphertext d'un plaintext apres un nombre r de round
/// @param plaintext Le message a chiffre
/// @param keys toutes les clefs ronde calculé ua préalable
/// @param r_Round Nombre de r_Round sachant que -1 est le rang initiale, et r apres le r round
/// @return le ciphertext
byte *ToyCipher_encryptRound(unsigned short plaintext, byte **keys, int r_Round);
int byte_affichage(byte *text);

#endif