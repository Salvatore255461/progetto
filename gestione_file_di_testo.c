#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interfaccia.h"

#define MAX_TENTATIVI 5000
#define LUNGHEZZA_MAX_RIGA 200

int estrai_parole_dal_file(const char *nome_file, int lunghezza_cercata, int max_parole_da_trovare, char *matrice_parole[], char *matrice_def[]) {
    FILE *fp;
    char temp_def[LUNGHEZZA_MAX_RIGA];
    char temp_parola[100];
    char dummy_buffer[LUNGHEZZA_MAX_RIGA];
    int parole_inserite = 0;
    int tentativi = 0;
    int i, j, k, duplicato;

    // 1. Apertura File 
    fp = fopen(nome_file, "r");
    if (fp == NULL) {
        printf("Errore: Impossibile aprire il file '%s'.\n", nome_file);
        return 0; // Restituisce 0 parole trovate
    }

    // 2. Conta le righe totali per sapere il range del random
    int righe_totali = 0;
    while (fgets(dummy_buffer, LUNGHEZZA_MAX_RIGA, fp) != NULL) {
        righe_totali++;
    }

    int coppie_totali = righe_totali / 2;
    if (coppie_totali < max_parole_da_trovare) {
        printf("Attenzione: Il file contiene poche parole (%d coppie).\n", coppie_totali);
        // Non usciamo, proviamo a prendere quello che c'è
    }

    // 3. Ciclo di estrazione
    printf("Sto cercando %d parole di %d lettere nel file...\n", max_parole_da_trovare, lunghezza_cercata);

    while (parole_inserite < max_parole_da_trovare) {
        if (tentativi > MAX_TENTATIVI) {
            break; // Usciamo per evitare loop infiniti
        }

        // Scegli una coppia a caso
        int indice_casuale = rand() % coppie_totali;

        // Torna all'inizio e salta fino alla riga giusta
        rewind(fp);
        for (j = 0; j < indice_casuale * 2; j++) {
            fgets(dummy_buffer, LUNGHEZZA_MAX_RIGA, fp);
        }

        // Leggi Definizione e Parola
        if (fgets(temp_def, LUNGHEZZA_MAX_RIGA, fp) == NULL) break;
        if (fgets(temp_parola, 100, fp) == NULL) break;

        // Pulizia stringhe (\n e \r)
        temp_def[strcspn(temp_def, "\n")] = 0;
        temp_parola[strcspn(temp_parola, "\n")] = 0;
        temp_def[strcspn(temp_def, "\r")] = 0;
        temp_parola[strcspn(temp_parola, "\r")] = 0;

        int len = strlen(temp_parola);

        // Se la lunghezza corrisponde
        if (len == lunghezza_cercata) {
            // Controllo Duplicati
            duplicato = 0;
            for (k = 0; k < parole_inserite; k++) {
                if (strcmp(matrice_parole[k], temp_parola) == 0) {
                    duplicato = 1;
                    break;
                }
            }

            // Inserimento nelle matrici
            if (duplicato == 0) {
                strncpy(matrice_parole[parole_inserite], temp_parola, lunghezza_cercata);
                matrice_parole[parole_inserite][lunghezza_cercata] = '\0'; // Terminatore
                strcpy(matrice_def[parole_inserite], temp_def);

                parole_inserite++;
            }
        }
        tentativi++;
    }

    // 4. Chiusura File
    fclose(fp);

    return parole_inserite; // Restituiamo al main quante ne abbiamo trovate
}
