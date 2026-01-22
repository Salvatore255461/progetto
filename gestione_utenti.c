#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestione_utenti.h"

#define FILE_UTENTI "utenti.txt"
#define FILE_TEMP "temp_utenti.txt"

int controlla_credenziali(char *user, char *pass) {              // Controlla se user e pass corrispondono
    FILE *fp = fopen(FILE_UTENTI, "r");
    char u_file[50], p_file[50];
    int score_file;

    if (fp == NULL) return 0;

    while (fscanf(fp, "%s %s %d", u_file, p_file, &score_file) != EOF) {
        if (strcmp(user, u_file) == 0 && strcmp(pass, p_file) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int utente_esiste(char *user) {                  // Controlla se un nome utente è già presente nel file
    FILE *fp = fopen(FILE_UTENTI, "r");
    char u_file[50], p_file[50];
    int score_file;

    if (fp == NULL) return 0; // Se il file non esiste, l'utente non esiste

    while (fscanf(fp, "%s %s %d", u_file, p_file, &score_file) != EOF) {
        if (strcmp(user, u_file) == 0) {
            fclose(fp);
            return 1; // Trovato! Esiste già.
        }
    }
    fclose(fp);
    return 0; // Non trovato
}

void elimina_utente_fisico(char *username) {              // Funzione per eliminare l'utente dal file
    FILE *fp_lettura = fopen(FILE_UTENTI, "r");
    FILE *fp_scrittura = fopen(FILE_TEMP, "w");

    char u[50], p[50];
    int score;
    int eliminato = 0;

    if (fp_lettura == NULL || fp_scrittura == NULL) {
        printf("Errore file durante l'eliminazione.\n");
        return;
    }

    while (fscanf(fp_lettura, "%s %s %d", u, p, &score) != EOF) {        // Copiamo tutto tranne l'utente da eliminare
        if (strcmp(u, username) == 0) {
            eliminato = 1; // Lo saltiamo (non lo scriviamo nel nuovo file)
        } else {
            fprintf(fp_scrittura, "%s %s %d\n", u, p, score);
        }
    }

    fclose(fp_lettura);
    fclose(fp_scrittura);

    if (eliminato) {
        remove(FILE_UTENTI);
        rename(FILE_TEMP, FILE_UTENTI);
        printf("\n>> Utente '%s' eliminato con successo!\n", username);
    } else {
        remove(FILE_TEMP);
        printf("\n>> Errore: Utente non trovato.\n");
    }
}

void registra_utente(char *user, char *pass) {
    // 1. Controllo preliminare se l'utente esiste già
    if (utente_esiste(user)) {
        printf("\n>> ERRORE: L'username '%s' e' gia' in uso! Scegline un altro.\n", user);
        printf("Premi INVIO per continuare...");
        while(getchar() != '\n'); getchar();
        return;
    }

    FILE *fp = fopen(FILE_UTENTI, "a");        // 2. Se non esiste, procediamo con la registrazione
    if (fp != NULL) {
        fprintf(fp, "%s %s 0\n", user, pass);
        fclose(fp);
        printf("Registrazione avvenuta con successo! Punteggio iniziale: 0\n");
        // Piccola pausa per leggere il messaggio
        printf("Premi INVIO per continuare...");
        while(getchar() != '\n'); getchar();
    } else {
        printf("Errore salvataggio utente.\n");
    }
}

int menu_autenticazione(char *username_buffer) {
    int scelta;
    char password[50];
    char temp_user[50]; // Buffer temporaneo per l'eliminazione

    printf("=== AREA UTENTE ===\n");
    printf("1. Login (Accedi e Gioca)\n");
    printf("2. Registrazione (Nuovo utente)\n");
    printf("3. Elimina Account\n"); // Nuova opzione
    printf("0. Indietro\n");
    printf("Scelta: ");

    if (scanf("%d", &scelta) != 1) {
        while(getchar() != '\n');
        return 0;
    }

    if (scelta == 0) return 0;

    // --- CASO 1: LOGIN ---
    if (scelta == 1) {
        printf("\nInserisci Username: ");
        scanf("%s", username_buffer);
        printf("Inserisci Password: ");
        scanf("%s", password);

        if (controlla_credenziali(username_buffer, password)) {
            printf("\nBenvenuto, %s!\n", username_buffer);
            return 1;
        } else {
            printf("\nCredenziali errate o utente non trovato.\n");
            printf("Premi INVIO per continuare...");
            while(getchar() != '\n'); getchar();
            return 0;
        }
    }
    // --- CASO 2: REGISTRAZIONE ---
    else if (scelta == 2) {
        printf("\n(Nuovo) Username: ");
        scanf("%s", username_buffer);
        printf("(Nuova) Password: ");
        scanf("%s", password);

        registra_utente(username_buffer, password);
        // Dopo la registrazione torniamo al menu precedente per sicurezza
        // (o puoi ritornare 1 se vuoi loggarlo subito, ma qui meglio fargli fare il login)
        return 0;
    }
    // --- CASO 3: ELIMINAZIONE UTENTE ---
    else if (scelta == 3) {
        printf("\n--- ELIMINAZIONE ACCOUNT ---\n");
        printf("Inserisci Username da eliminare: ");
        scanf("%s", temp_user);
        printf("Inserisci Password per conferma: ");
        scanf("%s", password);

        if (controlla_credenziali(temp_user, password)) {          // Per sicurezza controlliamo che le credenziali siano giuste prima di eliminare
            char conferma;
            printf("Sei SICURO di voler eliminare '%s'? (s/n): ", temp_user);
            while(getchar() != '\n'); // Pulizia buffer
            scanf("%c", &conferma);

            if (conferma == 's' || conferma == 'S') {
                elimina_utente_fisico(temp_user);
            } else {
                printf("Operazione annullata.\n");
            }
        } else {
            printf("\n>> Errore: Credenziali errate. Impossibile eliminare.\n");
        }

        printf("Premi INVIO per continuare...");
        while(getchar() != '\n'); getchar();
        return 0;
    }

    return 0;
}

void aggiorna_punteggio(char *username, int punti_da_aggiungere) {
    FILE *fp_lettura = fopen(FILE_UTENTI, "r");
    FILE *fp_scrittura = fopen(FILE_TEMP, "w");

    char u[50], p[50];
    int score;
    int trovato = 0;

    if (fp_lettura == NULL || fp_scrittura == NULL) {
        printf("Errore critica file utenti.\n");
        return;
    }

    while (fscanf(fp_lettura, "%s %s %d", u, p, &score) != EOF) {
        if (strcmp(u, username) == 0) {
            score = score + punti_da_aggiungere;
            trovato = 1;
        }
        fprintf(fp_scrittura, "%s %s %d\n", u, p, score);
    }

    fclose(fp_lettura);
    fclose(fp_scrittura);

    if (trovato) {
        remove(FILE_UTENTI);
        rename(FILE_TEMP, FILE_UTENTI);
    } else {
        remove(FILE_TEMP);
    }
}
