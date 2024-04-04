#ifndef _AES_H_
#define _AES_H_

typedef unsigned char byte;

typedef byte (*mat_func[4][4])(byte);

typedef struct State_s {
    byte val[4][4];
} State;

typedef struct AES_128_s {
    State roundKeys[11];
} AES_128;

void addRoundKey(State *state, State *key);
void subBytes(State *state);
void shiftRows(State *state);
void mixColumns(State *state);

void invSubBytes(State *state);
void invShiftRows(State *state);
void invMixColumns(State *state);

void setCipherKey(AES_128 *aes, byte cipherKey[16]);
void encrypt128(AES_128 *aes, byte message[16]);
void decrypt128(AES_128 *aes, byte message[16]);

#endif