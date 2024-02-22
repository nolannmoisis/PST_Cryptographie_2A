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

int scalar(int a, int b){
    int count = 0;
    int sum = a & b;
    for(int i = 0; i < 4; i++){
        if(sum & 0b1)count++;
        sum = sum >> 1;
    }
    return count%2;
}

byte **SBox_LinearProbability(void){
    byte **LP = (byte**)calloc(S_BOX_SIZE, sizeof(byte*));
    int buffer = 0;
    int correlation = 0;

    for(int a = 0; a < S_BOX_SIZE; a++){
        LP[a] = (byte*)calloc(S_BOX_SIZE, sizeof(byte));

        for (int b = 0; b < S_BOX_SIZE; b++){
            correlation = 0;
            for(int x = 0; x < S_BOX_SIZE; x++){
                //printf("scalaire (a = %d, x = %d) : %d et l'autre b = %d : %d\n", a, x, scalar(a, x), b, scalar((int)subBytesTab[x], b));
                if (scalar(a, x) == (scalar((int)subBytesTab[x], b))){
                    correlation++;
                }
            }
            //printf("\n");
            buffer = ((2*(correlation)-16));
            buffer *= buffer;
            buffer /= 16;
            LP[a][b] = (byte)buffer;
        }
    }

    return LP;
}
