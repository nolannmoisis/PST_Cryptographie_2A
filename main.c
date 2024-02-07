#include "SBox.h"

int main(int argc, char **argv)
{
    char *filePath = "differentialProbability.txt";

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

    byte **DP = SBox_LinearProbability();

    DP_FilePrint(DP, filePath);

    DP_Delete(DP);

    return 0;
}