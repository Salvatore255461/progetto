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

    while (1) {
        scelta = mostra_menu_principale(utente_loggato, current_user);

        switch (scelta) {
            case 1: // LOGIN / GIOCA
                if (utente_loggato == 0) {
                                                    // Se NON sono loggato, mostro la schermata di login/registrazione
                    if (menu_autenticazione(current_user) == 1) {
                        utente_loggato = 1;
                        gioca_partita(current_user);
                    }
                } else {                                // Se SONO GIA' loggato, gioco direttamente
                    gioca_partita(current_user);
                }
                break;

            case 2: // REGOLAMENTO
                visualizza_regolamento();
                break;

            case 3: // CLASSIFICA
                mostra_classifica_ordinata();
                break;

            case 4: // LOGOUT / CAMBIA UTENTE
                if (utente_loggato == 1) {
                    printf("\n>> Logout effettuato con successo. A presto %s!\n", current_user);

                    utente_loggato = 0;
                    strcpy(current_user, "");

                    printf("Premi INVIO per continuare...");
                    while(getchar() != '\n'); getchar();
                } else {
                    printf("Opzione non valida (non sei loggato).\n");
                }
                break;

            case 0: // ESCI DAL PROGRAMMA
                printf("Arrivederci!\n");
                return 0;

            default:
                printf("Scelta non valida.\n");
        }
    }
    return 0;
}
