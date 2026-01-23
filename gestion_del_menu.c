#include <stdio.h>
#include <stdlib.h>
#include "gestione_menu.h"

#define FILE_REGOLAMENTO "regolamento.txt"

int mostra_menu_principale(int utente_loggato, char *nome_utente) {
    int scelta;

    printf("\n\n");
    printf("=================================\n");
    printf("      PAROLE CROCIATE - MENU     \n");
    printf("=================================\n");

    if (utente_loggato == 0) {
        // CASO A: Nessuno loggato
        printf("1. Accedi / Registrati e GIOCA\n");
    } else {
        // CASO B: Utente loggato
        printf("1. GIOCA (Utente: %s)\n", nome_utente);
    }

    printf("2. Regolamento\n");
    printf("3. Classifica\n");

    if (utente_loggato == 1) {                        // Mostriamo questa opzione SOLO se sei loggato
        printf("4. Logout / Cambia Utente\n");
    }

    printf("0. Esci\n");
    printf("---------------------------------\n");
    printf("Inserisci scelta: ");

    while (scanf("%d", &scelta) != 1) {
        printf("Inserisci un numero valido: ");
        while(getchar() != '\n');
    }
    return scelta;
}

int scegli_difficolta() {
    int liv;
    printf("\n=== SCEGLI LA DIFFICOLTA' ===\n");
    printf("1. FACILE    (Meta' lettere visibili) [Vittoria: +10 pt]\n");
    printf("2. NORMALE   (3 lettere visibili)     [Vittoria: +15 pt]\n");
    printf("3. DIFFICILE (Griglia vuota)          [Vittoria: +20 pt]\n");
    printf("-----------------------------\n");
    printf("Scelta: ");

    while (scanf("%d", &liv) != 1 || liv < 1 || liv > 3) {
        printf(">> Errore: Inserisci 1, 2 o 3: ");
        while (getchar() != '\n');
    }
    return liv;
}

void visualizza_regolamento() {
    FILE *fp = fopen(FILE_REGOLAMENTO, "r");
    char buffer[255];

    printf("\n\n=== REGOLAMENTO DI GIOCO ===\n\n");

    if (fp == NULL) {
        printf("Errore: Impossibile trovare il file '%s'.\n", FILE_REGOLAMENTO);
    } else {
        while (fgets(buffer, 255, fp) != NULL) {
            printf("%s", buffer);
        }
        fclose(fp);
    }
    printf("\n\nPremi INVIO per tornare al menu...");
    fflush(stdin); getchar();
    if (getchar() != '\n');
}
