#include "Mini AES.h"

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

}

void mixColumnsReverse(Message *message){

}

void addRoundKey(Message *message, Message *roundKey){

}

void encrypt(Message *message, Message *roundKey, int round){
    
}

void convertCharToHex(Message *message){
    checkMessage(message); // Permet de vérifier si le message existe ou s'il n'est pas corrompu

    // Parcours l'entièreté du message
    for (int i = 0; i < message->size; i++) {
        // Vérifie si le terme héxadécimal est un chiffre compris entre 0 et 9
        if (message->tab[i] >= '0' && message->tab[i] <= '9') {
            // Convertir les caractères
            message->tab[i] -= '0'; 
        }

        // Vérifie si le terme héxadéciaml est une lettre compris entre A et F
        else if (message->tab[i] >= 'A' && message->tab[i] <= 'F') {
            // Convertir les caractères
            message->tab[i] -= 'A' - 10;
        }
        
        // Vérifie si le terme héxadéciaml est une lettre compris entre a et f
        else if (message->tab[i] >= 'a' && message->tab[i] <= 'f') {
            // Convertir les caractères
            message->tab[i] -= 'a' - 10;
        }
    }
}

Message *messageCreate(char *path){

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
    if(fscanf(pfile, "%d\n", &new->size) != 1)
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
        if(fscanf(pfile, "%c\n", &(new->tab[i])) != 1)
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

    convertCharToHex(new);

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
            printf("[%d] ",message->tab[j]);
        }
        printf("\n");
    }
    printf("\n");
}