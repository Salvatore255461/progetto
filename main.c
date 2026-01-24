#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interfaccia.h"

int main() {
    int scelta;
    char current_user[50] = "";
    int utente_loggato = 0;

    while (1) {
        scelta = mostra_menu_principale(utente_loggato, current_user);

        switch (scelta) {
            case 1: // LOGIN / GIOCA
                // A. Se non sono loggato, faccio login
                if (utente_loggato == 0) {
                    if (menu_autenticazione(current_user) == 1) {
                        utente_loggato = 1;
                        // Appena loggato, vado SUBITO alla scelta difficoltà
                        gioca_partita(current_user);
                    }
                }
                // B. Se ero già loggato, vado SUBITO alla scelta difficoltà
                else {
                    gioca_partita(current_user);
                }
                break;

            case 2: // REGOLAMENTO
                visualizza_regolamento();
                break;

            case 3: // CLASSIFICA
                mostra_classifica_ordinata();
                break;

            case 4: // LOGOUT
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
