#ifndef _MINI_AES_H_
#define _MINI_AES_H_

//inclusion des settings
#include"settings.h"
#define SIZE_STATISTIC_TABLE 16

extern const byte ToysubBytesTab[16];
extern const byte ToysubBytesTab_inverse[16];

typedef struct HPRD_s{
    byte index;
    unsigned int value;
} HPRD;

typedef struct Statistic_Table_S{
    int n_key;
    int coef;
    byte* theGoodOne;
    unsigned int *total_value;
    HPRD **hrpd;
} Statistic_Table;

Statistic_Table *Statistic_Table_create(int n_key, int coef);
void Statistic_Table_destroy(Statistic_Table* statistic_table);
int Statistic_Table_Compare(const void *a, const void *b);

byte **ToyCipherKey_create(unsigned short nb);
int ToyCipherKey_permutation(byte *tab);
void ToyCipherKey_delete(byte **key);
int ToyCipher_permutation(byte *tab);
void ToyCipher_subBytes(byte *tab);
int ToyCipherKey_RoundKey(byte **key);
byte **ToyCipher_GoodPair(unsigned short key, unsigned short a, unsigned short b, int *count);
byte *ToyCipher_encrypt(unsigned short message, unsigned short key);

/// @brief Fonction renvoyant le ciphertext d'un plaintext apres un nombre r de round
/// @param plaintext Le message a chiffre
/// @param keys toutes les clefs ronde calculé ua préalable
/// @param r_Round Nombre de r_Round sachant que -1 est le rang initiale, et r apres le r round
/// @return le ciphertext
byte *ToyCipher_encryptRound(unsigned short plaintext, byte **keys, int r_Round);
int byte_affichage(byte *text);
unsigned short *ToyCipher_HPRD(int size, unsigned short key, byte *good_bit);
void ToyCipher_Statistique(int q, int n_keys, int C);

int Bits_Identify(const byte a, const byte b);

#endif