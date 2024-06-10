#include "Mini AES.h"

const byte subBytesReverseTab[16] = {0xE, 0xD, 0x4, 0xC, 0x3, 0x2, 0x0, 0x6, 0xF, 0x8, 0x7, 0x1, 0xB, 0x9, 0x5, 0xA};
const byte subBytesTab[16] = {0x6, 0xB, 0x5, 0x4, 0x2, 0xE, 0x7, 0xA, 0x9, 0xD, 0xF, 0xC, 0x3, 0x1, 0x0, 0x8};
//const byte subBytesTab[16] = {0x7, 0x3, 0xD, 0x9, 0xC, 0x2, 0x4, 0x8, 0xA, 0xB, 0x1, 0x0, 0xE, 0xF, 0x5, 0x6};
const byte constKey[16] = {0x1, 0x2, 0x4, 0x8, 0x3, 0x6, 0xC, 0xB, 0x5, 0xA, 0x7, 0xE, 0xF, 0xD, 0x9};
const byte matrixMultiplication[16][3] = {{0x0, 0x0, 0x0},
                                          {0x1, 0x2, 0x3},
                                          {0x2, 0x4, 0x6},
                                          {0x3, 0x6, 0x5},
                                          {0x4, 0x8, 0xC},
                                          {0x5, 0xA, 0xF},
                                          {0x6, 0xC, 0xA},
                                          {0x7, 0xE, 0x9},
                                          {0x8, 0x3, 0xB},
                                          {0x9, 0x1, 0x8},
                                          {0xA, 0x7, 0xD},
                                          {0xB, 0x5, 0xE},
                                          {0xC, 0xB, 0x7},
                                          {0xD, 0x9, 0x4},
                                          {0xE, 0xF, 0x1},
                                          {0xF, 0xD, 0x2}};
const byte matrixMixColumns[4] = {0x3, 0x2, 0x2, 0x3};

void checkMessage(Message *message){
    // Vérification si le message existe
    if (!message)
    {
        printf("ERROR : NON-EXISTENT MESSAGE\n"); // Affiche l'erreur
        assert(message); // Sort du programme
    }

    // Vérification si le tableau du message existe
    else if (!(message->tab))
    {
        printf("ERROR : NON-EXISTENT MESSAGE BOARD\n"); // Affiche l'erreur
        assert(message->tab); // Sort du programme
    }

    // Vérification si la taille du message existe
    else if (!(message->size))
    {
        printf("ERROR : NON-EXISTENT MESSAGE SIZE\n"); // Affiche l'erreur
        assert(message->size); // Sort du programme
    }
}

void subBytes(Message *message){
    checkMessage(message); // Permet de vérifier si le message existe ou s'il n'est pas corrompu

    // Parcours l'entièreté du message
    for(int i = 0; i < message->size; i++){
        // Substitue l'élément i du message par celui du tableau subBytesTab
        message->tab[i] = subBytesTab[(int)message->tab[i]];
    }
}

void subBytesReverse(Message *message){
    checkMessage(message); // Permet de vérifier si le message existe ou s'il n'est pas corrompu

    // Parcours l'entièreté du message
    for(int i = 0; i < message->size; i++){
        // Substitue l'élément i du message par celui du tableau subBytesReverseTab
        message->tab[i] = subBytesReverseTab[(int)message->tab[i]];
    }
}

void shiftRows(Message *message){
    checkMessage(message); // Permet de vérifier si le message existe ou s'il n'est pas corrompu

    int tmp=0;
    for(int i = 0; i < sqrt(message->size); i++){
        for(int k = 0; k < i; k++) {
            for (int j = i; j < message->size; j += (int)sqrt(message->size)) {
                if (j < sqrt(message->size)) {
                    tmp = message->tab[j];
                    message->tab[j] = message->tab[(int) (j + sqrt(message->size))];
                }
                if (j + sqrt(message->size) >= message->size) {
                    message->tab[j] = tmp;
                } else if (j >= sqrt(message->size)) {
                    message->tab[j] = message->tab[(int) (j + sqrt(message->size))];
                }
            }
        }
    }
}

void shiftRowsReverse(Message *message){
    checkMessage(message); // Permet de vérifier si le message existe ou s'il n'est pas corrompu

    int tmp = 0;
    for(int i = (int)sqrt(message->size); i > 0; i--){
        for(int k = (int)sqrt(message->size); k > i; k--) {
            for (int j = (int)message->size - i; j > 0; j -= (int)sqrt(message->size)) {
                if (j > message->size - sqrt(message->size)) {
                    tmp = message->tab[j];
                    message->tab[j] = message->tab[(int) (j - sqrt(message->size))];
                }
                if (j - sqrt(message->size) <=0) {
                    message->tab[j] = tmp;
                } else if (j <= message->size - sqrt(message->size)) {
                    message->tab[j] = message->tab[(int) (j - sqrt(message->size))];
                }
            }
        }
    }
}

void mixColumns(Message *message){
    checkMessage(message); // Permet de vérifier si le message existe ou s'il n'est pas corrompu

    int tmp0 = message->tab[0], tmp2 = message->tab[2];
    message->tab[0] = matrixMultiplication[(int)(message->tab[0])][(int)(matrixMixColumns[0])-1] ^ matrixMultiplication[(int)(message->tab[1])][(int)(matrixMixColumns[1])-1];
    message->tab[1] = matrixMultiplication[(int)(tmp0)][(int)(matrixMixColumns[2])-1] ^ matrixMultiplication[(int)(message->tab[1])][(int)(matrixMixColumns[3])-1];
    message->tab[2] = matrixMultiplication[(int)(message->tab[2])][(int)(matrixMixColumns[0])-1] ^ matrixMultiplication[(int)(message->tab[3])][(int)(matrixMixColumns[1])-1];
    message->tab[3] = matrixMultiplication[(int)(tmp2)][(int)(matrixMixColumns[2])-1] ^ matrixMultiplication[(int)(message->tab[3])][(int)(matrixMixColumns[3])-1];
}

void mixColumnsReverse(Message *message){
    checkMessage(message); // Permet de vérifier si le message existe ou s'il n'est pas corrompu

    int tmp0 = message->tab[0], tmp2 = message->tab[2];
    message->tab[0] = matrixMultiplication[(int)(message->tab[0])][(int)(matrixMixColumns[0])-1] ^ matrixMultiplication[(int)(message->tab[1])][(int)(matrixMixColumns[1])-1];
    message->tab[1] = matrixMultiplication[(int)(tmp0)][(int)(matrixMixColumns[2])-1] ^ matrixMultiplication[(int)(message->tab[1])][(int)(matrixMixColumns[3])-1];
    message->tab[2] = matrixMultiplication[(int)(message->tab[2])][(int)(matrixMixColumns[0])-1] ^ matrixMultiplication[(int)(message->tab[3])][(int)(matrixMixColumns[1])-1];
    message->tab[3] = matrixMultiplication[(int)(tmp2)][(int)(matrixMixColumns[2])-1] ^ matrixMultiplication[(int)(message->tab[3])][(int)(matrixMixColumns[3])-1];
}

Message **createRoundKeys(Message *initKey, int roundCount){
    checkMessage(initKey);// Permet de vérifier si le message existe ou s'il n'est pas corrompu
    if(!(0 <= roundCount && roundCount <= 15)) //Vérification de la validité du nombre de clef à créer
    {
        printf("ERROR : NON-POSSIBLE-VALUE-ROUND\n");
        assert(false);
    }

    Message **roundKeys = (Message**)calloc(roundCount + 1, sizeof(Message*));
    if(!roundKeys){
        printf("ERROR : NON-EXISTENT MESSAGE\n");
        assert(false);
    }

    //Initialisation des variables et de la première clef ronde identique à la clef initial
    int x0 = 0, x1 = 0;
    roundKeys[0] = initKey;

    for(int i = 1; i < roundCount + 1; i++)
    {
        roundKeys[i] = (Message*)calloc(1,sizeof(Message));
        roundKeys[i]->tab = (byte*)calloc(4,sizeof(byte));
        roundKeys[i]->size = 4;
        checkMessage(roundKeys[i]);

        //Initialisation des valeurs
        x0 = roundKeys[i - 1]->tab[4];
        x1 = roundKeys[i - 1]->tab[3];

        x0 = subBytesTab[x0];
        x1 = subBytesTab[x1];

        x0 = x0 ^ constKey[i - 1];

        roundKeys[i]->tab[0] = roundKeys[i - 1]->tab[0] ^ x0;
        roundKeys[i]->tab[1] = roundKeys[i - 1]->tab[1] ^ x1;
        roundKeys[i]->tab[2] = roundKeys[i - 1]->tab[2] ^ roundKeys[i - 1]->tab[0];
        roundKeys[i]->tab[3] = roundKeys[i - 1]->tab[3] ^ roundKeys[i - 1]->tab[1];

    }

    return roundKeys;
}

void roundKeysDestroy(Message **roundKeys, int roundCount){
    if(!(0 <= roundCount && roundCount <= 15)){ //Vérification de la validité du nombre de clef à créer
        printf("ERROR : NON-POSSIBLE-VALUE-ROUND\n");
        assert(false);
    }
    if(!roundKeys){ //Vérification de la validité du tableau
        printf("ERROR : NON-EXISTENT MESSAGE\n");
        assert(false);
    }

    for(int i = 1; i < roundCount + 1; i++)
    {
        checkMessage(roundKeys[i]);
        free(roundKeys[i]->tab);
        free(roundKeys[i]);
    }

    free(roundKeys);
}

void addRoundKey(Message *message, Message *roundKey){
    checkMessage(message);
    checkMessage(roundKey);
    for(int i = 0; i < message->size; i++)message->tab[i] ^= roundKey->tab[i];
}

void encrypt(Message *message, Message **roundKey, int round){
    addRoundKey(message, roundKey[0]);
    for(int i = 1; i < round; i++){
        subBytes(message);
        shiftRows(message);
        mixColumns(message);
        addRoundKey(message, roundKey[i]);
    }
    subBytes(message);
    shiftRows(message);
    addRoundKey(message, roundKey[round]);

}

void decrypt(Message *message, Message **roundKeys, int round){
    addRoundKey(message, roundKeys[round]);
    shiftRowsReverse(message);
    subBytesReverse(message);
    for(int i = round - 1; i > 0; i--){
        addRoundKey(message, roundKeys[i]);
        mixColumns(message);
        shiftRowsReverse(message);
        subBytesReverse(message);
    }
    addRoundKey(message, roundKeys[0]);
}

Message *messageCreate(char *path, Message* key){

    //Création du pointeur vers le fichier
    FILE *pfile = fopen(path, "r");

    //Vérification de l'adresse du fichier
    if(!pfile)
    {
        printf("ERROR : INCORRECT FILE ADDRESS -> %s\n", path);
        assert(pfile);
    }

    //Allocation du message
    Message *new = (Message*)calloc(1, sizeof(Message));

    //Lecture du nombre d'entré
    if(fscanf(pfile, "%d ", &new->size) != 1)
    {
        printf("ERROR : RECOVERY NUMBER OF FILE ENTRIES\n");
        fclose(pfile);
        return NULL;
    }

    //Allocation du tableau contenant les données
    new->tab = (byte*)calloc(new->size, sizeof(byte));

    for(int i = 0; i < new->size; i++)
    {
        //Vérification des valeurs récupérés et cast d'un byte en int (lisibilité)
        if(fscanf(pfile, "%c ", &(new->tab[i])) != 1)
        {
            printf("EROOR : RECOVERY NUMBER TO BE CHIFFER\n");
            fclose(pfile);
            return NULL;
        }
        if('0' <= new->tab[i] && new->tab[i] <= '9')new->tab[i] -= '0';
        else if('A' <= new->tab[i] && new->tab[i] <= 'F')new->tab[i] -= '7';
        else if('a' <= new->tab[i] && new->tab[i] <= 'f')new->tab[i] -= 'W';
        else
        {
            printf("EROOR : INCORRECT DATA\n");
            fclose(pfile);
            return NULL;
        }
    }
    fscanf(pfile, "\n");

    if(fscanf(pfile, "%d ", &key->size) != 1)
    {
        printf("ERROR : RECOVERY NUMBER OF FILE ENTRIES\n");
        fclose(pfile);
        return NULL;
    }

    //Allocation du tableau contenant les données
    key->tab = (byte*)calloc(key->size, sizeof(byte));
    
    for(int i = 0; i < key->size; i++)
    {
        //Vérification des valeurs récupérés et cast d'un byte en int (lisibilité)
        if(fscanf(pfile, "%c ", &(key->tab[i])) != 1)
        {
            printf("EROOR : RECOVERY NUMBER TO BE CHIFFER\n");
            fclose(pfile);
            return NULL;
        }
        if('0' <= key->tab[i] && key->tab[i] <= '9')key->tab[i] -= '0';
        else if('A' <= key->tab[i] && key->tab[i] <= 'F')key->tab[i] -= '7';
        else if('a' <= key->tab[i] && key->tab[i] <= 'f')key->tab[i] -= 'W';
        else
        {
            printf("EROOR : INCORRECT DATA\n");
            fclose(pfile);
            return NULL;
        }
    }

    fclose(pfile);
    return new;
}

void messageDestroy(Message** message)
{
    //Vérification de l'existance de la variable message
    if(!message)
    {
        printf("Variable message inexistant\n");
        assert(message);
    }
    else if (!(*message))
    {
        printf("Variable message inexistant\n");
        assert(*message);
    }

    //Vérification de l'existance du tableau et libération
    if((*message)->tab)free((*message)->tab);
    free((*message));
    *message = NULL;
}

void messagePrint(Message *message){
    checkMessage(message); // Permet de vérifier si le message existe ou s'il n'est pas corrompu

    for(int i = 0; i < sqrt(message->size); i++){
        for (int j = i; j < message->size; j += sqrt(message->size)) {
            if (message->tab[j] >= 10)
            {
                printf("[%c] ",message->tab[j] + 'A' - 10);
            }
            else{
                printf("[%d] ",message->tab[j]);
            }            
        }
        printf("\n");
    }
    printf("\n");
}