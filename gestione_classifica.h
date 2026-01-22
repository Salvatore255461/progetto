#ifndef GESTIONE_CLASSIFICA_H_INCLUDED
#define GESTIONE_CLASSIFICA_H_INCLUDED

// Definiamo qui la struttura, così possiamo usarla anche altrove se serve
typedef struct {
    char username[50];
    char password[50];
    int punteggio;
} Giocatore;

void mostra_classifica_ordinata();    // Funzione che legge, ordina e stampa la classifica
#endif // GESTIONE_CLASSIFICA_H_INCLUDED
