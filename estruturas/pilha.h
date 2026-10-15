
/*
* TAD Pilha (LIFO = Last-In-First-Out), implementada com arranjo (vetor).
 * Interface conforme o enunciado do Trabalho Prático (base).
 */
#ifndef PILHA_H
#define PILHA_H
 
/* Capacidade máxima da pilha (tamanho pré-definido do arranjo) */
#define MAX 100
 
/* Tipo do elemento armazenado na pilha */
typedef int Elemento;
 
/* Valor retornado por Pexamina/Premove quando a pilha está vazia */
#define PILHA_ERRO (-1)
 
/* Pilha é um ponteiro para struct; os detalhes ficam escondidos em pilha.c */
struct pilha;
typedef struct pilha *Pilha;
 
/* Pcria: cria uma pilha vazia. Retorna NULL se faltar memória. */
Pilha Pcria(void);
 
/* Pdestroi: destrói a pilha e libera a memória alocada. */
void Pdestroi(Pilha p);
 
/* Pvazia: examina se a pilha está vazia (1 = vazia, 0 = não vazia). */
int Pvazia(Pilha p);
 
/* Pcheia: examina se a pilha está cheia (1 = cheia, 0 = não cheia). */
int Pcheia(Pilha p);
 
/* Ptamanho: retorna a quantidade de elementos na pilha. */
int Ptamanho(Pilha p);
 
/* Pexamina: retorna o elemento no topo da pilha (= top), sem removê-lo. */
Elemento Pexamina(Pilha p);
 
/* Pinsere: insere o elemento no topo da pilha (= push). */
void Pinsere(Pilha p, Elemento elemento);
 
/* Premove: remove e retorna o elemento no topo da pilha (= pop). */
Elemento Premove(Pilha p);
 
#endif /* PILHA_H */
 