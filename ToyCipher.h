#ifndef _MINI_AES_H_
#define _MINI_AES_H_

//inclusion des settings
#include"settings.h"

extern const byte ToysubBytesTab[16];

byte **ToyCipherKey_create(short nb);
int ToyCipherKey_permutation(byte *tab);
void ToyCipherKey_delete(byte **key);
int ToyCipher_permutation(byte *tab);
void ToyCipher_subBytes(byte *tab);
int ToyCipherKey_RoundKey(byte **key);

#endif