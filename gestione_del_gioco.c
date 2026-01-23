#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gestione_memoria_dinamica.h"
#include "gestione_griglia.h"
#include "gestione_file_di_testo.h"
#include "gestione_del_gioco.h"
#include "gestione_utenti.h"
#include "gestione_menu.h"

#define NUM_PAROLE 10
#define NOME_FILE "esempio_parole.txt"
#define LUNGHEZZA_MAX_DEF 200

void gioca_partita(char *username) {
    int k;
    int gioco_in_corso = 1;
    int riga_utente;
    char input_utente[100];
    int livello_difficolta;
    int vite = 3;

    srand(time(NULL));

    livello_difficolta = scegli_difficolta();

    // Setup
    int num_lettere_parola = (rand() % 4) + 6;
    char griglia_di_gioco[MAX_DIM][MAX_DIM];
    inizializza_griglia(griglia_di_gioco);

    printf("\n--- PARTITA DI %s (Livello %d) ---\n", username, livello_difficolta);
    printf("Sto caricando parole da %d lettere...\n", num_lettere_parola);

    char *matrice_parole[NUM_PAROLE];
    char *matrice_def[NUM_PAROLE];

    if (alloca_matrici(matrice_parole, matrice_def, NUM_PAROLE, num_lettere_parola, LUNGHEZZA_MAX_DEF) == 0) return;

    int parole_trovate = estrai_parole_dal_file(NOME_FILE, num_lettere_parola, NUM_PAROLE, matrice_parole, matrice_def);

    if (parole_trovate == 0) {
        printf("ERRORE: Nessuna parola trovata.\n");
        libera_matrici(matrice_parole, matrice_def, NUM_PAROLE);
        return;
    }

    riempi_griglia_con_parole(griglia_di_gioco, matrice_parole, parole_trovate, num_lettere_parola);
    applica_difficolta_griglia(griglia_di_gioco, parole_trovate, num_lettere_parola, livello_difficolta);

    // --- GAME LOOP ---
    while (gioco_in_corso) {

        printf("\n\n");
        printf("========================================\n");
        printf("  GIOCATORE: %s\n", username);
        printf("  VITE RIMASTE: %d ", vite);
        printf("[ ");
        for(int v=0; v < vite; v++) printf("* ");
        printf("]");
        if (vite == 1) printf(" <--- ATTENZIONE!");
        printf("\n========================================\n");

        stampa_griglia_con_definizioni(griglia_di_gioco, parole_trovate, num_lettere_parola, matrice_def);

        printf("\n(Scrivi -1 alla riga per tornare al menu)\n");
        printf("Inserisci numero RIGA: ");

        if (scanf("%d", &riga_utente) != 1) {
            printf(">> ERRORE: Devi inserire un NUMERO, non lettere!\n");
            while (getchar() != '\n');
        }
        else {
            if (riga_utente == -1) break;

            if (riga_utente >= 0 && riga_utente < parole_trovate) {

                int riga_completa = 1;
                for (k = 0; k < num_lettere_parola; k++) {
                    if (griglia_di_gioco[riga_utente][k] == '_') {
                        riga_completa = 0;
                        break;
                    }
                }

                if (riga_completa == 1) {
                    printf("\n>> ATTENZIONE: Riga gia' completata!\n");
                } else {
                    printf("Inserisci LETTERA o PAROLA per riga %d: ", riga_utente);
                    scanf("%s", input_utente);

                    int risultato = gestisci_input_utente(griglia_di_gioco, matrice_parole, riga_utente, input_utente);

                    if (risultato > 0) {
                        printf("\n>> BRAVO! Hai indovinato!\n");
                    } else {
                        vite--;
                        printf("\n>> ERRORE! Hai PERSO UNA VITA!\n");

                        // --- GAME OVER ---
                        if (vite <= 0) {
                            printf("\n#######################################\n");
                            printf("#              GAME OVER              #\n");
                            printf("#    Hai esaurito le tue possibilita' #\n");
                            printf("#######################################\n");

                            printf("\nEcco com'era la griglia completa:\n\n");
                            riempi_griglia_con_parole(griglia_di_gioco, matrice_parole, parole_trovate, num_lettere_parola);
                            stampa_griglia_con_definizioni(griglia_di_gioco, parole_trovate, num_lettere_parola, matrice_def);

                            // Uscita immediata
                            gioco_in_corso = 0;
                        }
                    }

                    // --- VITTORIA ---
                    if (gioco_in_corso && controlla_vittoria(griglia_di_gioco, parole_trovate, num_lettere_parola)) {
                        printf("\n\n*** HAI VINTO LA PARTITA! ***\n");
                        stampa_griglia_con_definizioni(griglia_di_gioco, parole_trovate, num_lettere_parola, matrice_def);

                        int punti_vinti = 0;
                        if (livello_difficolta == 1) punti_vinti = 10;
                        else if (livello_difficolta == 2) punti_vinti = 15;
                        else if (livello_difficolta == 3) punti_vinti = 20;

                        printf("\n>> Hai guadagnato %d PUNTI!\n", punti_vinti);
                        aggiorna_punteggio(username, punti_vinti);

                        // MODIFICA: Rimosso "Premi 1 per continuare". Uscita immediata.
                        gioco_in_corso = 0;
                    }
                }
            } else {
                printf(">> Riga non valida.\n");
            }
        }
    }

    libera_matrici(matrice_parole, matrice_def, NUM_PAROLE);
}
    }

    libera_matrici(matrice_parole, matrice_def, NUM_PAROLE);
}
