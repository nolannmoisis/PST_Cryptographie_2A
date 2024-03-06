#include "ToyCipher.h"

int main(int argc, char **argv)
{
    /*char *filePathDif = "differentialProbability.txt";
    char *filePathLin = "linearProbability.txt";*/

    /*Message *message = messageCreate("./instance1.txt");

    //Création clef initial
    byte *key = (byte*)calloc(4,sizeof(byte));
    key[0] = 0x4;
    key[1] = 0xA;
    key[2] = 0x7;
    key[3] = 0x1;

    int roundCount = 15;

    Message initKey = {.tab = key, .size = 4};
    Message **roundKeys = createRoundKeys(&initKey, roundCount);

    messagePrint(message);


    encrypt(message, roundKeys, roundCount);

    messagePrint(message);

    decrypt(message, roundKeys, roundCount);

    messagePrint(message);

    roundKeysDestroy(roundKeys, 1);
    free(key);
    messageDestroy(&message);*/

    /*byte **DP = SBox_DifferentialProbability();

    DP_FilePrint(DP, filePathDif);

    DP_Delete(DP);

    byte **LP = SBox_LinearProbability();

    DP_FilePrint(LP, filePathLin);

    DP_Delete(LP);*/

    // byte **keys = ToyCipherKey_create(0x0000);
    // if(ToyCipherKey_RoundKey(keys)){
    //     printf("ERROR ROUND KEYS\n");
    //     assert(0);
    // }

    // byte *text;

    // for(int j = -1; j < 6; j++){
    //     text = ToyCipher_encryptRound(0x0000, keys, j);
    //     byte_affichage(text);
    //     free(text);
    // }

    // ToyCipherKey_delete(keys);

    /*int nb = 0;
    unsigned short p0 = ((pairs[nb][0] << 12) & 0xF000) ^ ((pairs[nb][1] << 8) & 0xF00) ^ ((pairs[nb][2] << 4) & 0xF0) ^ ((pairs[nb][3]) & 0xF);
    unsigned short p1 = p0 ^ 0x0400; 
    byte *c0 = ToyCipher_encryptRound(p0, keys, 5);
    byte *c1 = ToyCipher_encryptRound(p1, keys, 5);


    printf("Plaintext 1 : ");
    byte_affichage(pairs[nb]);
    printf("Plaintext 2 : ");
    pairs[nb][1] ^= 0x4;
    byte_affichage(pairs[nb]);
    printf("\n");
    printf("CipherText 1 : ");
    byte_affichage(c0);
    printf("CipherText 2 : ");
    byte_affichage(c1);
    free(c0);
    free(c1);*/

    int size = 0;
    byte **pairs = ToyCipher_GoodPair(0x0000, 0x0400, 0x0400, &size);

    printf("Le nombre de bonnes pairs est de %d\n", size);

    for(int i = 0; i < size; i++){
        free(pairs[i]);
    }
    free(pairs);

    return 0;
}
