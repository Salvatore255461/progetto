#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gestione_memoria_dinamica.h"
#include "gestione_griglia.h"

#define NUM_PAROLE 10
#define NOME_FILE "esempio_parole.txt"
#define MAX_TENTATIVI 5000
#define LUNGHEZZA_MAX_DEF 200

int main() {
    FILE *fp;
    char temp_def[LUNGHEZZA_MAX_DEF];
    char temp_parola[100];
    char dummy_buffer[LUNGHEZZA_MAX_DEF];
    int i, j, k;

    srand(time(NULL));

    // 1. Generazione casuale SOLO delle colonne (lunghezza parola)
    int num_lettere_parola = (rand() % 6) + 4;

    // 2. Griglia Statica
    char griglia_di_gioco[MAX_DIM][MAX_DIM];
    inizializza_griglia(griglia_di_gioco);

    printf("Generato numero colonne: %d\n", num_lettere_parola);
    printf("Righe fisse: %d\n", NUM_PAROLE);

    // 3. Allocazione
    char *matrice_parole[NUM_PAROLE];
    char *matrice_def[NUM_PAROLE];

    if (alloca_matrici(matrice_parole, matrice_def, NUM_PAROLE, num_lettere_parola, LUNGHEZZA_MAX_DEF) == 0) return 1;

    // 4. File Input
    fp = fopen(NOME_FILE, "r");
    if (fp == NULL) {
        printf("Errore file.\n");
        libera_matrici(matrice_parole, matrice_def, NUM_PAROLE);
        return 1;
    }

    int righe_totali = 0;
    while (fgets(dummy_buffer, LUNGHEZZA_MAX_DEF, fp) != NULL) righe_totali++;
    int coppie_totali = righe_totali / 2;

    if (coppie_totali < NUM_PAROLE) {
        fclose(fp);
        libera_matrici(matrice_parole, matrice_def, NUM_PAROLE);
        return 1;
    }

    // 5. Estrazione Parole
    int parole_inserite = 0;
    int tentativi = 0;
    int duplicato;

    printf("Estrazione in corso...\n");

    while (parole_inserite < NUM_PAROLE) {
        if (tentativi > MAX_TENTATIVI) break;

        int indice_casuale = rand() % coppie_totali;
        rewind(fp);
        for (j = 0; j < indice_casuale * 2; j++) fgets(dummy_buffer, LUNGHEZZA_MAX_DEF, fp);

        if (fgets(temp_def, LUNGHEZZA_MAX_DEF, fp) == NULL) break;
        if (fgets(temp_parola, 100, fp) == NULL) break;

        temp_def[strcspn(temp_def, "\n")] = 0;
        temp_parola[strcspn(temp_parola, "\n")] = 0;
        temp_def[strcspn(temp_def, "\r")] = 0;
        temp_parola[strcspn(temp_parola, "\r")] = 0;

        int len = strlen(temp_parola);

        if (len == num_lettere_parola) {
            duplicato = 0;
            for (k = 0; k < parole_inserite; k++) {
                if (strcmp(matrice_parole[k], temp_parola) == 0) {
                    duplicato = 1;
                    break;
                }
            }
            if (duplicato == 0) {
                strncpy(matrice_parole[parole_inserite], temp_parola, num_lettere_parola);
                matrice_parole[parole_inserite][num_lettere_parola] = '\0';
                strcpy(matrice_def[parole_inserite], temp_def);
                parole_inserite++;
            }
        }
        tentativi++;
    }
    fclose(fp);

    // --- INSERIMENTO E STAMPA RETTANGOLARE ---

    // Copiamo tutte le parole trovate (fino a un massimo di NUM_PAROLE)
    // Passiamo: Griglia, MatriceParole, Righe (10), Colonne (Random)
    riempi_griglia_con_parole(griglia_di_gioco, matrice_parole, parole_inserite, num_lettere_parola);

    printf("\n=== TABELLONE DI GIOCO (%d Righe x %d Colonne) ===\n", NUM_PAROLE, num_lettere_parola);

    // Passiamo 10 come righe fisse e num_lettere_parola come colonne
    stampa_griglia(griglia_di_gioco, NUM_PAROLE, num_lettere_parola);

    printf("\n=== DEBUG: LEGENDA ===\n");
    for(i=0; i<parole_inserite; i++) {
        printf("Riga %d: %s (Def: %s)\n", i, matrice_parole[i], matrice_def[i]);
    }

    libera_matrici(matrice_parole, matrice_def, NUM_PAROLE);
    return 0;
}
