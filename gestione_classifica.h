#ifndef GESTIONE_CLASSIFICA_H_INCLUDED
#define GESTIONE_CLASSIFICA_H_INCLUDED

typedef struct Giocatore {
    char username[50];
    char password[50];
    int punteggio;

    struct Giocatore *next; // PUNTATORE AL PROSSIMO NODO
} Giocatore;

void mostra_classifica_ordinata();            // Funzione principale che legge, ordina e stampa la classifica usando le liste

#endif // GESTIONE_CLASSIFICA_H_INCLUDED
