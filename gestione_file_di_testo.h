#ifndef GESTIONE_FILE_DI_TESTO_H_INCLUDED
#define GESTIONE_FILE_DI_TESTO_H_INCLUDED

int estrai_parole_dal_file(const char *nome_file,int lunghezza_cercata,int max_parole_da_trovare,char *matrice_parole[],char *matrice_def[]);      // apre il file e cerca le parole della lunghezza giusta
                                                                                                                                                    // Restituisce il numero di parole effettivamente trovate.
#endif // GESTIONE_FILE_DI_TESTO_H_INCLUDED
