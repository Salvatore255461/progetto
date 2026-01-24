#ifndef PROTOTIPI_H_INCLUDED
#define PROTOTIPI_H_INCLUDED

#include <stdio.h> // Serve per il tipo FILE*

// --- COSTANTI GLOBALI ---
#define MAX_DIM 15 // Dimensione massima della griglia

// --- STRUTTURE DATI ---

// Struttura per la Classifica (Lista Concatenata)
typedef struct Giocatore {
    char username[50];
    char password[50];
    int punteggio;
    struct Giocatore *next; // Puntatore al prossimo nodo
} Giocatore;

// ==========================================
//          ELENCO DI TUTTE LE FUNZIONI
// ==========================================

// --- GESTIONE MENU ---
int mostra_menu_principale(int utente_loggato, char *nome_utente);
int scegli_difficolta();
void visualizza_regolamento();

// --- GESTIONE UTENTI ---
int menu_autenticazione(char *username_buffer);
void aggiorna_punteggio(char *username, int punti_da_aggiungere);
int procedura_eliminazione_account(char *username_loggato);

// --- GESTIONE CLASSIFICA ---
void mostra_classifica_ordinata();

// --- GESTIONE GRIGLIA ---
void inizializza_griglia(char griglia[MAX_DIM][MAX_DIM]);
void stampa_griglia(char griglia[MAX_DIM][MAX_DIM], int righe, int colonne); // (Versione base)
void stampa_griglia_con_definizioni(char griglia[MAX_DIM][MAX_DIM], int righe, int colonne, char *definizioni[]);
void riempi_griglia_con_parole(char griglia[MAX_DIM][MAX_DIM], char *parole[], int num_parole, int lunghezza);
void applica_difficolta_griglia(char griglia[MAX_DIM][MAX_DIM], int righe, int colonne, int livello);

// --- GESTIONE MEMORIA DINAMICA ---
int alloca_matrici(char *parole[], char *definizioni[], int num_parole, int len_parola, int len_def);
void libera_matrici(char *parole[], char *definizioni[], int num_parole);

// --- GESTIONE FILE DI TESTO ---
int estrai_parole_dal_file(const char *nome_file, int num_lettere, int max_parole, char *parole[], char *definizioni[]);

// --- GESTIONE DEL GIOCO ---
void gioca_partita(char *username);
int gestisci_input_utente(char griglia[MAX_DIM][MAX_DIM], char *parole[], int riga_scelta, char *input);
int controlla_vittoria(char griglia[MAX_DIM][MAX_DIM], int righe, int colonne);

#endif // PROTOTIPI_H_INCLUDED
