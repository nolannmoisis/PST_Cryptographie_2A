#include "ToyCipher.h"

const byte ToysubBytesTab[16] = {0x7, 0x3, 0xD, 0x9, 0xC, 0x2, 0x4, 0x8, 0xA, 0xB, 0x1, 0x0, 0xE, 0xF, 0x5, 0x6};

int ToyCipher_permutation (byte *tab)
{
    byte tmp[4];
    byte value;
    for (int i = 0; i < 4; i++)
    {
        tmp[i] = tab[i];
    }

    for (int i = 0; i < 4; i++)
    {
        value = 0;
        for (int j = 0; j < 4; j++)
        {
            value ^= (tmp[j] >> (3-i)) & 0b1;
            value = value << 1;
        }
        value = value & 0x1F;
        tab[i] = value >> 1;
    }
    return 0;
}

byte **ToyCipherKey_create(short nb){

    byte **key = (byte**)calloc(6, sizeof(byte*));

    if(!key){
        printf("ERROR Key Creation\n");
        assert(0);
    }

    for(int i = 0; i < 6; i++){
        key[i] = (byte*)calloc(4, sizeof(byte));
    }

    key[0][0] = (nb >> 12) & 0xF;
    key[0][1] = (nb >> 8) & 0xF;
    key[0][2] = (nb >> 4) & 0xF;
    key[0][3] = (nb >> 0) & 0xF;

    return key;
}

int ToyCipherKey_permutation(byte *key){
    unsigned short tmp[2] = {0, 0};

    tmp[0] = (key[0] << 12) ^ (key[1] << 8) ^ (key[2] << 4) ^ (key[3]);

    tmp[1] ^= tmp[0] << 5;
    tmp[1] ^= tmp[0] >> 11;

    key[0] = (tmp[1] >> 12) & 0xF;
    key[1] = (tmp[1] >> 8) & 0xF;
    key[2] = (tmp[1] >> 4) & 0xF;
    key[3] = (tmp[1] >> 0) & 0xF;

    return 0;
}

void ToyCipherKey_delete(byte **key){
    if(key){
        for(int i = 0; i < 6; i++){
            free(key[i]);
        }
        free(key);
    }
}

void ToyCipher_subBytes(byte *tab)
{
    // Parcours l'entièreté du message
    for(int i = 0; i < 4; i++){
        // Substitue l'élément i du message par celui du tableau subBytesTab
        tab[i] = ToysubBytesTab[(int)tab[i]];
    }
}

int ToyCipherKey_RoundKey(byte **key){
    if(!key){
        printf("ERROR Key\n");
        assert(0);
        return -1;
    }

    for(int i = 1; i < 6; i++){
        key[i][0] = ToysubBytesTab[key[i-1][0]];
        key[i][1] = key[i-1][1] ^ i;
        key[i][2] = key[i-1][2];
        key[i][3] = key[i-1][3];

        ToyCipherKey_permutation(key[i]);
    }

    return 0;
}

