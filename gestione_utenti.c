#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interfaccia.h"

#define FILE_UTENTI "utenti.txt"
#define FILE_TEMP "temp_utenti.txt"

// --- FUNZIONI INTERNE ---

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

void elimina_utente_fisico(char *username) {                    // Funzione di eliminazione
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
        printf("\n>> Account '%s' eliminato definitivamente!\n", username);
    } else {
        remove(FILE_TEMP);
    }
}

int registra_utente(char *user, char *pass) {
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
        return 1;
    } else {
        printf("Errore salvataggio utente.\n");
        return 0;
    }
}

// --- FUNZIONI PUBBLICHE ---

int menu_autenticazione(char *username_buffer) {
    int scelta;
    char password[50];

    printf("\n=== AREA UTENTE ===\n");
    printf("1. Login (Accedi e Gioca)\n");
    printf("2. Registrazione (Nuovo utente)\n");
    printf("0. Indietro\n");
    printf("Scelta: ");

    if (scanf("%d", &scelta) != 1) {
        while(getchar() != '\n');
        return 0;
    }

    if (scelta == 0) return 0;

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
    else if (scelta == 2) {
        printf("\n(Nuovo) Username: ");
        scanf("%s", username_buffer);
        printf("(Nuova) Password: ");
        scanf("%s", password);

        if (registra_utente(username_buffer, password) == 1) {
            printf("\n>> Accesso automatico effettuato come %s...\n", username_buffer);
            return 1;
        } else {
            return 0;
        }
    }

    return 0;
}

// Funzione che viene chiamata dal Main SOLO se l'utente è loggato
int procedura_eliminazione_account(char *username_loggato) {
    char password[50];
    char conferma;

    printf("\n--- ELIMINAZIONE ACCOUNT: %s ---\n", username_loggato);
    printf("Per sicurezza, conferma la tua Password: ");
    scanf("%s", password);

    // Controlliamo se la password corrisponde all'utente loggato
    if (controlla_credenziali(username_loggato, password)) {

        printf("ATTENZIONE: L'operazione e' irreversibile.\n");
        printf("Sei SICURO di voler eliminare il tuo account? (s/n): ");
        while(getchar() != '\n'); // Pulisci buffer
        scanf("%c", &conferma);

        if (conferma == 's' || conferma == 'S') {
            elimina_utente_fisico(username_loggato);
            return 1; // Restituisce 1 = Eliminazione avvenuta
        } else {
            printf("Operazione annullata.\n");
            return 0;
        }
    } else {
        printf("\n>> Password errata. Impossibile eliminare l'account.\n");
        printf("Premi INVIO per continuare...");
        while(getchar() != '\n'); getchar();
        return 0;
    }
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

