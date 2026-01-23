#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestione_classifica.h"

#define FILE_UTENTI "utenti.txt"

Giocatore* inserisci_in_testa(Giocatore *testa, char *u, char *p, int s) {                // Funzione per aggiungere un nuovo nodo in testa alla lista
    Giocatore *nuovo_nodo = (Giocatore*) malloc(sizeof(Giocatore));                        // Allocazione dinamica del nodo

    if (nuovo_nodo == NULL) {
        printf("Errore di memoria (malloc fallita).\n");
        return testa;
    }
    strcpy(nuovo_nodo->username, u);
    strcpy(nuovo_nodo->password, p);
    nuovo_nodo->punteggio = s;

    nuovo_nodo->next = testa; // Il nuovo nodo punta alla vecchia testa
    return nuovo_nodo;        // La nuova testa è il nuovo nodo
}

void libera_lista(Giocatore *testa) {                    // Funzione per liberare tutta la memoria della lista alla fine
    Giocatore *temp;
    while (testa != NULL) {
        temp = testa;       // Salviamo il nodo corrente
        testa = testa->next; // Ci spostiamo al prossimo
        free(temp);         // Liberiamo quello salvato
    }
}

// --- FUNZIONE PRINCIPALE ---

void mostra_classifica_ordinata() {
    FILE *fp = fopen(FILE_UTENTI, "r");

    // La lista parte vuota (testa punta a NULL)
    Giocatore *head = NULL;

    char u[50], p[50];
    int s;

    // Variabili per l'ordinamento e la stampa
    Giocatore *i, *j;
    int temp_score;
    char temp_user[50];
    char temp_pass[50];
    int pos = 1;

    printf("\n=== CLASSIFICA GIOCATORI (Linked List) ===\n");

    if (fp == NULL) {
        printf("Nessun utente registrato o file non trovato.\n");
    } else {
        // A. CARICAMENTO: Leggiamo dal file e creiamo la lista dinamica
        while (fscanf(fp, "%s %s %d", u, p, &s) != EOF) {
            head = inserisci_in_testa(head, u, p, s);
        }
        fclose(fp);

        // Se la lista è vuota
        if (head == NULL) {
            printf("Nessun giocatore in classifica.\n");
        }
        else {
            // B. ORDINAMENTO (Bubble Sort su Lista)
            // Scambiamo i DATI all'interno dei nodi
            for (i = head; i != NULL; i = i->next) {
                for (j = i->next; j != NULL; j = j->next) {
                    // Ordinamento Decrescente (dal più grande al più piccolo)
                    if (j->punteggio > i->punteggio) {
                        // SCAMBIO PUNTEGGIO
                        temp_score = i->punteggio;
                        i->punteggio = j->punteggio;
                        j->punteggio = temp_score;

                        // SCAMBIO NOME
                        strcpy(temp_user, i->username);
                        strcpy(i->username, j->username);
                        strcpy(j->username, temp_user);

                        // SCAMBIO PASSWORD (serve per mantenere coerenza dati)
                        strcpy(temp_pass, i->password);
                        strcpy(i->password, j->password);
                        strcpy(j->password, temp_pass);
                    }
                }
            }

            // C. STAMPA: Scorriamo la lista dall'inizio alla fine
            printf("%-5s %-20s %s\n", "POS", "UTENTE", "PUNTEGGIO");
            printf("---------------------------------------\n");

            Giocatore *corrente = head;
            while (corrente != NULL) {
                printf("%-5d %-20s %d pt\n", pos, corrente->username, corrente->punteggio);
                corrente = corrente->next; // Passa al prossimo nodo
                pos++;
            }
        }

        // D. PULIZIA: Liberiamo la memoria allocata con malloc
        libera_lista(head);
    }

    printf("\nPremi INVIO per tornare al menu...");
    fflush(stdin);
    while(getchar() != '\n');
    getchar();
}
