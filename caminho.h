/*
 * Disciplina : Estruturas de Dados 2 - Trabalho Prático 1
 * Aluna      : Julia Cristina Martins de Almeida Nakano
 * Matrícula  : 0077414
 * Data       : 16/10/2026
 *
 * caminho.h - Caminho de menor custo em grafo dirigido valorado.
 */

#ifndef CAMINHO_H
#define CAMINHO_H

#include "grafo.h"

/* Gcaminho: imprime, em uma linha, o trajeto de menor custo do vértice a
 * ao vértice b no grafo dirigido g, no formato "3 -> 6 -> 1 -> 2".
 *
 *   g     : grafo dirigido
 *   pesos : vetor de pesos das arestas com |A|+1 posições, indexado pelo
 *           identificador da aresta (a posição 0 não é usada). Os pesos
 *           devem ser não negativos.
 *   a, b  : vértices de partida e de chegada
 *
 * Se não existir caminho de a até b (ou se b não existir), imprime apenas
 * o vértice a. Se a não existir, não imprime nada. */
void Gcaminho(Grafo g, float *pesos, int a, int b);

#endif /* CAMINHO_H */
