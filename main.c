#include "AES.h"
#include "settings.h"

int main(int argc, char** argv){
    AES_128 *aes_128 = (AES_128*)malloc(sizeof(AES_128));

    byte cipherkey[16] = { 0 };

    long int number = 0;
    setCipherKey(aes_128, cipherkey);
    
    //Recherche d'une clef correspondante
    while(!((aes_128->roundKeys[8].val[0][3] == 0) && (aes_128->roundKeys[8].val[1][0] == 0))){
        printf("Nombre de clef essayer : %ld\n", number++);
        for(int i = 0; i < 16; i++){
            if(cipherkey[i] == 0xFF)
                cipherkey[i] = 0x00;
            else{
                cipherkey[i]++;
                break;
            }
        }
        setCipherKey(aes_128, cipherkey);
    }

    printf("\nClef trouver :\n");



    for(int i = 0; i < 11; i++){
        printf("Clef round %d\t:\t", i);
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                if(!(aes_128->roundKeys[i].val[j][k] >> 4))
                    printf("0");
                else
                    printf("%x", aes_128->roundKeys[i].val[j][k] >> 4);

                if(!(aes_128->roundKeys[i].val[j][k] & 0xF))
                    printf("0");
                else
                    printf("%x", aes_128->roundKeys[i].val[j][k] & 0xF);
            }
        }
        printf("\n");
    }

    free(aes_128);
    return 0;
}

/*
    Clef correspondante 3dd20000000000000000000000000000
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


