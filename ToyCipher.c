#include "ToyCipher.h"

const byte ToysubBytesTab[16] = {0x7, 0x3, 0xD, 0x9, 0xC, 0x2, 0x4, 0x8, 0xA, 0xB, 0x1, 0x0, 0xE, 0xF, 0x5, 0x6};
const byte ToysubBytesTab_inverse[16] = {0xB, 0xA, 0x5, 0x1, 0x6, 0xE, 0xF, 0x0, 0x7, 0x3, 0x8, 0x9, 0x4, 0x2, 0xC, 0xD};

int byte_affichage(byte *text){
    if(!text){
        printf("ERROR TEXT\n");
        assert(0);
        return -1;
    }

    for(int i = 0; i < 4; i++){
        if (text[i] < 10){
            printf("[%d] ", text[i]);
        }
        else{
            printf("[%c] ", text[i] + 'A' - 10);
        }
    }
    printf("\n");
    return 0;
}

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

byte **ToyCipherKey_create(unsigned short nb){

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

byte *ToyCipher_encrypt(unsigned short message, unsigned short key){
    byte *encrypt = (byte*)calloc(4, sizeof(byte));

    encrypt[0] = (message >> 12) & 0xF;
    encrypt[1] = (message >> 8) & 0xF;
    encrypt[2] = (message >> 4) & 0xF;
    encrypt[3] = (message >> 0) & 0xF;

    byte **keys = ToyCipherKey_create(key);

    if(ToyCipherKey_RoundKey(keys))
        assert(0);

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 4; j++){
            encrypt[j] ^= keys[i][j];
        }
        ToyCipher_subBytes(encrypt);
        if(i != 4)
            ToyCipher_permutation(encrypt);
    }

    for(int j = 0; j < 4; j++){
        encrypt[j] ^= keys[5][j];
    }

    ToyCipherKey_delete(keys);

    return encrypt;
}

byte **ToyCipher_GoodPair(unsigned short key, unsigned short a, unsigned short b, int *count){
    byte **pairs = (byte**)calloc(1, sizeof(byte*));
    byte b0[4] = {(b >> 12) & 0xF, (b >> 8) & 0xF, (b >> 4) & 0xF, b & 0xF};

    byte **keys = ToyCipherKey_create(key);
    byte *x0 = NULL, *x1 = NULL;
    int max_capacity = 1;
    unsigned short tmp;
    *count = 0;

    if(ToyCipherKey_RoundKey(keys)){
        printf("ERROR KEYS INIT\n");
        assert(0);
    }

    for(int i = 0; i < (1 << 16); i++){
        x0 = ToyCipher_encryptRound((unsigned short)i, keys, 5);
        x1 = ToyCipher_encryptRound((unsigned short)(i ^ a), keys, 5);
        bool good = true;

        for(int j = 0; (j < 4) && good; j++){
            tmp = (x0[j] ^ b0[j]) & 0xF;
            if(tmp != (x1[j] & 0xF)){
                good = false;
            }
        }

        if(good){
            //Augmentation du tableau de bonnes pairs si besoin
            if((*count) == max_capacity){
                pairs = (byte**)realloc(pairs, (++max_capacity) * sizeof(byte*));
            }

            // byte *new_byte = (byte*)calloc(4, sizeof(byte));
            
            // new_byte[0] = (i >> 12) & 0xF;
            // new_byte[1] = (i >> 8) & 0xF;
            // new_byte[2] = (i >> 4) & 0xF;
            // new_byte[3] = i & 0xF;

            // pairs[*count] = new_byte;
            pairs[*count] = x0;
            (*count)++;
        }
        else{
            free(x0);
        }
        // free(x0);
        free(x1);
    }

    ToyCipherKey_delete(keys);

    return pairs;
}

byte *ToyCipher_encryptRound(unsigned short plaintext, byte **keys, int r_Round){
    //vérification des paramtètres initiaux
    if(!keys){
        printf("ERROR KEYS NULL\n");
        assert(0);
    }

    int round;
    r_Round++;

    byte *ciphertext = (byte*)calloc(4, sizeof(byte));

    if(!ciphertext){
        free(ciphertext);
        printf("ERROR Allocation\n");
        assert(0);
    }

    //Initialisation du tableau de base
    ciphertext[0] = (plaintext >> 12) & 0xF;
    ciphertext[1] = (plaintext >> 8) & 0xF;
    ciphertext[2] = (plaintext >> 4) & 0xF;
    ciphertext[3] = (plaintext >> 0) & 0xF;

    for(round = 0; round < 5; round++){
        if(r_Round == round)
            return ciphertext;

        //Changement à la clef round + 1
        for(int j = 0; j < 4; j++){
            ciphertext[j] ^= keys[round][j];
        }
        ToyCipher_subBytes(ciphertext);

        if(round != 4)
            ToyCipher_permutation(ciphertext);
    }

    if(round == r_Round)
        return ciphertext;

    for(int j = 0; j < 4; j++){
        ciphertext[j] ^= keys[round][j];
    }

    return ciphertext;
}

unsigned short *ToyCipher_HPRD(byte **pairs, unsigned short b, int size)
{
    unsigned short *HPRD = (unsigned short*)calloc(1 << 16, sizeof(unsigned short));

    byte y0[4], y1[4];

    //Parcours de toutes les clefs
    for(int i = 0; i < (1 << 16); i++){
        //Parcours de toutes les bonnes paires
        for(int pairs_size = 0; pairs_size < 4*(int)((float)(1 << 16) / size); pairs_size++){
            bool good = true;
            int diff;

            for(byte j = 0; j < 4 && good; j++){
                diff = 4*(3-j);
                y0[j] = pairs[pairs_size][j];
                y1[j] = pairs[pairs_size][j] ^ ((b >> diff) & 0xF);

                y0[j] ^= (i >> diff) & 0xF;
                y1[j] ^= (i >> diff) & 0xF;

                y0[j] = ToysubBytesTab_inverse[y0[j]];
                y1[j] = ToysubBytesTab_inverse[y1[j]];

                if((y0[j] ^ y1[j]) != ((b >> diff) & 0xF)){
                    good = false;
                }
            }

            if(good){
                HPRD[i]++;
            }

        }   
    }

    return HPRD;
}
