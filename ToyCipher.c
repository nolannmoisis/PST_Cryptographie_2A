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

byte **ToyCipherKey_create(byte a, byte b, byte c, byte d){
    a = a & 0xF;
    b = b & 0xF;
    c = c & 0xF;
    d = d & 0xF;

    byte **key = (byte**)calloc(6, sizeof(byte*));

    if(!key){
        printf("ERROR Key Creation\n");
        assert(0);
    }

    for(int i = 0; i < 6; i++){
        key[i] = (byte*)calloc(4, sizeof(byte));
    }

    key[0][0] = a;
    key[0][1] = b;
    key[0][2] = c;
    key[0][3] = d;

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

void ToyCipher_delete(byte **key){
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
