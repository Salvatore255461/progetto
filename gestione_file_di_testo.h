#ifndef GESTIONE_FILE_DI_TESTO_H_INCLUDED
#define GESTIONE_FILE_DI_TESTO_H_INCLUDED

// Funzione che apre il file, cerca le parole della lunghezza giusta e riempie le matrici.
// Restituisce il numero di parole effettivamente trovate.
int estrai_parole_dal_file(const char *nome_file,int lunghezza_cercata,int max_parole_da_trovare,char *matrice_parole[],char *matrice_def[]);

#endif // GESTIONE_FILE_DI_TESTO_H_INCLUDED
