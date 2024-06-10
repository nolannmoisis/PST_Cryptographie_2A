#include "SBox.h"

#pragma region Constant
const int S_BOX_SIZE = 16;
const byte subBytesTab[16] = {0x6, 0xB, 0x5, 0x4, 0x2, 0xE, 0x7, 0xA, 0x9, 0xD, 0xF, 0xC, 0x3, 0x1, 0x0, 0x8};
#pragma endregion

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

void LP_FilePrint(byte **LP, char *filePath){
    FILE *file = fopen(filePath, "w");
    for (int i = 0; i < S_BOX_SIZE; i++){
        for (int j = 0; j < S_BOX_SIZE; j++){
            if (LP[i][j] != 0){
                fprintf(file, "[%d] ", LP[i][j]);
            }
            else{
                fprintf(file, "[.] ");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
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
                if (scalar(a, x) == (scalar((int)subBytesTab[x], b))){
                    correlation++;
                }
            }
            buffer = ((2*(correlation)-16));
            buffer *= buffer;
            buffer /= 16;
            LP[a][b] = (byte)buffer;
        }
    }

    return LP;
}

void LP_Delete(byte **LP){
    for (int i = 0; i < S_BOX_SIZE; i++){
        free(LP[i]);
    }
    
    free(LP);
}