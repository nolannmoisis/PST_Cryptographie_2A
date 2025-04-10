#include "ToyCipher.h"

const byte ToysubBytesTab[16] = {0x7, 0x3, 0xD, 0x9, 0xC, 0x2, 0x4, 0x8, 0xA, 0xB, 0x1, 0x0, 0xE, 0xF, 0x5, 0x6};
const byte ToysubBytesTab_inverse[16] = {0xB, 0xA, 0x5, 0x1, 0x6, 0xE, 0xF, 0x0, 0x7, 0x3, 0x8, 0x9, 0x4, 0x2, 0xC, 0xD};

int Statistic_Table_Compare(const void *a, const void *b){
    HPRD *x = (HPRD*)a;
    HPRD *y = (HPRD*)b;
    return y->value - x->value;
}

int Bits_Identify(const byte a, const byte b){
    int count = 0;
    byte n = a ^ b;
    n = ~n;
    for(int i = 0; i < 4; i++){
        if(n & 0b1)
            count++;
        n = n >> 1;
    }
    return count;
}

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

unsigned short *ToyCipher_HPRD(int size, unsigned short key, byte *good_bit)
{
    unsigned short *HPRD = (unsigned short*)calloc(1 << 4, sizeof(unsigned short));

    byte **keys = ToyCipherKey_create(key);
    ToyCipherKey_RoundKey(keys);

    //byte K[4] = {0};

    *good_bit = keys[5][1];

    // printf("good key %x\n", keys[5][1]);
    
    //Parcours de toutes les bonnes paires
    for(int pairs_size = 0; pairs_size < size; pairs_size++){

        unsigned short x0 = rand() & 0xFFFF;
        unsigned short x1 = x0 ^ 0x0400;

        byte *c0 = ToyCipher_encryptRound(x0, keys, 5);
        byte *c1 = ToyCipher_encryptRound(x1, keys, 5);
        bool good = true;

        if ((c0[0] ^ c1[0]) != 0) good = false;
        if ((c0[2] ^ c1[2]) != 0) good = false;
        if ((c0[3] ^ c1[3]) != 0) good = false;

        byte d = c0[1] ^ c1[1];
        if (d != 0x1 && d != 0x4 && d != 0x6 && d != 0x9 && d != 0xB) good = false;

        if (good)
        {
            //Parcours de toutes les clefs
            for(int k1 = 0; k1 < (1 << 4); k1++){
                byte z01 = c0[1] ^ k1;
                byte z11 = c1[1] ^ k1;
                byte y01 = ToysubBytesTab_inverse[z01];
                byte y11 = ToysubBytesTab_inverse[z11];

                if ((y01 ^ y11) == 0x4)
                {
                    HPRD[k1]++;
                }
            }
        }

        free(c0);
        free(c1);
    }

    ToyCipherKey_delete(keys);

    // for (int k = 0; k < (1 << 4); k++)
    // {
    //     printf("key = %x, score = %d\n", k, HPRD[k]);
    // }

    return HPRD;
}

Statistic_Table *Statistic_Table_create(int n_key, int coef){
    Statistic_Table* tab = (Statistic_Table*)calloc(1, sizeof(Statistic_Table));

    tab->coef = coef;
    tab->n_key = n_key;

    tab->total_value = (unsigned int*)calloc(n_key, sizeof(unsigned int));
    tab->theGoodOne = (byte*)calloc(n_key, sizeof(byte));

    tab->hrpd = (HPRD**)calloc(n_key, sizeof(HPRD*));

    for (int i = 0; i < n_key; i++){
        tab->hrpd[i] = (HPRD*)calloc(SIZE_STATISTIC_TABLE, sizeof(HPRD));

        for (int j = 0; j < SIZE_STATISTIC_TABLE; j++){
            tab->hrpd[i][j].index = j;
        }
    }
    
    return tab;
}

void Statistic_Table_destroy(Statistic_Table* statistic_table){
    free(statistic_table->theGoodOne);
    free(statistic_table->total_value);
    for(int i = 0; i < statistic_table->n_key; i++){
        free(statistic_table->hrpd[i]);
    }
    free(statistic_table->hrpd);
    free(statistic_table);
}

void ToyCipher_Statistique(int q, int n_keys, int C){
    if(!C || !q){
        printf("0 keys\n");
        return;
    }

    Statistic_Table *statistic_table = Statistic_Table_create(n_keys, C);
    float statistique[4] = {0.0f};
    float bits_identify_count[4] = { 0.0f };

    for(int i = 0; i < statistic_table->n_key; i++){
        unsigned short *buffer = ToyCipher_HPRD(q * statistic_table->coef, (unsigned short)( rand() % (1 << SIZE_STATISTIC_TABLE) ), &statistic_table->theGoodOne[i]);
        unsigned int total = 0;
        for(int j = 0; j < SIZE_STATISTIC_TABLE; j++){
            statistic_table->hrpd[i][j].value = buffer[j];
            total += buffer[j];
        }
        free(buffer);
        statistic_table->total_value[i] = total;
        qsort(statistic_table->hrpd[i], SIZE_STATISTIC_TABLE, sizeof(HPRD), Statistic_Table_Compare);
        for(int j = 0; j < SIZE_STATISTIC_TABLE; j++){
            if(statistic_table->hrpd[i][j].index == statistic_table->theGoodOne[i]){
                switch (j)
                {
                case 0:
                case 1:
                case 2:
                case 3:
                    statistique[0] += 1.0f/statistic_table->n_key;
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                    statistique[1] += 1.0f/statistic_table->n_key;
                    break;
                case 8:
                case 9:
                case 10:
                case 11:
                    statistique[2] += 1.0f/statistic_table->n_key;
                    break;
                default:
                    statistique[3] += 1.0f/statistic_table->n_key;
                    break;
                }
            }
        }
        int n = Bits_Identify(statistic_table->hrpd[i][0].index , statistic_table->theGoodOne[i]);

        switch (n)
        {
        case 4:
            bits_identify_count[3] += 1.0f/statistic_table->n_key;
        case 3:
            bits_identify_count[2] += 1.0f/statistic_table->n_key;
        case 2:
            bits_identify_count[1] += 1.0f/statistic_table->n_key;
        case 1:
            bits_identify_count[0] += 1.0f/statistic_table->n_key;
            break;
        default:
            break;
        }
    }
    printf("Proportion : (C = %d, Number Keys = %d)\n", statistic_table->coef, statistic_table->n_key);
    for (int i = 0, proportion = 100; i < 4; i++, proportion -= 25){
        printf("\t%d - %d%%    \t: %.1f%%\n", proportion, proportion - 25, 100 * statistique[i]);
    }
    printf("\n");
    for(int i = 3; i > -1; i--){
        printf("\t%d Bits identify\t: %.1f%%\n", i + 1, 100 * bits_identify_count[i]);
    }
    
    Statistic_Table_destroy(statistic_table);
}
