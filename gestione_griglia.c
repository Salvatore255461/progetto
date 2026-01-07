#include <stdio.h>
#include <string.h>
#include "gestione_griglia.h"

void inizializza_griglia(char griglia[MAX_DIM][MAX_DIM]) {
    int i, j;
    for (i = 0; i < MAX_DIM; i++) {
        for (j = 0; j < MAX_DIM; j++) {
            griglia[i][j] = ' '; // Mettiamo uno spazio invece del punto, è più pulito
        }
    }
}

void stampa_griglia(char griglia[MAX_DIM][MAX_DIM], int righe, int colonne) {
    int i, j;

    // 1. Stampiamo il bordo superiore iniziale
    // Esempio: +---+---+---+
    for (j = 0; j < colonne; j++) {
        printf("+---");
    }
    printf("+\n");

    // 2. Ciclo principale per ogni riga
    for (i = 0; i < righe; i++) {

        // A. Stampa il contenuto della riga con i divisori verticali
        // Esempio: | A | B | C |
        for (j = 0; j < colonne; j++) {
            printf("| %c ", griglia[i][j]);
        }
        printf("|\n"); // Chiude la riga con l'ultima stanghetta

        // B. Stampa il bordo inferiore della riga (che fa da tetto alla successiva)
        // Esempio: +---+---+---+
        for (j = 0; j < colonne; j++) {
            printf("+---");
        }
        printf("+\n");
    }
}

void riempi_griglia_con_parole(char griglia[MAX_DIM][MAX_DIM], char *matrice_parole[], int num_righe, int num_colonne) {
    int i, j;

    for (i = 0; i < num_righe; i++) {
        char *parola_corrente = matrice_parole[i];

        for (j = 0; j < num_colonne; j++) {
            // Copiamo il carattere solo se esiste, altrimenti lasciamo lo spazio
            if (parola_corrente[j] != '\0') {
                griglia[i][j] = parola_corrente[j];
            } else {
                break;
            }
        }
    }
}
