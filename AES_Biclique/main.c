#include "AES.h"
#include "settings.h"

#define DEMO //presentation pour la demonstration

int main(int argc, char** argv){

    #ifdef DEMO
        if(system("clear"));
        printf("Vous pouvez choisir plusieurs demonstration :\n");
        printf("\t1 - Observation des differences sur les 3 derniers tours\n");
        printf("\t2 - Montrer une partie de la matrice de clefs\n");
        printf("\t3 - Montrer la différence entre une attaque biclique et le brute force sur %d clef differente\n", (1 << 24));

        printf("Demo : ");

        int demo_state, tmp;
        if(scanf("%d", &demo_state));
        while (demo_state < 1 || 4 < demo_state){
            printf("\nErreur lors de la selection de la demo, veuillez reessayer\n");
            printf("Demo : ");
            if(scanf("%d", &demo_state));
        }

        //Case 1
        byte init_key[16] = { 0x1f, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        byte C0[16] = { 0 }, S0[16] = { 0 };
        AES_128 key0, key1, key2;
        Inner_State interne0, interne1, interne2;

        //Case 3
        AES_128 secret_key = { 0x0 }, attaque = { 0x0 }, brute_force = { 0x0 };
        byte word[16] = { 0 };
        Inner_State interne;
        State ciphertext, result;
        clock_t start, end_biclique, end;
        double timer1, timer2;
        bool find = false;
        int round;
        
        switch (demo_state)
        {
        case 3:

            printf("Premiere variable (modulo 256) : ");
            if(scanf("%d", &tmp));
            //Valeur de la première case
            secret_key.roundKeys[8].val[0][0] = tmp%256;
            //Valeur de la deuxième case
            secret_key.roundKeys[8].val[2][0] = 0x00;

            printf("\nDeuxieme variable (modulo 256) : ");
            if(scanf("%d", &tmp));
            //Valeur de la troisème case
            secret_key.roundKeys[8].val[0][3] = tmp%256;

            printf("\nTroiseme variable (modulo 256) : ");
            if(scanf("%d", &tmp));
            //Valeur de la quatrième case
            secret_key.roundKeys[8].val[1][0] = tmp%256;
            //Mise à jour de deux autres cases pour le bon fonctionnement de l'attaque biclique sur 3 cases
            secret_key.roundKeys[8].val[0][2] = secret_key.roundKeys[8].val[0][3] ^ 0x00;
            secret_key.roundKeys[8].val[1][2] = secret_key.roundKeys[8].val[1][0] ^ 0x00;
            setCipherKey_recomputeFrom8(&secret_key);

            encrypt128(&secret_key, word, &interne);
            ciphertext = interne.inner[21];

            printf("\nCalcule de l'attaque biclique\n");
            //Attaque Biclique
            start = clock();
            result = Attaque_Biclique(&secret_key);
            attaque.roundKeys[8] = result;
            setCipherKey_recomputeFrom8(&attaque);
            end_biclique = clock();

            printf("\nCalcule de l'attaque Brute Force\n");
            //Brute Force
            for(int i0 = 0; i0 < 256 && !find; i0++){
                brute_force.roundKeys[8].val[0][0] = i0;
                for(int i1 = 0; i1 < 256 && !find; i1++){
                    brute_force.roundKeys[8].val[0][3] = i1;
                    brute_force.roundKeys[8].val[0][2] = i1;
                    for(int i2 = 0; i2 < 256 && !find; i2++){
                        brute_force.roundKeys[8].val[1][0] = i2;
                        brute_force.roundKeys[8].val[1][2] = i2;
                        setCipherKey_recomputeFrom8(&brute_force);
                        encrypt128(&brute_force, word, &interne);
                        if(is_equal(ciphertext, interne.inner[21]))
                            find = true;
                    }
                }
            }

            end = clock();

            timer1 = (double)(end_biclique - start)/ CLOCKS_PER_SEC;
            timer2 = (double)(end - end_biclique)/ CLOCKS_PER_SEC;

            round = 8;
            printf("Clef secrete\n");
            for(int a = 0; a < 4; a++){
                for(int b = 0; b < 4; b++){
                    printf("[%x]", secret_key.roundKeys[round].val[a][b]);
                }
                printf("\n");
            }
            printf("\nClef retrouve avec l'attaque en %.2lf s\n", timer1);
            for(int a = 0; a < 4; a++){
                for(int b = 0; b < 4; b++){
                    printf("[%x]", attaque.roundKeys[round].val[a][b]);
                }
                printf("\n");
            }
            printf("\nClef retrouve avec le brute force en %.2lf s\n", timer2);
            for(int a = 0; a < 4; a++){
                for(int b = 0; b < 4; b++){
                    printf("[%x]", brute_force.roundKeys[round].val[a][b]);
                }
                printf("\n");
            }
            printf("\n\nUne diminution de %.2lf%%\n", (timer2) ? ((1 - (timer1/timer2)) * 100) : 0.00f);
            break;

        case 1:
            printf("key : ");
            for(int i = 0; i < 16; i++){
                    int x1 = (init_key[i] >> 4) & 0xf, x0 = init_key[i] & 0xf;
                    printf("%x%x", (x1) ? x1: 0, (x0) ? x0: 0);
            }
            printf("\n\nVariation i : f\tj : f\n");
            
            setCipherKey(&key0, init_key);
            key1 = key0;
            key2 = key0;
            setCipherKey_delta_i(&key1, 0xf);
            setCipherKeyRound(&key1);
            setCipherKey_delta_j(&key2, 0xf);
            setCipherKeyRound(&key2);

            decrypt128(&key0, C0, &interne0);
            for(int a = 0; a < 4; a++)
                for(int b = 0; b < 4; b++)
                    S0[4*b+a] = interne0.inner[15].val[a][b];

            interne1 = interne0;
            f_encrypt128(&key1, S0, &interne1);
            decrypt128(&key2, C0, &interne2);

            for(int s = 15; s < 22; s++){
                printf("#%d\n", s);
                for(int a = 0; a < 4; a++){
                    for(int b = 0; b < 4; b++){
                        int x1 = (interne0.inner[s].val[a][b] >> 4) & 0xf, x0 = interne0.inner[s].val[a][b] & 0xf;
                        printf("[%x%x]", (x1) ? x1: 0, (x0) ? x0: 0);
                    }
                    printf("\t");
                    for(int b = 0; b < 4; b++){
                        int x1 = (interne1.inner[s].val[a][b] >> 4) & 0xf, x0 = interne1.inner[s].val[a][b] & 0xf;
                        printf("[%x%x]", (x1) ? x1: 0, (x0) ? x0: 0);
                    }
                    printf("\t");
                    for(int b = 0; b < 4; b++){
                        int x1 = (interne2.inner[s].val[a][b] >> 4) & 0xf, x0 = interne2.inner[s].val[a][b] & 0xf;
                        printf("[%x%x]", (x1) ? x1: 0, (x0) ? x0: 0);
                    }
                    printf("\n");
                }
                printf("\n");
            }
            printf("\n");

            break;
        default:
            printf("2 - Montrer une partie de la matrice de clefs\n");
            break;
        }

    #else

        AES_128 secret_key = { 0x0 };
        //Valeur de la première case
        secret_key.roundKeys[8].val[0][0] = 0xae;
        //Valeur de la deuxième case
        secret_key.roundKeys[8].val[2][0] = 0x00;
        //Valeur de la troisème case
        secret_key.roundKeys[8].val[0][3] = 0xd0;
        //Valeur de la quatrième case
        secret_key.roundKeys[8].val[1][0] = 0x31;
        //Mise à jour de deux autres cases
        secret_key.roundKeys[8].val[0][2] = secret_key.roundKeys[8].val[0][3] ^ 0x00;
        secret_key.roundKeys[8].val[1][2] = secret_key.roundKeys[8].val[1][0] ^ 0x00;
        setCipherKey_recomputeFrom8(&secret_key);

        byte word[16] = { 0 };
        Inner_State interne;
        encrypt128(&secret_key, word, &interne);
        State ciphertext = interne.inner[21];

        clock_t start = clock();
        State result = Attaque_Biclique(&secret_key);
        AES_128 attaque = { 0x0 };
        attaque.roundKeys[8] = result;
        setCipherKey_recomputeFrom8(&attaque);
        clock_t end_biclique = clock();

        AES_128 brute_force = { 0 };
        bool find = false;

        for(int i0 = 0; i0 < 256 && !find; i0++){
            brute_force.roundKeys[8].val[0][0] = i0;
            for(int i1 = 0; i1 < 256 && !find; i1++){
                brute_force.roundKeys[8].val[0][3] = i1;
                brute_force.roundKeys[8].val[0][2] = i1;
                for(int i2 = 0; i2 < 256 && !find; i2++){
                    brute_force.roundKeys[8].val[1][0] = i2;
                    brute_force.roundKeys[8].val[1][2] = i2;
                    setCipherKey_recomputeFrom8(&brute_force);
                    encrypt128(&brute_force, word, &interne);
                    if(is_equal(ciphertext, interne.inner[21]))
                        find = true;
                }
            }
        }
        clock_t end = clock();

        double timer1 = (end_biclique - start)/ CLOCKS_PER_SEC;
        double timer2 = (end - end_biclique)/ CLOCKS_PER_SEC;

        printf("Clef secrete\n");
        for(int a = 0; a < 4; a++){
            for(int b = 0; b < 4; b++){
                printf("[%x]", secret_key.roundKeys[0].val[a][b]);
            }
            printf("\n");
        }
        printf("\nClef retrouve avec l'attaque en %.2lf s\n", timer1);
        for(int a = 0; a < 4; a++){
            for(int b = 0; b < 4; b++){
                printf("[%x]", attaque.roundKeys[0].val[a][b]);
            }
            printf("\n");
        }
        printf("\nClef retrouve avec le brute force en %.2lf s\n", timer2);
        for(int a = 0; a < 4; a++){
            for(int b = 0; b < 4; b++){
                printf("[%x]", brute_force.roundKeys[0].val[a][b]);
            }
            printf("\n");
        }
        printf("\n\nUne diminution de %.2lf%%\n", (1 - (timer1/timer2)) * 100);
    #endif
}