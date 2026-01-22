#ifndef GESTIONE_UTENTI_H_INCLUDED
#define GESTIONE_UTENTI_H_INCLUDED
int menu_autenticazione(char *username_buffer);            // Gestisce l'intero processo di Login o Registrazione.
                                                          // Restituisce 1 se l'utente è autenticato, 0 se annulla.

void aggiorna_punteggio(char *username, int punti_da_aggiungere);      // Aggiunge punti al punteggio attuale dell'utente e salva su file
#endif // GESTIONE_UTENTI_H_INCLUDED
