#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Serve per rand()
#include "gestione_griglia.h"

char mio_toupper(char c) {                            // Trasforma una lettera minuscola in maiuscola sottraendo 32 dal codice ASCII.
    if (c >= 'a' && c <= 'z') {
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

void applica_difficolta_griglia(char griglia[MAX_DIM][MAX_DIM], int righe, int colonne, int livello) {
    int i;
    int lettere_da_mantenere;
    int lettere_da_nascondere;
    int nascoste_finora;
    int indice_casuale;

    for (i = 0; i < righe; i++) {

        // 1. Calcolo del numero di lettere da rivelare in base al tipo di difficoltà
        if (livello == 1) {
            // FACILE: Metà delle lettere (divisione intera approssima per difetto)
            lettere_da_mantenere = colonne / 2;
        }
        else if (livello == 2) {
            // NORMALE: Fisse 3 lettere
            lettere_da_mantenere = 3;
        }
        else {
            // DIFFICILE:(tutto nascosto)
            lettere_da_mantenere = 0;
        }

        // Calcoliamo quante caselle dobbiamo trasformare in '_'
        lettere_da_nascondere = colonne - lettere_da_mantenere;
        nascoste_finora = 0;

        // 2. CICLO PER NASCONDERE LE LETTERE
        while (nascoste_finora < lettere_da_nascondere) {
            indice_casuale = rand() % colonne; // Scegli una colonna a caso

            // Se la casella non è già stata nascosta, la nascondiamo ora
            if (griglia[i][indice_casuale] != '_') {
                griglia[i][indice_casuale] = '_';
                nascoste_finora++;
            }
        }
    }
}

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

        // Scorriamo la parola corretta
        for (j = 0; j < len_soluzione; j++) {
            // Confrontiamo usando la nostra funzione manuale
            if (mio_toupper(parola_soluzione[j]) == mio_toupper(lettera)) {
                // Se corrisponde e la casella era nascosta ('_'), la scopriamo
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

        // Se le lunghezze sono diverse, le parole sono sicuramente diverse
        if (len_input != len_soluzione) {
            uguali = 0;
        } else {
            // Confronto manuale carattere per carattere
            for (j = 0; j < len_soluzione; j++) {
                if (mio_toupper(parola_soluzione[j]) != mio_toupper(input[j])) {
                    uguali = 0;
                    break;
                }
            }
        }

        if (uguali == 1) {
            // Ha indovinato! Scopriamo tutta la riga
            for (j = 0; j < len_soluzione; j++) {
                griglia[riga][j] = parola_soluzione[j];
            }
            modifiche = 1;
        }
    }

    return modifiche;         // Restituisce > 0 se abbiamo scoperto qualcosa
}

int controlla_vittoria(char griglia[MAX_DIM][MAX_DIM], int righe, int colonne) {
    int i, j;
    for (i = 0; i < righe; i++) {
        for (j = 0; j < colonne; j++) {
            // Se troviamo anche solo un trattino, non hai ancora vinto
            if (griglia[i][j] == '_') return 0;
        }
    }
    return 1;             // Vittoria!
}


int riga_e_completata(char griglia[MAX_DIM][MAX_DIM], int riga, int colonne) {
    int j;
    for (j = 0; j < colonne; j++) {
        // Se trovo un buco ('_'), la riga NON è completa
        if (griglia[riga][j] == '_') {
            return 0;
        }
    }
                            // la riga è completa
    return 1;
}
