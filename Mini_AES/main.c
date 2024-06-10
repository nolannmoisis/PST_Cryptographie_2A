#include "Mini AES.h"

int main() 
{
    Message *key = (Message*)calloc(1, sizeof(Message));
    Message *message = messageCreate("instance1.txt", key);

    int roundCount = 15;
    Message **roundKeys = createRoundKeys(key, roundCount);

    printf("Message d origine : \n");
    messagePrint(message);

    encrypt(message, roundKeys, roundCount);

    printf("Message chiffre : \n");
    messagePrint(message);

    decrypt(message, roundKeys, roundCount);

    printf("Message dechiffre : \n");
    messagePrint(message);

    roundKeysDestroy(roundKeys, 1);
    free(key);
    messageDestroy(&message);

    return 0;
}