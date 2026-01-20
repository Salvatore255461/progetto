#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gestione_memoria_dinamica.h"
#include "gestione_griglia.h"
#include "gestione_file_di_testo.h"

#define NUM_PAROLE 10
#define NOME_FILE "esempio_parole.txt"
#define LUNGHEZZA_MAX_DEF 200

int main() {
    int i, k; // Variabili per i cicli
    int gioco_in_corso = 1;
    int riga_utente;
    char input_utente[100];

    srand(time(NULL));

    // 1. Setup Iniziale
    int num_lettere_parola = (rand() % 4) + 6; 
    char griglia_di_gioco[MAX_DIM][MAX_DIM];
    inizializza_griglia(griglia_di_gioco);

    printf("--- BENVENUTO AL CRUCIVERBA ---\n");
    printf("Sto caricando parole da %d lettere...\n", num_lettere_parola);

    char *matrice_parole[NUM_PAROLE];
    char *matrice_def[NUM_PAROLE];

    if (alloca_matrici(matrice_parole, matrice_def, NUM_PAROLE, num_lettere_parola, LUNGHEZZA_MAX_DEF) == 0) return 1;

    int parole_trovate = estrai_parole_dal_file(NOME_FILE, num_lettere_parola, NUM_PAROLE, matrice_parole, matrice_def);

    if (parole_trovate == 0) {
        printf("ERRORE: Nessuna parola trovata.\n");
        libera_matrici(matrice_parole, matrice_def, NUM_PAROLE);
        return 0;
    }

    // 2. Preparazione Griglia
    riempi_griglia_con_parole(griglia_di_gioco, matrice_parole, parole_trovate, num_lettere_parola);
    nascondi_lettere_casuali(griglia_di_gioco, parole_trovate, num_lettere_parola);

    // 3. GAME LOOP
    while (gioco_in_corso) {
        
        // A. Stampa stato attuale
        printf("\n\n========================================\n");
        stampa_griglia(griglia_di_gioco, NUM_PAROLE, num_lettere_parola);
        
        printf("\n--- DEFINIZIONI ---\n");
        for(i = 0; i < parole_trovate; i++) {
            printf("Riga %d: %s\n", i, matrice_def[i]);
        }

        // B. Input Utente
        printf("\n(Scrivi -1 alla riga per uscire)\n");
        printf("Inserisci numero RIGA: ");
        scanf("%d", &riga_utente);

        if (riga_utente == -1) break; // Uscita dal gioco

        // Controllo se la riga esiste
        if (riga_utente >= 0 && riga_utente < parole_trovate) {
            
            // CONTROLLO RIGA COMPLETA
            int riga_completa = 1; 
            for (k = 0; k < num_lettere_parola; k++) {
                if (griglia_di_gioco[riga_utente][k] == '_') {
                    riga_completa = 0; // Trovato un buco, non è completa
                    break;
                }
            }

            if (riga_completa == 1) {
                // CASO 1: La riga è piena
                printf("\n>> ATTENZIONE: La riga %d e' gia' completata! Scegline un'altra.\n", riga_utente);
            } 
            else {
                // CASO 2: La riga ha spazi liberi
                printf("Inserisci una LETTERA o la PAROLA intera per la riga %d: ", riga_utente);
                scanf("%s", input_utente);

                int risultato = gestisci_input_utente(griglia_di_gioco, matrice_parole, riga_utente, input_utente);

                if (risultato > 0) {
                    printf("\n>> BRAVO! Hai scoperto qualcosa!\n");
                } else {
                    printf("\n>> PECCATO! La lettera o la parola non corrisponde.\n");
                }

                // Controllo Vittoria
                if (controlla_vittoria(griglia_di_gioco, parole_trovate, num_lettere_parola)) {
                    printf("\n\n***************************************\n");
                    printf("   COMPLIMENTI! HAI COMPLETATO TUTTO!  \n");
                    printf("***************************************\n");
                    stampa_griglia(griglia_di_gioco, NUM_PAROLE, num_lettere_parola);
                    gioco_in_corso = 0; // Impostiamo a 0 per uscire dal while
                }
            }
            // ------------------------------------------------

        } else {
            // Se la riga non è valida
            printf(">> ERRORE: Riga inesistente! Riprova.\n");
        }
    }

    // 4. Pulizia
    libera_matrici(matrice_parole, matrice_def, NUM_PAROLE);
    printf("Grazie per aver giocato!\n");

    return 0;
}
