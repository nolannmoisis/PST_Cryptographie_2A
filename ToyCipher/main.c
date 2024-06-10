#include "ToyCipher.h"
#include "SBox.h"
#include "Mini AES.h"

#pragma region Define
#define SBoxLineaire
// #define SBoxDifferential
// #define ToyCipherHRPD
#pragma endregion

int main(int argc, char **argv)
{
    #pragma region Filepath
    char *filePathDif = "differentialProbability.txt";
    char *filePathLin = "linearProbability.txt";
    #pragma endregion

    #ifdef SBoxDifferential
        byte **DP = SBox_DifferentialProbability();
        DP_FilePrint(DP, filePathDif);
        DP_Delete(DP);
    #endif

    #ifdef SBoxLineaire
        byte **LP = SBox_LinearProbability();
        LP_FilePrint(LP, filePathLin);
        LP_Delete(LP);
    #endif

    #ifdef ToyCipherHRPD
        int q = (1 << 7);
        int C = 1;
        float statistique[4] = {0.0f};
        float bits_identify_count[5] = { 0.0f };

        Statistic_Table *statistic_table = Statistic_Table_create(1500, C);

        for(int i = 0; i < statistic_table->n_key; i++){
            unsigned short *buffer = ToyCipher_HPRD(q * statistic_table->coef, (unsigned short)( rand() % (1 << SIZE_STATISTIC_TABLE) ), &statistic_table->theGoodOne[i]);
            unsigned int total = 0;

            for(int j = 0; j < SIZE_STATISTIC_TABLE; j++){
                statistic_table->hrpd[i][j].value = buffer[j];
                total += buffer[j];
            }

            free(buffer);

            statistic_table->total_value[i] = total;

            qsort(statistic_table->hrpd[i], SIZE_STATISTIC_TABLE, sizeof(HPRD), Statistic_Table_Compare);

            for(int j = 0; j < SIZE_STATISTIC_TABLE; j++){
                if(statistic_table->hrpd[i][j].index == statistic_table->theGoodOne[i]){
                    switch (j){
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                            statistique[0] += 1.0f/statistic_table->n_key;
                            break;
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                            statistique[1] += 1.0f/statistic_table->n_key;
                            break;
                        case 8:
                        case 9:
                        case 10:
                        case 11:
                            statistique[2] += 1.0f/statistic_table->n_key;
                            break;
                        default:
                            statistique[3] += 1.0f/statistic_table->n_key;
                            break;
                    }
                }
            }

            int n = Bits_Identify(statistic_table->hrpd[i][0].index , statistic_table->theGoodOne[i]);

            switch (n){
                case 4:
                    bits_identify_count[4] += 1.0f/statistic_table->n_key;
                case 3:
                    bits_identify_count[3] += 1.0f/statistic_table->n_key;
                case 2:
                    bits_identify_count[2] += 1.0f/statistic_table->n_key;
                case 1:
                    bits_identify_count[1] += 1.0f/statistic_table->n_key;
                default:
                    bits_identify_count[0] += 1.0f/statistic_table->n_key;
                    break;
            }
        }

        printf("Proportion : (C = %d, Number Keys = %d)\n", statistic_table->coef, statistic_table->n_key);

        for (int i = 0, proportion = 100; i < 4; i++, proportion -= 25){
            printf("\t%d - %d%%    \t: %.1f%%\n", proportion, proportion - 25, 100 * statistique[i]);
        }

        printf("\n");

        for(int i = 4; i > -1; i--){
            printf("\t%d Bits identify\t: %.1f%%\n", i, 100 * bits_identify_count[i]);
        }
        
        Statistic_Table_destroy(statistic_table);
    #endif

    return 0;
}