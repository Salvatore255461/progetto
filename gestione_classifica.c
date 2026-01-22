#include <stdio.h>
#include <stdlib.h>
#include "gestione_classifica.h"

#define FILE_UTENTI "utenti.txt"
#define MAX_UTENTI 100

void mostra_classifica_ordinata() {
    FILE *fp = fopen(FILE_UTENTI, "r");
    Giocatore lista[MAX_UTENTI]; // Array temporaneo
    int count = 0;
    int i, j;
    Giocatore temp;

    printf("\n=== CLASSIFICA GIOCATORI (Top Score) ===\n");

    if (fp == NULL) {
        printf("Nessun utente registrato o file non trovato.\n");
    } else {
        // 1. CARICAMENTO (Lettura dal file all'array)
        while (fscanf(fp, "%s %s %d", lista[count].username, lista[count].password, &lista[count].punteggio) != EOF) {
            count++;
            if (count >= MAX_UTENTI) break;
        }
        fclose(fp);

        // 2. ORDINAMENTO 
        for (i = 0; i < count - 1; i++) {
            for (j = 0; j < count - i - 1; j++) {
                if (lista[j].punteggio < lista[j+1].punteggio) {
                    // Scambio
                    temp = lista[j];
                    lista[j] = lista[j+1];
                    lista[j+1] = temp;
                }
            }
        }

        // 3. STAMPA
        printf("%-5s %-20s %s\n", "POS", "UTENTE", "PUNTEGGIO");
        printf("---------------------------------------\n");

        for (i = 0; i < count; i++) {
            printf("%-5d %-20s %d pt\n", i + 1, lista[i].username, lista[i].punteggio);
        }
    }

    printf("\nPremi INVIO per tornare al menu...");
    fflush(stdin);
    while(getchar() != '\n'); // Pulizia buffer sicura
    getchar(); // Attesa input
}
