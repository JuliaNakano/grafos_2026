/*
 * TAD Fila (FIFO = First-In-First-Out), implementada com arranjo (vetor)
 * circular. Interface conforme o enunciado do Trabalho Prático (base).
 */
#ifndef FILA_H
#define FILA_H

/* Capacidade máxima da fila (tamanho pré-definido do arranjo) */
#define FILA_MAX 100

/* Tipo do elemento armazenado na fila */
typedef int ElementoFila;

/* Valor retornado por Fexamina/Fremove quando a fila está vazia */
#define FILA_ERRO (-1)

/* Fila é um ponteiro para struct; os detalhes ficam escondidos em fila.c */
struct fila;
typedef struct fila *Fila;

/* Fcria: cria uma fila vazia. Retorna NULL se faltar memória. */
Fila Fcria(void);

/* Fdestroi: destrói a fila e libera a memória alocada. */
void Fdestroi(Fila f);

/* Fvazia: examina se a fila está vazia (1 = vazia, 0 = não vazia). */
int Fvazia(Fila f);

/* Fcheia: examina se a fila está cheia (1 = cheia, 0 = não cheia). */
int Fcheia(Fila f);

/* Ftamanho: retorna a quantidade de elementos na fila. */
int Ftamanho(Fila f);

/* Fexamina: retorna o elemento que será o próximo a ser removido, sem removê-lo. */
ElementoFila Fexamina(Fila f);

/* Finsere: insere o elemento no fim da fila (= enqueue). */
void Finsere(Fila f, ElementoFila elemento);

/* Fremove: remove e retorna o elemento do início da fila (= dequeue). */
ElementoFila Fremove(Fila f);

#endif /* FILA_H */