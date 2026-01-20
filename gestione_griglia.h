#ifndef GESTIONE_GRIGLIA_H_INCLUDED
#define GESTIONE_GRIGLIA_H_INCLUDED

#define MAX_DIM 20

void inizializza_griglia(char griglia[MAX_DIM][MAX_DIM]);
void stampa_griglia(char griglia[MAX_DIM][MAX_DIM], int righe, int colonne);
void riempi_griglia_con_parole(char griglia[MAX_DIM][MAX_DIM], char *matrice_parole[], int num_righe, int num_colonne);
void nascondi_lettere_casuali(char griglia[MAX_DIM][MAX_DIM], int righe, int colonne);    //funzione che mi permette di nascondere le lettere in maniera casuale

int gestisci_input_utente(char griglia[MAX_DIM][MAX_DIM], char *matrice_parole[], int riga_scelta, char *input_utente);     // Gestisce l'input: controlla se è una lettera o una parola e aggiorna la griglia
                                                                                                                            // Restituisce 1 se ha indovinato qualcosa, 0 se ha sbagliato

int controlla_vittoria(char griglia[MAX_DIM][MAX_DIM], int righe, int colonne);        // Controlla se ci sono ancora trattini '_' nella griglia
                                                                                       // Restituisce 1 se il gioco è finito (vittoria), 0 se continua

int riga_e_completata(char griglia[MAX_DIM][MAX_DIM], int riga_da_controllare, int num_colonne);  //Controlla se una singola riga è già finita
#endif // GESTIONE_GRIGLIA_H_INCLUDED
