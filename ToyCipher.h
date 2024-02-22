#ifndef _MINI_AES_H_
#define _MINI_AES_H_

//inclusion des settings
#include"settings.h"

byte *permutation (byte *tab);

byte *ToyCipherKey_create(byte a, byte b, byte c, byte d);
byte *ToyCipherKey_permutation(byte *tab);

#endif