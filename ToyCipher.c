#include "ToyCipher.h"

const byte subBytesTab[16] = {0x7, 0x3, 0xD, 0x9, 0xC, 0x2, 0x4, 0x8, 0xA, 0xB, 0x1, 0x0, 0xE, 0xF, 0x5, 0x6};

int ToyCipherKey_permutation (byte *tab)
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

void ToyCipher_subBytes(byte *tab)
{
    // Parcours l'entièreté du message
    for(int i = 0; i < 4; i++){
        // Substitue l'élément i du message par celui du tableau subBytesTab
        tab[i] = subBytesTab[(int)tab[i]];
    }
}