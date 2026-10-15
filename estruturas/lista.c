/*
 *
 * Implementação da TAD Lista usando lista dinâmica duplamente encadeada,
 * conforme o Esquema 1 do enunciado.
 *
 * Representação:
 *   - Cabeçalho (struct lista): tamanho, inicio e fim
 *   - Nós (struct nolista)    : ant, valor e prox
 *   - ant do primeiro nó e prox do último nó são NULL
 *   - lista vazia: tamanho == 0, inicio == NULL e fim == NULL
 */

#include <stdlib.h>
#include "lista.h"

/* Nó da lista */
typedef struct nolista {
    struct nolista *ant;   /* nó anterior (NULL no primeiro) */
    ElementoLista valor;   /* dado armazenado */
    struct nolista *prox;  /* próximo nó (NULL no último) */
} NoLista;

/* Cabeçalho da lista */
struct lista {
    int tamanho;           /* quantidade de elementos na lista */
    NoLista *inicio;       /* primeiro nó */
    NoLista *fim;          /* último nó */
};

/* Lbusca (auxiliar): retorna o nó da posição indicada, ou NULL se a
 * posição for inválida. Percorre a partir da ponta mais próxima,
 * aproveitando que a lista é duplamente encadeada. */
static NoLista *Lbusca(Lista l, int posicao) {
    NoLista *no;
    int i;
    if (posicao < 1 || posicao > l->tamanho)
        return NULL;
    if (posicao <= l->tamanho / 2) {
        no = l->inicio;                     /* percorre do início para o fim */
        for (i = 1; i < posicao; i++)
            no = no->prox;
    } else {
        no = l->fim;                        /* percorre do fim para o início */
        for (i = l->tamanho; i > posicao; i--)
            no = no->ant;
    }
    return no;
}

/* Lcria: cria uma lista vazia */
Lista Lcria(void) {
    Lista l = (Lista) malloc(sizeof(struct lista));
    if (l == NULL)
        return NULL;     /* sem memória */
    l->tamanho = 0;
    l->inicio = NULL;
    l->fim = NULL;
    return l;
}

/* Ldestroi: destrói a lista */
void Ldestroi(Lista l) {
    NoLista *no, *prox;
    if (l == NULL)
        return;
    no = l->inicio;
    while (no != NULL) {                    /* libera cada nó */
        prox = no->prox;
        free(no);
        no = prox;
    }
    free(l);                                /* libera o cabeçalho */
}

/* Lvazia: examina se a lista está vazia */
int Lvazia(Lista l) {
    return l->tamanho == 0;
}

/* Lcheia: examina se a lista está cheia (sem memória para um novo nó) */
int Lcheia(Lista l) {
    NoLista *teste = (NoLista *) malloc(sizeof(NoLista));
    (void) l;                               /* l não é usado: a lista é dinâmica */
    if (teste == NULL)
        return 1;
    free(teste);
    return 0;
}

/* Ltamanho: retorna a quantidade de elementos na lista */
int Ltamanho(Lista l) {
    return l->tamanho;
}

/* Lexamina: retorna o elemento na posição indicada */
ElementoLista Lexamina(Lista l, int posicao) {
    NoLista *no = Lbusca(l, posicao);
    if (no == NULL)
        return LISTA_ERRO;        /* posição inválida: retorna código de erro */
    return no->valor;
}

/* Llocaliza: retorna a posição do elemento (0 se não existir) */
int Llocaliza(Lista l, ElementoLista elemento) {
    NoLista *no = l->inicio;
    int posicao = 1;
    while (no != NULL) {
        if (no->valor == elemento)
            return posicao;           /* primeira ocorrência */
        no = no->prox;
        posicao++;
    }
    return 0;                         /* não encontrado */
}

/* Linsere: insere o elemento na posição indicada */
void Linsere(Lista l, ElementoLista elemento, int posicao) {
    NoLista *novo, *depois;
    if (posicao < 1 || posicao > l->tamanho + 1)
        return;                       /* posição inválida: nada é inserido */
    novo = (NoLista *) malloc(sizeof(NoLista));
    if (novo == NULL)
        return;                       /* sem memória: nada é inserido */
    novo->valor = elemento;

    /* "depois" é o nó que ficará logo após o novo (NULL se for no fim) */
    depois = Lbusca(l, posicao);
    novo->prox = depois;
    novo->ant = (depois != NULL) ? depois->ant : l->fim;

    /* ajusta os vizinhos (ou o início/fim da lista) para apontarem para o novo */
    if (novo->ant != NULL)
        novo->ant->prox = novo;
    else
        l->inicio = novo;             /* inseriu no início */
    if (novo->prox != NULL)
        novo->prox->ant = novo;
    else
        l->fim = novo;                /* inseriu no fim */

    l->tamanho++;
}

/* Lremove: remove e retorna o elemento na posição indicada */
ElementoLista Lremove(Lista l, int posicao) {
    NoLista *no = Lbusca(l, posicao);
    ElementoLista valor;
    if (no == NULL)
        return LISTA_ERRO;            /* posição inválida: retorna código de erro */
    valor = no->valor;

    /* os vizinhos passam a apontar um para o outro (ou ajusta início/fim) */
    if (no->ant != NULL)
        no->ant->prox = no->prox;
    else
        l->inicio = no->prox;         /* removeu o primeiro */
    if (no->prox != NULL)
        no->prox->ant = no->ant;
    else
        l->fim = no->ant;             /* removeu o último */

    free(no);
    l->tamanho--;
    return valor;
}