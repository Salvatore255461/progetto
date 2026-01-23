#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestione_menu.h"
#include "gestione_del_gioco.h"
#include "gestione_classifica.h"
#include "gestione_utenti.h"

int main() {
    int scelta;
    char current_user[50] = "";
    int utente_loggato = 0;

    int scelta_pre_gioco;

    while (1) {
        scelta = mostra_menu_principale(utente_loggato, current_user);

        switch (scelta) {
            case 1: // LOGIN / GIOCA
                // A. Se non sono loggato, provo a fare login
                if (utente_loggato == 0) {
                    if (menu_autenticazione(current_user) == 1) {
                        utente_loggato = 1;
                    }
                }

                // B. Se ora sono loggato
                if (utente_loggato == 1) {
                    // --- SOTTO-MENU PRE-PARTITA ---
                    printf("\n-----------------------------------\n");
                    printf("Ciao %s, cosa vuoi fare?\n", current_user);
                    printf("1. Procedi al Gioco (Scegli difficolta')\n");
                    printf("2. Elimina questo Account\n");
                    printf("0. Annulla e torna al Menu\n");
                    printf("-----------------------------------\n");
                    printf("Scelta: ");

                    if (scanf("%d", &scelta_pre_gioco) != 1) {
                        while(getchar() != '\n'); // Pulisci buffer se inserisce lettere
                        scelta_pre_gioco = 0;
                    }

                    if (scelta_pre_gioco == 1) {
                        // AVVIA IL GIOCO
                        gioca_partita(current_user);
                    }
                    else if (scelta_pre_gioco == 2) {
                        // AVVIA ELIMINAZIONE
                        if (procedura_eliminazione_account(current_user) == 1) {
                            // Se eliminato, logout forzato
                            utente_loggato = 0;
                            strcpy(current_user, "");
                            printf("\n(Sei stato disconnesso automaticamente)\n");
                            // Pausa per leggere
                            printf("Premi INVIO per tornare al menu...");
                            while(getchar() != '\n'); getchar();
                        }
                    }
                    else {
                        printf("\nRitorno al menu principale...\n");
                    }
                    // ------------------------------
                }
                break;

            case 2: // REGOLAMENTO
                visualizza_regolamento();
                break;

            case 3: // CLASSIFICA
                mostra_classifica_ordinata();
                break;

            case 4: // LOGOUT (Visibile solo se loggato)
                if (utente_loggato == 1) {
                    printf("\n>> Logout effettuato. A presto %s!\n", current_user);
                    utente_loggato = 0;
                    strcpy(current_user, "");
                } else {
                    printf("Opzione non valida.\n");
                }
                break;

            case 5: // ELIMINA ACCOUNT
                if (utente_loggato == 1) {
                    if (procedura_eliminazione_account(current_user) == 1) {
                        utente_loggato = 0;
                        strcpy(current_user, "");
                        printf("\n(Sei stato disconnesso automaticamente)\n");
                        while(getchar() != '\n'); getchar();
                    }
                } else {
                    printf("Opzione non valida.\n");
                }
                break;

            case 0:
                printf("Arrivederci!\n");
                return 0;

            default:
                printf("Scelta non valida.\n");
        }
    }
    return 0;
}

