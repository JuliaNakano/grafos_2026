/*
 * Disciplina : Estruturas de Dados 2 - Trabalho Prático 1
 * Aluna      : Julia Cristina Martins de Almeida Nakano
 * Matrícula  : 0077414
 * Data       : 16/10/2026
 *
 * grafo.h - Interface da TAD Grafo (grafo estático, com capacidade máxima
 * de vértices e arestas definida na criação).
 *
 * Convenções (conforme o enunciado):
 *   - Prefixo das rotinas: G + letra do tipo de retorno
 *       G = Grafo, V = vértice, A = aresta, B = booleano (1/0),
 *       I = inteiro.
 *   - Identificadores de vértices e arestas são inteiros positivos.
 *   - O valor 0 indica vértice/aresta inexistente (ou erro).
 *   - Nenhuma rotina imprime mensagens de erro.
 *   - O ponteiro Grafo recebido é assumido válido (não é verificado).
 *
 * Decisões de projeto (suposições, ver relatório):
 *   - O identificador de um novo vértice/aresta é o MENOR identificador
 *     livre. Sem remoções isso coincide com a ordem de criação (|V'|, |A'|),
 *     como pede o enunciado.
 *   - GAcriaAresta só cria a aresta se os dois vértices existirem.
 *   - O grau de um vértice é grau de saída + grau de entrada; um laço
 *     conta 2 (uma saída e uma entrada).
 *   - Em arestas não dirigidas, GValfa é o 1º vértice informado na criação
 *     e GVomega o 2º.
 */

#ifndef GRAFO_H
#define GRAFO_H

struct grafo;
typedef struct grafo *Grafo;

/* ---------------- Operações relacionadas ao grafo ---------------- */

/* Cria um grafo com no máximo v vértices e a arestas (v > 0, a > 0).
 * Retorna NULL se os parâmetros forem inválidos ou faltar memória. */
Grafo GGcriaGrafo(int v, int a);

/* Destrói o grafo, liberando a memória. Retorna sempre NULL. */
Grafo GGdestroiGrafo(Grafo g);

/* Cria um vértice. Retorna seu identificador, ou 0 se |V| já é o máximo. */
int GVcriaVertice(Grafo g);

/* Cria a aresta (v1,v2) ou {v1,v2}. Retorna seu identificador, ou 0 se
 * |A| já é o máximo ou se v1 ou v2 não existem. */
int GAcriaAresta(Grafo g, int v1, int v2);

/* Existência por identificador (1 = existe, 0 = não existe). */
int GBexisteIdVertice(Grafo g, int v);
int GBexisteIdAresta(Grafo g, int a);

/* Existe a aresta dirigida (v1,v2)? */
int GBexisteArestaDir(Grafo g, int v1, int v2);

/* Existe a aresta não dirigida {v1,v2}? (em qualquer sentido) */
int GBexisteAresta(Grafo g, int v1, int v2);

/* Identificador da aresta (v1,v2); 0 se não existir. Havendo arestas
 * múltiplas, retorna a de menor identificador. */
int GApegaArestaDir(Grafo g, int v1, int v2);

/* Identificador da aresta {v1,v2}; 0 se não existir. Havendo arestas
 * múltiplas, retorna a de menor identificador. */
int GApegaAresta(Grafo g, int v1, int v2);

/* Iteração sobre vértices em ordem crescente de identificador.
 * Ambas retornam 0 quando não há (próximo) vértice. */
int GVprimeiroVertice(Grafo g);
int GVproximoVertice(Grafo g, int v1);

/* Iteração sobre arestas em ordem crescente de identificador.
 * Ambas retornam 0 quando não há (próxima) aresta. */
int GAprimeiraAresta(Grafo g);
int GAproximaAresta(Grafo g, int a1);

/* Contadores: quantidade atual e máximo previsto. */
int GInumeroVertices(Grafo g);
int GInumeroVerticesMax(Grafo g);
int GInumeroArestas(Grafo g);
int GInumeroArestasMax(Grafo g);

/* Cria e carrega um grafo de arquivo texto (1ª linha: nV nA; depois uma
 * aresta por linha: partida chegada). Retorna NULL se o arquivo for
 * inválido. O grafo carregado tem capacidade exata nV e nA (mínimo 1
 * aresta de capacidade). */
Grafo GGcarregaGrafo(const char *f);

/* Salva o grafo em arquivo texto no mesmo formato. Se houve remoções, os
 * vértices e arestas são renumerados de forma compacta no arquivo.
 * Retorna 1 se conseguiu salvar, 0 caso contrário. */
int GBsalvaGrafo(Grafo g, const char *f);

/* ------------ Operações relacionadas aos vértices do grafo ------------ */

/* Grau do vértice (saída + entrada); 0 se não existir. */
int GIpegaGrau(Grafo g, int v);

/* Estrela do vértice (grafos NÃO dirigidos): todas as arestas incidentes
 * em v, em ordem crescente de identificador. Um laço aparece uma vez. */
int GAprimaAresta(Grafo g, int v);
int GAproxAresta(Grafo g, int v, int a1);

/* Estrela de entrada (grafos dirigidos): arestas que chegam em v. */
int GAprimaEntrada(Grafo g, int v);
int GAproxEntrada(Grafo g, int v, int a1);

/* Estrela de saída (grafos dirigidos): arestas que saem de v. */
int GAprimaSaida(Grafo g, int v);
int GAproxSaida(Grafo g, int v, int a1);

/* ------------ Operações relacionadas às arestas do grafo ------------ */

/* A aresta é um laço? (0 se a aresta não existir) */
int GBarestaLaco(Grafo g, int a);

/* Vértice de partida / chegada da aresta (0 se não existir). */
int GValfa(Grafo g, int a);
int GVomega(Grafo g, int a);

/* Outro extremo da aresta a, dado um extremo v1. Retorna 0 se a aresta
 * não existir ou se v1 não for extremo dela. Em um laço retorna v1. */
int GVvizinho(Grafo g, int a, int v1);

/* ---------------------- Operações de remoção ----------------------
 * (extensões não previstas no enunciado) */

/* Remove a aresta a. Retorna 1 se removeu, 0 se ela não existia.
 * O identificador a fica livre para ser reutilizado. */
int GBremoveAresta(Grafo g, int a);

/* Remove o vértice v e todas as arestas incidentes nele. Retorna 1 se
 * removeu, 0 se ele não existia. */
int GBremoveVertice(Grafo g, int v);

#endif /* GRAFO_H */
