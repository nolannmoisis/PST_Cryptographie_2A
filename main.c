#include"Mini AES.h"

int main(int argc, char **argv)
{
    Message *message = messageCreate("./instance2.txt");
    messagePrint(message);
    //printf("[%d] [%d]\n[%d] [%d]\n\n", (int)message->tab[0], (int)message->tab[2], (int)message->tab[1], (int)message->tab[3]);
    //subBytes(message);
    shiftRows(message);
    messagePrint(message);
    shiftRowsReverse(message);
    messagePrint(message);
    //printf("[%d] [%d]\n[%d] [%d]\n\n", (int)message->tab[0], (int)message->tab[2], (int)message->tab[1], (int)message->tab[3]);
    messageDestroy(&message);

    return 0;
}