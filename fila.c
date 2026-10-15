/*
 *
 * Implementação da TAD Fila (FIFO) usando arranjo circular.
 *
 * Representação:
 *   - item[]  : vetor com capacidade FILA_MAX
 *   - inicio  : posição do elemento mais antigo (próximo a ser removido)
 *   - tamanho : quantidade de elementos na fila
 *   - O fim da fila é calculado: (inicio + tamanho) % FILA_MAX, que é a
 *     posição livre onde entra o próximo elemento. O uso do resto da
 *     divisão faz o vetor "dar a volta", reaproveitando as posições que
 *     ficam livres no começo depois das remoções.
 *   (fila vazia: tamanho == 0 | fila cheia: tamanho == FILA_MAX)
 */

#include <stdlib.h>
#include "fila.h"

struct fila {
    int inicio;                  /* posição do próximo a ser removido */
    int tamanho;                 /* quantidade de elementos na fila */
    ElementoFila item[FILA_MAX]; /* arranjo circular que armazena os elementos */
};

/* Fcria: cria uma fila vazia */
Fila Fcria(void) {
    Fila f = (Fila) malloc(sizeof(struct fila));
    if (f == NULL)
        return NULL;     /* sem memória */
    f->inicio = 0;
    f->tamanho = 0;
    return f;
}

/* Fdestroi: destrói a fila */
void Fdestroi(Fila f) {
    free(f);             /* free(NULL) é seguro */
}

/* Fvazia: examina se a fila está vazia */
int Fvazia(Fila f) {
    return f->tamanho == 0;
}

/* Fcheia: examina se a fila está cheia */
int Fcheia(Fila f) {
    return f->tamanho == FILA_MAX;
}

/* Ftamanho: retorna a quantidade de elementos na fila */
int Ftamanho(Fila f) {
    return f->tamanho;
}

/* Fexamina: retorna o elemento que será o próximo a ser removido */
ElementoFila Fexamina(Fila f) {
    if (Fvazia(f))
        return FILA_ERRO;         /* fila vazia: retorna código de erro */
    return f->item[f->inicio];    /* o mais antigo está em inicio */
}

/* Finsere: insere o elemento no fim da fila (= enqueue) */
void Finsere(Fila f, ElementoFila elemento) {
    int fim;
    if (Fcheia(f))
        return;                   /* fila cheia: nada é inserido */
    fim = (f->inicio + f->tamanho) % FILA_MAX;  /* posição livre após o último */
    f->item[fim] = elemento;
    f->tamanho++;
}

/* Fremove: remove e retorna o elemento do início da fila (= dequeue) */
ElementoFila Fremove(Fila f) {
    ElementoFila elemento;
    if (Fvazia(f))
        return FILA_ERRO;         /* fila vazia: retorna código de erro */
    elemento = f->item[f->inicio];
    f->inicio = (f->inicio + 1) % FILA_MAX;     /* avança, dando a volta no vetor */
    f->tamanho--;
    return elemento;
}