#include "SBox.h"

byte **SBox_DifferentialProbability(void){

    byte **DP = (byte**)calloc(S_BOX_SIZE, sizeof(byte*));
    byte *buffer = (byte*)calloc(S_BOX_SIZE, sizeof(byte));

    for(int i = 0; i < S_BOX_SIZE; i++){

        DP[i] = (byte*)calloc(S_BOX_SIZE, sizeof(byte));

        for(int j = 0; j < S_BOX_SIZE; j++){
            
        }
    }

    free(buffer);
}

byte **SBox_LinearProbability(void){

}