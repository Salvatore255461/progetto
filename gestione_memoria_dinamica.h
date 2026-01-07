#ifndef GESTIONE_MEMORIA_H_INCLUDED
#define GESTIONE_MEMORIA_H_INCLUDED

// Alloca dinamicamente due matrici parallele (parole e definizioni)
// Restituisce 1 se successo, 0 se errore
int alloca_matrici(char *m_parole[], char *m_def[], int num_righe, int len_parola, int len_def);

// Libera la memoria allocata per le due matrici
void libera_matrici(char *m_parole[], char *m_def[], int num_righe);

#endif // GESTIONE_MEMORIA_H_INCLUDED


