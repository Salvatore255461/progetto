#ifndef GESTIONE_GRIGLIA_H_INCLUDED
#define GESTIONE_GRIGLIA_H_INCLUDED

#define MAX_DIM 20

// Inizializza tutto a '.'
void inizializza_griglia(char griglia[MAX_DIM][MAX_DIM]);

// Stampa la griglia usando righe e colonne separate
void stampa_griglia(char griglia[MAX_DIM][MAX_DIM], int righe, int colonne);

// Copia le parole nella griglia
void riempi_griglia_con_parole(char griglia[MAX_DIM][MAX_DIM], char *matrice_parole[], int num_righe, int num_colonne);

#endif // GESTIONE_GRIGLIA_H_INCLUDED
