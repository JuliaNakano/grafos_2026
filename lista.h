/*
 * TAD Lista, implementada como lista dinâmica duplamente encadeada
 * (Esquema 1 do enunciado). Interface conforme o Trabalho Prático (base).
 *
 * Convenção de posições: as posições começam em 1.
 *   - Lexamina, Lremove : posição válida de 1 até Ltamanho(l)
 *   - Linsere           : posição válida de 1 até Ltamanho(l) + 1
 *                         (Ltamanho + 1 insere no fim da lista)
 *   - Llocaliza         : retorna 0 se o elemento não existir
 */

#ifndef LISTA_H
#define LISTA_H

/* Tipo do elemento armazenado na lista */
typedef int ElementoLista;

/* Valor retornado por Lexamina/Lremove quando a posição é inválida */
#define LISTA_ERRO (-1)

/* Lista é um ponteiro para struct; os detalhes ficam escondidos em lista.c */
struct lista;
typedef struct lista *Lista;

/* Lcria: cria uma lista vazia. Retorna NULL se faltar memória. */
Lista Lcria(void);

/* Ldestroi: destrói a lista, liberando todos os nós e o cabeçalho. */
void Ldestroi(Lista l);

/* Lvazia: examina se a lista está vazia (1 = vazia, 0 = não vazia). */
int Lvazia(Lista l);

/* Lcheia: examina se a lista está cheia, isto é, se não há memória
 * para criar mais um nó (1 = cheia, 0 = não cheia). */
int Lcheia(Lista l);

/* Ltamanho: retorna a quantidade de elementos na lista. */
int Ltamanho(Lista l);

/* Lexamina: retorna o elemento na posição indicada, sem removê-lo. */
ElementoLista Lexamina(Lista l, int posicao);

/* Llocaliza: retorna a posição do elemento, ou 0 se ele não existir. */
int Llocaliza(Lista l, ElementoLista elemento);

/* Linsere: insere o elemento na posição indicada. */
void Linsere(Lista l, ElementoLista elemento, int posicao);

/* Lremove: remove e retorna o elemento na posição indicada. */
ElementoLista Lremove(Lista l, int posicao);

#endif /* LISTA_H */