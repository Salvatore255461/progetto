#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gestione_memoria_dinamica.h"
#include "gestione_griglia.h"
#include "gestione_file_di_testo.h"    // introduzione di questo nuovo file per la gestine del file di testo;

#define NUM_PAROLE 10
#define NOME_FILE "esempio_parole.txt"
#define LUNGHEZZA_MAX_DEF 200

int main() {
    int i;
    int gioco_in_corso = 1; // Variabile per controllare un loop che si interromperà al completamento della griglia;
    int riga_utente;
    char input_utente[100]; // in questo vettore andremo a riportare la lettera o parola scelta dall'utente;

    srand(time(NULL));

    // 1. GENERAZIONE NUMERO CASUALE
    int num_lettere_parola = (rand() % 4) + 6;
    char griglia_di_gioco[MAX_DIM][MAX_DIM];
    inizializza_griglia(griglia_di_gioco);

    printf("--- BENVENUTO AL CRUCIVERBA ---\n");
                                                    // da questa riga ho cacciato la printf riguardo il caricamento delle parole;
    // ALLOCAZIONE MEMORIA
    char *matrice_parole[NUM_PAROLE];
    char *matrice_def[NUM_PAROLE];

    if (alloca_matrici(matrice_parole, matrice_def, NUM_PAROLE, num_lettere_parola, LUNGHEZZA_MAX_DEF) == 0) return 1;
    
    // ESTRAZIONE PAROLE 
    int parole_trovate = estrai_parole_dal_file(NOME_FILE, num_lettere_parola, NUM_PAROLE, matrice_parole, matrice_def); // Passiamo il nome del file, la lunghezza che vogliamo e le matrici vuote da riempire

    if (parole_trovate == 0) {     // controllo di sicurezza;
        printf("ERRORE: Nessuna parola trovata.\n");
        libera_matrici(matrice_parole, matrice_def, NUM_PAROLE);
        return 0;
    }

    // 2. GESTIONE GRIGLIA E RIEMPIMENTO
    riempi_griglia_con_parole(griglia_di_gioco, matrice_parole, parole_trovate, num_lettere_parola);
    nascondi_lettere_casuali(griglia_di_gioco, parole_trovate, num_lettere_parola);

    // 3. GAME LOOP                             // da qui in poi ci sarebbe l'effettiva interazione del gioco con l'utente
    while (gioco_in_corso) {

        // A. Stampa stato attuale
        printf("\n\n========================================\n");
        stampa_griglia(griglia_di_gioco, NUM_PAROLE, num_lettere_parola);                //Ogni volta la griglia mi dovrà stampare la griglia aggiornata e le definzioni, finchè non sarà completata;

        printf("\n--- DEFINIZIONI ---\n");
        for(i = 0; i < parole_trovate; i++) {
            printf("Riga %d: %s\n", i, matrice_def[i]);
        }

        // B. Input Utente
        printf("\n(Scrivi -1 alla riga per uscire)\n");
        printf("Inserisci numero RIGA: ");
        scanf("%d", &riga_utente);

        if (riga_utente == -1) break;                                    // uscita forzata nel caso si voglia smettere di giocare;

        if (riga_utente < 0 || riga_utente >= parole_trovate) {
            printf(">> ERRORE: Riga inesistente! Riprova.\n");
            continue;
        }

        printf("Inserisci una LETTERA o la PAROLA intera per la riga %d: ", riga_utente);
        scanf("%s", input_utente); // Legge la stringa (lettera o parola)

        // C. Elaborazione Input
        int risultato = gestisci_input_utente(griglia_di_gioco, matrice_parole, riga_utente, input_utente);

        // D. Controllo Vittoria
        if (controlla_vittoria(griglia_di_gioco, parole_trovate, num_lettere_parola)) {
            printf("\n\n***************************************\n");
            printf("   COMPLIMENTI! HAI COMPLETATO TUTTO!  \n");
            printf("***************************************\n");
            stampa_griglia(griglia_di_gioco, NUM_PAROLE, num_lettere_parola); // Stampa finale
            gioco_in_corso = 0; // Esce dal while
        }
    }

    // 4. Pulizia
    libera_matrici(matrice_parole, matrice_def, NUM_PAROLE);  // libera lo spazio che abbiamo preso prima con la malloc
    printf("Grazie per aver giocato!\n");

    return 0;
}
