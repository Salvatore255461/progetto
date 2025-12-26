#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_PAROLE 10
#define NOME_FILE "esempio_parole.txt"
#define MAX_TENTATIVI 5000
#define LUNGHEZZA_MAX_DEF 200 // Dimensione buffer per la definizione

int main() {
    FILE *fp;
    char temp_def[LUNGHEZZA_MAX_DEF];   // Buffer per leggere la definizione
    char temp_parola[100];              // Buffer per leggere la parola
    char dummy_buffer[LUNGHEZZA_MAX_DEF]; // Buffer per saltare le righe
    int i, j, k;

    // 1. Inizializzazione casualità
    srand(time(NULL));

    // 2. Generazione numero colonne (tra 6 e 9)
    // Questo determina la lunghezza che devono avere le PAROLE (risposte)
    int num_colonne = (rand() % 4) + 6;
    int lunghezza_richiesta = num_colonne; // fgets conta anche il char, ma noi rimuoviamo \n

    printf("Numero colonne generato: %d\n", num_colonne);
    printf("Cerco 10 parole UNICHE di %d lettere (basandomi sul file fornito).\n", num_colonne);

    // 3. Allocazione dinamica: Due matrici parallele
    // matrice_parole: contiene le risposte
    // matrice_def: contiene le definizioni associate
    char *matrice_parole[NUM_PAROLE];
    char *matrice_def[NUM_PAROLE];

    for (i = 0; i < NUM_PAROLE; i++) {
        // Alloco spazio per la parola (risposta)
        matrice_parole[i] = (char *)malloc((num_colonne + 1) * sizeof(char));

        // Alloco spazio per la definizione (fissa a 200 char per sicurezza)
        matrice_def[i] = (char *)malloc(LUNGHEZZA_MAX_DEF * sizeof(char));

        if (matrice_parole[i] == NULL || matrice_def[i] == NULL) {
            printf("Errore memoria.\n");
            return 1;
        }
    }

    // 4. Apertura file
    fp = fopen(NOME_FILE, "r");
    if (fp == NULL) {
        printf("Errore apertura file '%s'.\n", NOME_FILE);
        return 1;
    }

    // Conta le righe totali per capire quante COPPIE ci sono
    int righe_totali = 0;
    while (fgets(dummy_buffer, LUNGHEZZA_MAX_DEF, fp) != NULL) {
        righe_totali++;
    }

    // Ogni coppia è formata da 2 righe (Definizione + Parola)
    int coppie_totali = righe_totali / 2;

    if (coppie_totali < NUM_PAROLE) {
        printf("Errore: Il file contiene solo %d coppie, ne servono almeno %d.\n", coppie_totali, NUM_PAROLE);
        fclose(fp);
        return 1;
    }

    // 5. Riempimento
    int parole_inserite = 0;
    int tentativi = 0;
    int duplicato;

    printf("Inizio estrazione dai %d elementi disponibili...\n", coppie_totali);

    while (parole_inserite < NUM_PAROLE) {

        if (tentativi > MAX_TENTATIVI) {
            printf("\nERRORE: Impossibile trovare abbastanza parole uniche di lunghezza %d.\n", num_colonne);
            break;
        }

        // Genera indice per una COPPIA (da 0 a coppie_totali-1)
        int indice_casuale = rand() % coppie_totali;

        rewind(fp);

        // SALTO LE RIGHE: Per arrivare alla coppia X, devo saltare X * 2 righe
        for (j = 0; j < indice_casuale * 2; j++) {
            fgets(dummy_buffer, LUNGHEZZA_MAX_DEF, fp);
        }

        // ORA LEGGO LA COPPIA GIUSTA
        // 1. Leggo la definizione (riga pari)
        if (fgets(temp_def, LUNGHEZZA_MAX_DEF, fp) == NULL) break;
        // 2. Leggo la parola (riga dispari)
        if (fgets(temp_parola, 100, fp) == NULL) break;

        // PULIZIA DELLE STRINGHE (Rimuovo il \n finale letto da fgets)
        // La funzione strcspn trova l'indice del carattere \n e lo sostituisce con \0
        temp_def[strcspn(temp_def, "\n")] = 0;
        temp_parola[strcspn(temp_parola, "\n")] = 0;
        // Rimuovo anche \r nel caso il file sia stato fatto su Windows
        temp_def[strcspn(temp_def, "\r")] = 0;
        temp_parola[strcspn(temp_parola, "\r")] = 0;

        // --- VERIFICA LUNGHEZZA ---
        int len = strlen(temp_parola);

        if (len == num_colonne) {

            // --- VERIFICA UNICITÀ ---
            duplicato = 0;
            for (k = 0; k < parole_inserite; k++) {
                if (strcmp(matrice_parole[k], temp_parola) == 0) {
                    duplicato = 1;
                    break;
                }
            }

            if (duplicato == 0) {
                // Copio Parola
                strncpy(matrice_parole[parole_inserite], temp_parola, num_colonne);
                matrice_parole[parole_inserite][num_colonne] = '\0';

                // Copio Definizione
                strcpy(matrice_def[parole_inserite], temp_def);

                // STAMPO SUBITO SUL PROMPT COME RICHIESTO
                printf("Inserita (%d): %s -> (Def: %s)\n",
                       parole_inserite + 1, temp_parola, temp_def);

                parole_inserite++;
            }
        }

        tentativi++;
    }

    fclose(fp);

    // 6. Stampa riepilogativa finale
    if (parole_inserite > 0) {
        printf("\n--- RISULTATO FINALE ---\n");
        for (i = 0; i < parole_inserite; i++) {
            printf("Riga %d [Parola: %s] \n       [Definizione: %s]\n",
                   i, matrice_parole[i], matrice_def[i]);
        }
    }

    // 7. Liberazione memoria (per entrambe le matrici)
    for (i = 0; i < NUM_PAROLE; i++) {
        free(matrice_parole[i]);
        free(matrice_def[i]);
    }

    return 0;
}
