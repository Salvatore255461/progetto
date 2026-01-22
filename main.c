#include <stdio.h>
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
        scelta = mostra_menu_principale();

        switch (scelta) {
            case 1:
                if (utente_loggato == 0) {
                    if (menu_autenticazione(current_user) == 1) {
                        utente_loggato = 1;
                        gioca_partita(current_user);
                    }
                } else {
                    gioca_partita(current_user);
                }
                break;

            case 2:
                visualizza_regolamento();
                break;

            case 3: // CLASSIFICA
                mostra_classifica_ordinata();
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
