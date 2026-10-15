//Uma estrutura de dados onde os dados são empilhados e o elemento que sai primeiro é sempre o do topo
// LIFO (Last In Frist Out)
/* O modelo intuitivo: existe um monte de pratos
em umaprateleira, sendo conveniente retirar
ou adicionar pratos na parte superior.*/

/*
Implementação da TAD Pilha (LIFO) usando arranjo (vetor).
 *
 * Representação:
 *   - item[]: vetor com capacidade MAX
 *   - topo  : quantidade de elementos na pilha, e também a posição
 *             livre onde entra o próximo elemento
 *             (pilha vazia: topo == 0 | pilha cheia: topo == MA
*/

#include <stdlib.h>
#include "pilha.h"
 
struct pilha {
    int topo;            /* quantidade de elementos na pilha */
    Elemento item[MAX];  /* arranjo que armazena os elementos */
};
 
/* Pcria: cria uma pilha vazia */
Pilha Pcria(void) {
    Pilha p = (Pilha) malloc(sizeof(struct pilha));
    if (p == NULL) 
        return NULL;     /* sem memória */
    p->topo = 0;
    return p;
}
 
/* Pdestroi: destrói a pilha */
void Pdestroi(Pilha p) {
    free(p);             /* free(NULL) é seguro */
}
 
/* Pvazia: examina se a pilha está vazia */
int Pvazia(Pilha p) {
    return p->topo == 0;
}
 
/* Pcheia: examina se a pilha está cheia */
int Pcheia(Pilha p) {
    return p->topo == MAX;
}
 
/* Ptamanho: retorna a quantidade de elementos na pilha */
int Ptamanho(Pilha p) {
    return p->topo;
}
 
/* Pexamina: retorna o elemento no topo da pilha (= top) */
Elemento Pexamina(Pilha p) {
    if (Pvazia(p))
        return PILHA_ERRO;        /* pilha vazia: retorna código de erro */
    return p->item[p->topo - 1];  /* o último inserido está em topo-1 */
}
 
/* Pinsere: insere o elemento no topo da pilha (= push) */
void Pinsere(Pilha p, Elemento elemento) {
    if (Pcheia(p))
        return;                   /* pilha cheia: nada é inserido */
    p->item[p->topo] = elemento;
    p->topo++;
}
 
/* Premove: remove e retorna o elemento no topo da pilha (= pop) */
Elemento Premove(Pilha p) {
    if (Pvazia(p))
        return PILHA_ERRO;        /* pilha vazia: retorna código de erro */
    p->topo--;
    return p->item[p->topo];
}