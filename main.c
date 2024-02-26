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

    byte *tab = (byte*)calloc(4, sizeof(byte));
    for (int i = 0; i < 4; i++)
    {
        tab[i] = 0x9;
    }

    ToyCipherKey_permutation(tab);

    for (int i = 0; i < 4; i++)
    {
        if (tab[i] >= 10)
            {
                printf("[%c] ", tab[i] + 'A' - 10);
            }
            else{
                printf("[%d] ", tab[i]);
            }   
    }
    printf("\n");

    return 0;
}