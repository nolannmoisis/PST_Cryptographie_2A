#include "AES.h"
#include "settings.h"

int main(int argc, char** argv){
    byte initial_key[16] = { 0xf, 0, 2, 2, 5, 6 ,8, 7, 6, 3, 0, 0xd, 0, 5, 6, 0xe };
    Dimention_Biclique **d_dimention_biclique = D_Dimention_Biclique_create(initial_key);

    for(int i = 0; i < 256; i++)
        free(d_dimention_biclique[i]);
    free(d_dimention_biclique);

    /*AES_128 *aes_128 = (AES_128*)malloc(sizeof(AES_128));

    byte cipherkey[16] = { 0 };

    setCipherKey(aes_128, cipherkey);
    
    /*AES_128 *key_0 = (AES_128*)malloc(sizeof(AES_128));
    AES_128 *key_1 = (AES_128*)malloc(sizeof(AES_128));
    AES_128 *key_2 = (AES_128*)malloc(sizeof(AES_128));

    Inner_State *inner_state_0 = (Inner_State*)malloc(sizeof(Inner_State));
    Inner_State *inner_state_1 = (Inner_State*)malloc(sizeof(Inner_State));
    Inner_State *inner_state_2 = (Inner_State*)malloc(sizeof(Inner_State));

    //Ciphertext C = 00000000000000000000000000000000
    byte C00[16] = {0};
    byte C01[16] = {0};
    byte P[16] = {0};

    //Bonne clef key = 1f 00 00 00      00 00 00 00     00 00 00 00     10 00 00 00
    //  0x1f, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
    byte Key_0[16] = { 0x1f, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    byte Key_1[16] = { 0x1f, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    byte Key_2[16] = { 0x1f, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    setCipherKey(key_0, Key_0);
    setCipherKey(key_1, Key_1);
    setCipherKey(key_2, Key_2);

    setCipherKey_delta_i(key_1, 0xAB);
    setCipherKey_delta_j(key_2, 0xAA);

    setCipherKeyRound(key_1);
    setCipherKeyRound(key_2);

    decrypt128(key_0, C00, inner_state_0);
    decrypt128(key_2, C01, inner_state_2);

    for(int i = 0; i < 16; i++)
        P[i] = C00[i];

    encrypt128(key_1, P, inner_state_1);

    // printf("Key :\n");
    // for(int k = 0; k < 11; k++){
    //     for(int i = 0; i < 4; i++){
    //         for(int j = 0; j < 4; j++){
    //             if((key_0->roundKeys[k].val[i][j]&0xF0) == 0x00)
    //                 printf("[0");
    //             else
    //                 printf("[%x",(key_0->roundKeys[k].val[i][j]&0xF0) >> 4);
    //             if((key_0->roundKeys[k].val[i][j]&0xF) == 0x0)
    //                 printf("0]");
    //             else
    //                 printf("%x]",key_0->roundKeys[k].val[i][j]&0xF);
    //         }
    //         printf("\t");
    //         for(int j = 0; j < 4; j++){
    //             if((key_1->roundKeys[k].val[i][j]&0xF0) == 0x00)
    //                 printf("[0");
    //             else
    //                 printf("[%x",(key_1->roundKeys[k].val[i][j]&0xF0) >> 4);
    //             if((key_1->roundKeys[k].val[i][j]&0xF) == 0x0)
    //                 printf("0]");
    //             else
    //                 printf("%x]",key_1->roundKeys[k].val[i][j]&0xF);
    //         }
    //         printf("\t");
    //         for(int j = 0; j < 4; j++){
    //             if((key_2->roundKeys[k].val[i][j]&0xF0) == 0x00)
    //                 printf("[0");
    //             else
    //                 printf("[%x",(key_2->roundKeys[k].val[i][j]&0xF0) >> 4);
    //             if((key_2->roundKeys[k].val[i][j]&0xF) == 0x0)
    //                 printf("0]");
    //             else
    //                 printf("%x]",key_2->roundKeys[k].val[i][j]&0xF);
    //         }
    //         printf("\n");
    //     }
    //     printf("\n");
    // }


    for(int c = 0; c < 22; c++){
        printf("S%d\n",c);
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if((inner_state_0->inner[c].val[i][j]&0xF0) == 0x00)
                    printf("[0");
                else
                    printf("[%x",(inner_state_0->inner[c].val[i][j]&0xF0) >> 4);
                if((inner_state_0->inner[c].val[i][j]&0xF) == 0x0)
                    printf("0]");
                else
                    printf("%x]",inner_state_0->inner[c].val[i][j]&0xF);
            }
            printf("\t");
            for(int j = 0; j < 4; j++){
                if((inner_state_1->inner[c].val[i][j]&0xF0) == 0x00)
                    printf("[0");
                else
                    printf("[%x",(inner_state_1->inner[c].val[i][j]&0xF0) >> 4);
                if((inner_state_1->inner[c].val[i][j]&0xF) == 0x0)
                    printf("0]");
                else
                    printf("%x]",inner_state_1->inner[c].val[i][j]&0xF);
            }
            printf("\t");
            for(int j = 0; j < 4; j++){
                if((inner_state_2->inner[c].val[i][j]&0xF0) == 0x00)
                    printf("[0");
                else
                    printf("[%x",(inner_state_2->inner[c].val[i][j]&0xF0) >> 4);
                if((inner_state_2->inner[c].val[i][j]&0xF) == 0x0)
                    printf("0]");
                else
                    printf("%x]",inner_state_2->inner[c].val[i][j]&0xF);
            }
            printf("\n");
        }
        printf("\n");
    }

    free(key_0);
    free(key_1);
    free(key_2);
    free(inner_state_0);
    free(inner_state_1);
    free(inner_state_2);
    return 0;*/
}

/*
    Clef correspondante 1f000000000000000000000010000000
*/


















// int main(int argc, char **argv)
// {
//     /*char *filePathDif = "differentialProbability.txt";
//     char *filePathLin = "linearProbability.txt";*/

//     /*Message *message = messageCreate("./instance1.txt");

//     //Création clef initial
//     byte *key = (byte*)calloc(4,sizeof(byte));
//     key[0] = 0x4;
//     key[1] = 0xA;
//     key[2] = 0x7;
//     key[3] = 0x1;

//     int roundCount = 15;

//     Message initKey = {.tab = key, .size = 4};
//     Message **roundKeys = createRoundKeys(&initKey, roundCount);

//     messagePrint(message);


//     encrypt(message, roundKeys, roundCount);

//     messagePrint(message);

//     decrypt(message, roundKeys, roundCount);

//     messagePrint(message);

//     roundKeysDestroy(roundKeys, 1);
//     free(key);
//     messageDestroy(&message);*/

//     /*byte **DP = SBox_DifferentialProbability();

//     DP_FilePrint(DP, filePathDif);

//     DP_Delete(DP);

//     byte **LP = SBox_LinearProbability();

//     DP_FilePrint(LP, filePathLin);

//     DP_Delete(LP);*/

//     // byte **keys = ToyCipherKey_create(0x0000);
//     // if(ToyCipherKey_RoundKey(keys)){
//     //     printf("ERROR ROUND KEYS\n");
//     //     assert(0);
//     // }

//     // byte *text;

//     // for(int j = -1; j < 6; j++){
//     //     text = ToyCipher_encryptRound(0x0000, keys, j);
//     //     byte_affichage(text);
//     //     free(text);
//     // }

//     // ToyCipherKey_delete(keys);

//     /*int nb = 0;
//     unsigned short p0 = ((pairs[nb][0] << 12) & 0xF000) ^ ((pairs[nb][1] << 8) & 0xF00) ^ ((pairs[nb][2] << 4) & 0xF0) ^ ((pairs[nb][3]) & 0xF);
//     unsigned short p1 = p0 ^ 0x0400; 
//     byte *c0 = ToyCipher_encryptRound(p0, keys, 5);
//     byte *c1 = ToyCipher_encryptRound(p1, keys, 5);


//     printf("Plaintext 1 : ");
//     byte_affichage(pairs[nb]);
//     printf("Plaintext 2 : ");
//     pairs[nb][1] ^= 0x4;
//     byte_affichage(pairs[nb]);
//     printf("\n");
//     printf("CipherText 1 : ");
//     byte_affichage(c0);
//     printf("CipherText 2 : ");
//     byte_affichage(c1);
//     free(c0);
//     free(c1);*/

//     srand(time(NULL));

//     for(int i = 0; i <= 50; i += 5){
//         ToyCipher_Statistique(1 << 7, 1500, i);
//         printf("\n");
//     }
    
//     // int value_key = (keys[5][0] << 12) ^ (keys[5][1] << 8) ^ (keys[5][2] << 4) ^ (keys[5][3]);
//     // printf("Valeur de la bonne clef = %d\n\n", HPRD[value_key]);
//     // ToyCipherKey_delete(keys);

//     // free(HPRD);

//     // int max = 0;
//     // int nb = 0;

//     // while(max > -1){
//     //     max = -1;
//     //     nb = 0;
//     //     for(int i = 0; i < (1 << 16); i++){
//     //         if(HPRD[i] > max){
//     //             max = HPRD[i];
//     //         }
//     //     }
//     //     if(max > -1){
//     //         printf("Valeur : %d\n", max);
//     //         for(int i = 0; i < (1 << 16); i++){
//     //             if(HPRD[i] == max){
//     //                 nb++;
//     //                 HPRD[i] = -1;
//     //             }
//     //         }
//     //         printf("Le nombre de clef est de %d\n\n", nb);
//     //     }
//     // }
//     // free(HPRD);

//     return 0;
// }