#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AES.h"

static byte sBox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

static byte invSBox[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

byte times01(byte x){
    return x;
}

byte times02(byte x)
{
    if (x & 0x80)
        return (x << 1) ^ 0x1B;
    else
        return (x << 1);
}

byte times03(byte x)
{
    return x ^ times02(x);
}

byte times0E(byte x) {
    return times02(times02(times02(x))) ^ times02(times02(x)) ^ times02(x);
}

byte times0B(byte x) {
    return times02(times02(times02(x))) ^ times02(x) ^ times01(x);
}

byte times0D(byte x) {
    return times02(times02(times02(x))) ^ times02(times02(x)) ^ x;
}

byte times09(byte x) {
    return times02(times02(times02(x))) ^ times01(x);
}

void addRoundKey(State *state, State *key)
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            state->val[i][j] ^= key->val[i][j];
        }
    }
}

Mat_Keys Matrice_Keys_create(byte initial_key[16]){
    Mat_Keys mat_keys;

    for(int i = 0; i < 256; i++){
        for(int j = 0; j < 256; j++){
            for(int c = 0; c < 16; c++){
                mat_keys.key[i][j][c] = initial_key[c];
                if(c == 1)
                    mat_keys.key[i][j][c] = (char)i;
                else if (c == 12)
                    mat_keys.key[i][j][c] = (char)j;
            }
        }
    }

    return mat_keys;
}

//Fonction du encrypt
void subBytes(State *state){
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            state->val[i][j] = sBox[state->val[i][j]];
        }
    }
}

void shiftRows(State *state){
    int i, j;
    for (i = 1; i < 4; i++)
    {
        byte tmp[4];
        for (j = 0; j < 4; j++)
        {
            tmp[j] = state->val[i][(j+i)%4];
        }
        for (j = 0; j < 4; j++)
        {
            state->val[i][j] = tmp[j];
        }
    }
}

void mixColumns(State *state){
    mat_func mat = {    {times02, times03, times01, times01}, 
                        {times01, times02, times03, times01},
                        {times01, times01, times02, times03}, 
                        {times03, times01, times01, times02}};

    int i, j, k;
    for(i = 0; i < 4; i++){
        byte tmp[4];
        for(j = 0; j < 4; j++){
            tmp[j] = 0;
            for(k = 0; k < 4; k++){
                tmp[j] ^= mat[j][k](state->val[k][i]);
            }
        }
        for(j = 0; j < 4; j++){
            state->val[j][i] = tmp[j];
        }
    }
}

//Fonction du decrypt
void invSubBytes(State *state){
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            state->val[i][j] = invSBox[state->val[i][j]];
        }
    }
}

void invShiftRows(State *state){
    int i, j;
    for (i = 1; i < 4; i++)
    {
        byte tmp[4];
        for (j = 0; j < 4; j++)
        {
            tmp[(j+i)%4] = state->val[i][j];
        }
        for (j = 0; j < 4; j++)
        {
            state->val[i][j] = tmp[j];
        }
    }
}

void invMixColumns(State *state){
    mat_func inv_mat = { {times0E, times0B, times0D, times09},
                         {times09, times0E, times0B, times0D},
                         {times0D, times09, times0E, times0B},
                         {times0B, times0D, times09, times0E} };

    int i, j, k;
    for (i = 0; i < 4; i++) {
        byte tmp[4];
        for (j = 0; j < 4; j++) {
            tmp[j] = 0;
            for (k = 0; k < 4; k++) {
                tmp[j] ^= inv_mat[j][k](state->val[k][i]);
            }
        }
        for (j = 0; j < 4; j++) {
            state->val[j][i] = tmp[j];
        }
    }
}

//Fonction pour les clefs de chiffrement
void setCipherKey(AES_128 *aes, byte cipherKey[16]){
    int i, j, k;

    //Initialisation de la première clef
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            aes->roundKeys[0].val[j][i] = cipherKey[4*i+j];
        }
    }

    //Création de la variable (02)^(i-1)
    byte var = 0x01;
    //Création des autres clef
    for(k = 1; k < 11; k++){
        //Mise à jour des constantes
        byte x[4];
        for(i = 0; i < 4; i++){
            x[i] = aes->roundKeys[k-1].val[(i+1)%4][3];
            x[i] = sBox[x[i]];
        }
        x[0] ^= var;
        var = (var < 0x80) ? (var << 1) : (var << 1) ^ 0x11B;  

        for(i = 0; i < 4; i++){
            aes->roundKeys[k].val[i][0] = aes->roundKeys[k-1].val[i][0] ^ x[i];
        }

        for(i = 1; i < 4; i++){
            for(j = 0; j < 4; j++){
                aes->roundKeys[k].val[j][i] = aes->roundKeys[k-1].val[j][i] ^ aes->roundKeys[k].val[j][i-1];
            }
        }
    }
}

void setCipherKey_delta_i(AES_128 *aes, byte i){
    aes->roundKeys[8].val[0][2] ^= i;
    aes->roundKeys[8].val[0][3] ^= i;
}

void setCipherKey_delta_j(AES_128 *aes, byte j){
    aes->roundKeys[8].val[1][0] ^= j;
    aes->roundKeys[8].val[1][2] ^= j;
}

void setCipherKeyRound(AES_128 *aes){
    int k, i, j;
    //Création de la variable (02)^(i-1)
    byte var = 0x1B;
    //Création des autres clef
    for(k = 9; k < 11; k++){
        //Mise à jour des constantes
        byte x[4];
        for(i = 0; i < 4; i++){
            x[i] = aes->roundKeys[k-1].val[(i+1)%4][3];
            x[i] = sBox[x[i]];
        }
        x[0] ^= var;
        var = (var < 0x80) ? (var << 1) : (var << 1) ^ 0x11B;  

        for(i = 0; i < 4; i++){
            aes->roundKeys[k].val[i][0] = aes->roundKeys[k-1].val[i][0] ^ x[i];
        }

        for(i = 1; i < 4; i++){
            for(j = 0; j < 4; j++){
                aes->roundKeys[k].val[j][i] = aes->roundKeys[k-1].val[j][i] ^ aes->roundKeys[k].val[j][i-1];
            }
        }
    }
}

void encrypt128(AES_128 *aes, byte message[16], Inner_State *all_state){
    State *cur_state = (State*)malloc(sizeof(State));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cur_state->val[j][i] = message[4*i+j];
        }
    }

    all_state->inner[0] = *cur_state;
    addRoundKey(cur_state, &aes->roundKeys[0]);
    
    all_state->inner[1] = *cur_state;

    for (int i = 1, k = 2; i < 10; i++)
    {
        subBytes(cur_state);
        
        shiftRows(cur_state);

        mixColumns(cur_state);

        all_state->inner[k++] = *cur_state;
        addRoundKey(cur_state, &aes->roundKeys[i]);

        all_state->inner[k++] = *cur_state;
    }

    subBytes(cur_state);
    shiftRows(cur_state);
    all_state->inner[20] = *cur_state;
    addRoundKey(cur_state, &aes->roundKeys[10]);
    all_state->inner[21] = *cur_state;
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            message[4*i+j] = cur_state->val[j][i];
        }
    }
    free(cur_state);
}

void decrypt128(AES_128 *aes, byte message[16], Inner_State *all_state){
    State *cur_state = (State*)malloc(sizeof(State));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cur_state->val[j][i] = message[4*i+j];
        }
    }

    all_state->inner[21] = *cur_state;
    addRoundKey(cur_state, &aes->roundKeys[10]);
    all_state->inner[20] = *cur_state;

    invShiftRows(cur_state);
    invSubBytes(cur_state);
    all_state->inner[19] = *cur_state;

    for (int i = 9, k = 18; i > 0; i--)
    {
        addRoundKey(cur_state, &aes->roundKeys[i]);
        all_state->inner[k--] = *cur_state;
        
        invMixColumns(cur_state);

        invShiftRows(cur_state);

        invSubBytes(cur_state);

        all_state->inner[k--] = *cur_state;
    }

    addRoundKey(cur_state, &aes->roundKeys[0]);
    all_state->inner[0] = *cur_state;
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            message[4*i+j] = cur_state->val[j][i];
        }
    }
    free(cur_state);
}
