#ifndef _MINI_AES_H_
#define _MINI_AES_H_

//inclusion des settings
#include"settings.h"

extern const byte subBytesTab[16];

byte **ToyCipherKey_create(byte a, byte b, byte c, byte d);
void ToyCipher_delete(byte **key);
int ToyCipherKey_permutation(byte *tab);
void ToyCipher_subBytes(byte *tab);

#endif