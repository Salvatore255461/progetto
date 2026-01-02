#include <stdio.h>
#include <stdlib.h>
#include "gestione.h"

int alloca_matrici(char *m_parole[], char *m_def[], int num_righe, int len_parola, int len_def) {
    int i;
    for (i = 0; i < num_righe; i++) {
        // Allocazione parola (+1 per il terminatore '\0')
        m_parole[i] = (char *)malloc((len_parola + 1) * sizeof(char));

        // Allocazione definizione
        m_def[i] = (char *)malloc(len_def * sizeof(char));

        // Controllo immediato errori: se malloc fallisce, restituisce NULL
        if (m_parole[i] == NULL || m_def[i] == NULL) {
            printf("Errore critico: Memoria esaurita alla riga %d.\n", i);

            // Opzionale: pulizia parziale di ciò che è stato allocato finora
            // per evitare memory leak in caso di crash
            int k;
            for(k=0; k<i; k++) {
                free(m_parole[k]);
                free(m_def[k]);
            }
            return 0; // Restituisce 0 (Fallimento)
        }
    }
    return 1; // Restituisce 1 (Successo)
}

void libera_matrici(char *m_parole[], char *m_def[], int num_righe) {
    int i;
    for (i = 0; i < num_righe; i++) {
        // È sicuro chiamare free su NULL, ma controlliamo per chiarezza
        if (m_parole[i] != NULL) free(m_parole[i]);
        if (m_def[i] != NULL)    free(m_def[i]);
    }
}
