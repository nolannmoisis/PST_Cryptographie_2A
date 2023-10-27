#include"Mini AES.h"

int main(int argc, char **argv)
{
    Message *message = messageCreate("./instance1.txt");

    

    messageDestroy(&message);

    return 0;
}