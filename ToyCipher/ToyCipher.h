#ifndef _TOY_CIPHER_H_
#define _TOY_CIPHER_H_

//inclusion des settings
#include"settings.h"

#pragma region Constant
#define SIZE_STATISTIC_TABLE 16

extern const byte ToysubBytesTab[16];
extern const byte ToysubBytesTab_inverse[16];
#pragma endregion

#pragma region Struct
/// @brief
typedef struct HPRD_s{
    /// @param index
    byte index;

    /// @param value
    unsigned int value;
} HPRD;

/// @brief
typedef struct Statistic_Table_S{
    /// @param n_key
    int n_key;

    /// @param coef 
    int coef;

    /// @param theGoodOne
    byte* theGoodOne;

    /// @param total_value
    unsigned int *total_value;

    /// @param hrpd
    HPRD **hrpd;
} Statistic_Table;
#pragma endregion

#pragma region Function
/// @brief 
/// @param n_key
/// @param coef 
/// @return 
Statistic_Table *Statistic_Table_create(int n_key, int coef);

/// @brief
/// @param statistic_table
void Statistic_Table_destroy(Statistic_Table* statistic_table);

/// @brief
/// @param a
/// @param b
/// @return 
int Statistic_Table_Compare(const void *a, const void *b);

/// @brief
/// @param nb
/// @return 
byte **ToyCipherKey_create(unsigned short nb);

/// @brief
/// @param key
/// @return 
int ToyCipherKey_permutation(byte *tab);

/// @brief
/// @param key
void ToyCipherKey_delete(byte **key);

/// @brief
/// @param tab
/// @return 
int ToyCipher_permutation(byte *tab);

/// @brief
/// @param tab
void ToyCipher_subBytes(byte *tab);

/// @brief
/// @param key
/// @return 
int ToyCipherKey_RoundKey(byte **key);

/// @brief
/// @param key
/// @param a
/// @param b
/// @param count
/// @return
byte **ToyCipher_GoodPair(unsigned short key, unsigned short a, unsigned short b, int *count);

/// @brief
/// @param message
/// @param key
/// @return
byte *ToyCipher_encrypt(unsigned short message, unsigned short key);

/// @brief Fonction renvoyant le ciphertext d'un plaintext apres un nombre r de round
/// @param plaintext Le message a chiffre
/// @param keys toutes les clefs ronde calculé ua préalable
/// @param r_Round Nombre de r_Round sachant que -1 est le rang initiale, et r apres le r round
/// @return le ciphertext
byte *ToyCipher_encryptRound(unsigned short plaintext, byte **keys, int r_Round);

/// @brief
/// @param text
/// @return 
int byte_affichage(byte *text);

/// @brief
/// @param size
/// @param key,
/// @param good_bit
/// @return 
unsigned short *ToyCipher_HPRD(int size, unsigned short key, byte *good_bit);

/// @brief
/// @param q
/// @param n_keys
/// @param C
void ToyCipher_Statistique(int q, int n_keys, int C);

/// @brief
/// @param a
/// @param b
/// @return 
int Bits_Identify(const byte a, const byte b);
#pragma endregion

#endif