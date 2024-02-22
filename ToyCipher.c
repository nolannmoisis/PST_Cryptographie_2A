#include "ToyCipher.h"

byte *permutation (byte *tab)
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
    return tab;
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

int ToyCipherKey_permutation(byte **tab){

}

void ToyCipher_delete(byte **key){
    if(key){
        for(int i = 0; i < 6; i++){
            free(key[i]);
        }
        free(key);
    }
}
