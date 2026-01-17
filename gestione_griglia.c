#include <stdio.h>
#include <string.h>
#include <stdlib.h> // aggiungo questa libreria per avere la generazione casuale
#include "gestione_griglia.h"



char mio_toupper(char c) {                            // Trasforma una lettera minuscola in maiuscola sottraendo 32 dal codice ASCII.
    if (c >= 'a' && c <= 'z') {                       // Se è già maiuscola o è un simbolo, la lascia invariata.
        return c - 32;
    }
    return c;
}

void inizializza_griglia(char griglia[MAX_DIM][MAX_DIM]) {
    int i, j;
    for (i = 0; i < MAX_DIM; i++) {
        for (j = 0; j < MAX_DIM; j++) {
            griglia[i][j] = ' ';
        }
    }
}

void stampa_griglia(char griglia[MAX_DIM][MAX_DIM], int righe, int colonne) {
    int i, j;

    // Bordo superiore
    printf("\n   ");
    for (j = 0; j < colonne; j++) printf("+---");
    printf("+\n");

    for (i = 0; i < righe; i++) {
        // Numero riga
        printf("%2d ", i);
        // Celle
        for (j = 0; j < colonne; j++) {
            printf("| %c ", griglia[i][j]);
        }
        printf("|\n");

        // Bordo inferiore riga
        printf("   ");
        for (j = 0; j < colonne; j++) printf("+---");
        printf("+\n");
    }
}

void riempi_griglia_con_parole(char griglia[MAX_DIM][MAX_DIM], char *matrice_parole[], int num_righe, int num_colonne) {
    int i, j;
    for (i = 0; i < num_righe; i++) {
        char *parola_corrente = matrice_parole[i];
        for (j = 0; j < num_colonne; j++) {
            if (parola_corrente[j] != '\0') {
                griglia[i][j] = parola_corrente[j];
            }
        }
    }
}

void nascondi_lettere_casuali(char griglia[MAX_DIM][MAX_DIM], int righe, int colonne) {
    int i, j;
    for (i = 0; i < righe; i++) {
        for (j = 0; j < colonne; j++) {
            // Genera numero tra 0 e 99. Se < 60 (60%), nascondi.
            if ((rand() % 100) < 60) {
                griglia[i][j] = '_';
            }
        }
    }
}

// parte di interazione con l'utente e il gioco;

int gestisci_input_utente(char griglia[MAX_DIM][MAX_DIM], char *matrice_parole[], int riga, char *input) {
    // 1. Validazione
    if (riga < 0 || matrice_parole[riga] == NULL) {
        printf("Riga non valida!\n");
        return 0;
    }

    char *parola_soluzione = matrice_parole[riga];
    int len_input = strlen(input);
    int len_soluzione = strlen(parola_soluzione);
    int modifiche = 0;
    int j;

    // CASO A: L'utente ha inserito una sola LETTERA
    if (len_input == 1) {
        char lettera = input[0];

        for (j = 0; j < len_soluzione; j++) {                     // Scorriamo la parola corretta e la confrontiamo la lettera
            if (mio_toupper(parola_soluzione[j]) == mio_toupper(lettera)) {    // Se corrisponde e la casella era nascosta ('_'), la scopriamo
                if (griglia[riga][j] == '_') {
                    griglia[riga][j] = parola_soluzione[j];
                    modifiche++;
                }
            }
        }
    }
    // CASO B: L'utente ha provato a indovinare la PAROLA INTERA
    else {
        int uguali = 1; // Flag: 1 = vero, 0 = falso

        if (len_input != len_soluzione) {            // Se le lunghezze sono diverse, le parole sono sicuramente diverse
            uguali = 0;
        } else {
                    
            for (j = 0; j < len_soluzione; j++) {       // Confronto carattere per carattere
                if (mio_toupper(parola_soluzione[j]) != mio_toupper(input[j])) {
                    uguali = 0;
                    break;
                }
            }
        }

        if (uguali == 1) {        // Ho indovinato! Scopriamo tutta la riga
            for (j = 0; j < len_soluzione; j++) {
                griglia[riga][j] = parola_soluzione[j];
            }
            modifiche = 1;
        }
    }

    return modifiche; // Restituisce >0 se abbiamo scoperto qualcosa
}

int controlla_vittoria(char griglia[MAX_DIM][MAX_DIM], int righe, int colonne) {
    int i, j;
    for (i = 0; i < righe; i++) {
        for (j = 0; j < colonne; j++) {
            if (griglia[i][j] == '_') return 0;        // ritorna 0 se non tutte le lettere sono state scoperte
        }
    }
    return 1; // Vittoria!
}
