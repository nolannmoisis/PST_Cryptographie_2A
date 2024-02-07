#include "SBox.h"

const int S_BOX_SIZE = 16;

byte **SBox_DifferentialProbability(void){
    byte **DP = (byte**)calloc(S_BOX_SIZE, sizeof(byte*));

    for(int a = 0; a < S_BOX_SIZE; a++){
        byte *buffer = (byte*)calloc(S_BOX_SIZE, sizeof(byte));
        DP[a] = (byte*)calloc(S_BOX_SIZE, sizeof(byte));

        for(int x = 0; x < S_BOX_SIZE; x++){
            buffer[subBytesTab[x]^subBytesTab[x^a]]++;
        }

        for (int b = 0; b < S_BOX_SIZE; b++){
            DP[a][b] = buffer[b];
        }

        free(buffer);
    }

    return DP;
}

void DP_FilePrint(byte **DP, char *filePath){
    FILE *file = fopen(filePath, "w");
    for (int i = 0; i < S_BOX_SIZE; i++){
        for (int j = 0; j < S_BOX_SIZE; j++){
            if (DP[i][j] != 0){
                fprintf(file, "[%d] ", DP[i][j]);
            }
            else{
                fprintf(file, "[.] ");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void DP_Delete(byte **DP){
    for (int i = 0; i < S_BOX_SIZE; i++){
        free(DP[i]);
    }
    
    free(DP);
}

byte **SBox_LinearProbability(void){
    byte **LP = (byte**)calloc(S_BOX_SIZE, sizeof(byte*));

    for(int a = 0; a < S_BOX_SIZE; a++){
        byte *buffer = (byte*)calloc(S_BOX_SIZE, sizeof(byte));
        LP[a] = (byte*)calloc(S_BOX_SIZE, sizeof(byte));

        for (int b = 0; b < S_BOX_SIZE; b++){
            for(int x = 0; x < S_BOX_SIZE; x++){
                if ((a*x)%16 == (subBytesTab[x]*b)%16){
                    buffer[b]++;
                }
            }
            LP[a][b] = ((2*(buffer[b])-16) * (2*(buffer[b])-16))/16;
        }

        free(buffer);
    }

    return LP;
}