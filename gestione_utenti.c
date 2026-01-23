#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestione_utenti.h"

#define FILE_UTENTI "utenti.txt"
#define FILE_TEMP "temp_utenti.txt"

int controlla_credenziali(char *user, char *pass) {
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

int utente_esiste(char *user) {
    FILE *fp = fopen(FILE_UTENTI, "r");
    char u_file[50], p_file[50];
    int score_file;

    if (fp == NULL) return 0;

    while (fscanf(fp, "%s %s %d", u_file, p_file, &score_file) != EOF) {
        if (strcmp(user, u_file) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void elimina_utente_fisico(char *username) {
    FILE *fp_lettura = fopen(FILE_UTENTI, "r");
    FILE *fp_scrittura = fopen(FILE_TEMP, "w");

    char u[50], p[50];
    int score;
    int eliminato = 0;

    if (fp_lettura == NULL || fp_scrittura == NULL) {
        printf("Errore file durante l'eliminazione.\n");
        return;
    }

    while (fscanf(fp_lettura, "%s %s %d", u, p, &score) != EOF) {
        if (strcmp(u, username) == 0) {
            eliminato = 1;
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

int registra_utente(char *user, char *pass) {            // Ora restituisce int (1 = OK, 0 = Errore)
    if (utente_esiste(user)) {
        printf("\n>> ERRORE: L'username '%s' e' gia' in uso! Scegline un altro.\n", user);
        printf("Premi INVIO per continuare...");
        while(getchar() != '\n'); getchar();
        return 0;
    }

    FILE *fp = fopen(FILE_UTENTI, "a");
    if (fp != NULL) {
        fprintf(fp, "%s %s 0\n", user, pass);
        fclose(fp);
        printf("Registrazione avvenuta con successo! Punteggio iniziale: 0\n");
        return 1; // Successo
    } else {
        printf("Errore salvataggio utente.\n");
        return 0; // Fallimento
    }
}

// --- FUNZIONI PUBBLICHE ---

int menu_autenticazione(char *username_buffer) {
    int scelta;
    char password[50];
    char temp_user[50];

    printf("\n=== AREA UTENTE ===\n");
    printf("1. Login (Accedi e Gioca)\n");
    printf("2. Registrazione (Nuovo utente)\n");
    printf("3. Elimina Account\n");
    printf("0. Indietro\n");
    printf("Scelta: ");

    if (scanf("%d", &scelta) != 1) {
        while(getchar() != '\n');
        return 0;
    }

    if (scelta == 0) return 0;

    // CASO 1: LOGIN 
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
    // CASO 2: REGISTRAZIONE
    else if (scelta == 2) {
        printf("\n(Nuovo) Username: ");
        scanf("%s", username_buffer);
        printf("(Nuova) Password: ");
        scanf("%s", password);
        
        if (registra_utente(username_buffer, password) == 1) {                         // Se la registrazione va a buon fine (restituisce 1)...
            printf("\n>> Accesso automatico effettuato come %s...\n", username_buffer);
            return 1;                                                                 // ritorniamo 1 così il Main fa partire subito il gioco!
        } else {
            return 0;                                                                 // Altrimenti torniamo al menu
        }
    }
    // CASO 3: ELIMINAZIONE UTENTE
    else if (scelta == 3) {
        printf("\n--- ELIMINAZIONE ACCOUNT ---\n");
        printf("Inserisci Username da eliminare: ");
        scanf("%s", temp_user);
        printf("Inserisci Password per conferma: ");
        scanf("%s", password);

        if (controlla_credenziali(temp_user, password)) {
            char conferma;
            printf("Sei SICURO di voler eliminare '%s'? (s/n): ", temp_user);
            while(getchar() != '\n');
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

