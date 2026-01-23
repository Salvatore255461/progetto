#ifndef GESTIONE_UTENTI_H_INCLUDED
#define GESTIONE_UTENTI_H_INCLUDED

// Gestisce Login o Registrazione.
int menu_autenticazione(char *username_buffer);

// Aggiorna i punti
void aggiorna_punteggio(char *username, int punti_da_aggiungere);

int procedura_eliminazione_account(char *username_loggato);    // Funzione per gestire l'eliminazione dell'account corrente
                                                              // Restituisce 1 se l'account è stato eliminato, 0 se annullato.

#endif // GESTIONE_UTENTI_H_INCLUDED
