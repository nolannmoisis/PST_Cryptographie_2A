#ifndef _AES_H_
#define _AES_H_

#include "settings.h"

typedef unsigned char byte;

typedef byte (*mat_func[4][4])(byte);

typedef struct State_s {
    byte val[4][4];
} State;

typedef struct AES_128_s {
    State roundKeys[11];
} AES_128;

typedef struct Dimention_Biclique_s{
    byte ciphertext[16];
    byte sub_state[16];
    AES_128 keys;
} Dimention_Biclique;

typedef struct Inner_State_s {
    State inner[22];
}Inner_State;

void addRoundKey(State *state, State *key);
void subBytes(State *state);
void shiftRows(State *state);
void mixColumns(State *state);

void invSubBytes(State *state);
void invShiftRows(State *state);
void invMixColumns(State *state);

void setCipherKey(AES_128 *aes, byte cipherKey[16]);
void setCipherKey_inv(AES_128 *aes, byte cipherKey[16]);
void encrypt128(AES_128 *aes, byte message[16], Inner_State *all_state);
void f_encrypt128(AES_128 *aes, byte state[16], Inner_State *all_state);
void g_encrypt128(AES_128 *aes, byte plaintext[16], Inner_State *all_state);
void decrypt128(AES_128 *aes, byte message[16], Inner_State *all_state);

//Modification des clefs
void setCipherKey_delta_i(AES_128 *aes, byte i);
void setCipherKey_delta_j(AES_128 *aes, byte j);
void setCipherKeyRound(AES_128 *aes);
void setCipherKey_recomputeFrom8(AES_128 *aes);

Dimention_Biclique **D_Dimention_Biclique_create(byte initial_key[16]);

int is_equal(State state1, State state2);
Inner_State** function_f (Dimention_Biclique mat_key, byte** messages);

/// @brief Mise en place de l'attaque biclique en donnant la clef secrete
/// @param secret_key 
/// @return 
State Attaque_Biclique(AES_128 *secret_key);

#endif