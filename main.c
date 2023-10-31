#include"Mini AES.h"

int main(int argc, char **argv)
{
    Message *message = messageCreate("./instance1.txt");
    messagePrint(message);
    //printf("[%d] [%d]\n[%d] [%d]\n\n", (int)message->tab[0], (int)message->tab[2], (int)message->tab[1], (int)message->tab[3]);
    /*subBytes(message);
    messagePrint(message);
    shiftRows(message);
    messagePrint(message);
    shiftRowsReverse(message);
    messagePrint(message);
    subBytesReverse(message);
    messagePrint(message);*/

    byte *key = (byte*)calloc(4,sizeof(byte));
    key[0] = 0x4;
    key[1] = 0xE;
    key[2] = 0x7;
    key[3] = 0x1;

    Message initKey = {.tab = key, .size = 4};
    Message **roundKeys = createRoundKeys(&initKey, 1);

    for(int i = 0; i < 2; i++){
        addRoundKey(message, roundKeys[i]);
        messagePrint(message);
    }

    for(int i = 1; i >= 0; i--){
        addRoundKey(message, roundKeys[i]);
        messagePrint(message);
    }

    roundKeysDestroy(roundKeys, 1);
    free(key);
    messageDestroy(&message);

    return 0;
}