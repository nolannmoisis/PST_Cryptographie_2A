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
            value += tmp[j] & (0b1 << (3-i));
            value = value << 1;
        }
        tab[i] = value >> 1;
    }
    return tab;
}