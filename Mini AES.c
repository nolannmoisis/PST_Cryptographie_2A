#include "Mini AES.h"

const byte subBytestab[16] = {6,'b' - 'W', 5, 4, 2, 'e' - 'W', 7, 'a' - 'W', 9, 'd' - 'W', 'f' - 'W', 'c' - 'W', 3, 1, 0, 8};

void subBytes(Message *message){
    //vérification de l'existance du message
    assert(message);
    assert(message->tab);
    assert(message->size);
    

    for(int i = 0; i < message->size; i++)message->tab[i] = subBytestab[(int)message->tab[i]];
}

void shiftRows(Message *message){
    //vérification de l'existance du message
    assert(message);
    assert(message->tab);
    assert(message->size);

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
    //vérification de l'existance du message
    assert(message);
    assert(message->tab);
    assert(message->size);

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

}

void addRoundKey(Message *message, Message *roundKey){

}

void encrypt(Message *message, Message *roundKey, int round){
    
}

Message *messageCreate(char *path){

    //Création du pointeur vers le fichier
    FILE *pfile = fopen(path, "r");

    //Vérification de l'adresse du fichier
    if(!pfile)
    {
        printf("Adresse du fichier incorrect\n");
        assert(pfile);
    }

    //Allocation du message
    Message *new = (Message*)calloc(1, sizeof(Message));

    //Lecture du nombre d'entré
    if(fscanf(pfile, "%d\n", &new->size) != 1)
    {
        printf("Erreur recuperation nombre entree fichier\n");
        fclose(pfile);
        return NULL;
    }

    //Allocation du tableau contenant les données
    new->tab = (byte*)calloc(new->size, sizeof(byte));

    for(int i = 0; i < new->size; i++)
    {
        //Vérification des valeurs récupérés et cast d'un byte en int (lisibilité)
        if(fscanf(pfile, "%c\n", &(new->tab[i])) != 1)
        {
            printf("Erreur recuperation nombre a chiffrer\n");
            fclose(pfile);
            return NULL;
        }
        if('0' <= new->tab[i] && new->tab[i] <= '9')new->tab[i] -= '0';
        else if('A' <= new->tab[i] && new->tab[i] <= 'F')new->tab[i] -= '7';
        else if('a' <= new->tab[i] && new->tab[i] <= 'f')new->tab[i] -= 'W';
        else
        {
            printf("Erreur, donnee incorrect\n");
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
    //vérification de l'existance du message
    assert(message);
    assert(message->tab);
    assert(message->size);

    for(int i = 0; i < sqrt(message->size); i++){
        for (int j = i; j < message->size; j += sqrt(message->size)) {
            printf("[%d] ",message->tab[j]);
        }
        printf("\n");
    }
    printf("\n");
}