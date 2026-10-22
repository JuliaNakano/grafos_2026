/*
 * Disciplina : Estruturas de Dados 2 - Trabalho Prático 1
 * Aluna      : Julia Cristina Martins de Almeida Nakano
 * Matrícula  : 0077414
 * Data       : 16/10/2026
 *
 * caminho.c - Algoritmo de Dijkstra (versão O(V^2), com busca linear do
 * vértice de menor distância) adaptado para a TAD Grafo.
 *
 * Só usa a interface da TAD: percorre os vértices com GVprimeiroVertice /
 * GVproximoVertice e as arestas de saída de cada vértice com
 * GAprimaSaida / GAproxSaida, obtendo o destino com GVomega. Arestas
 * múltiplas e laços são tratados naturalmente (cada aresta é relaxada
 * separadamente).
 *
 * Vetores auxiliares indexados pelo identificador do vértice:
 *   dist[v]    : menor distância conhecida de a até v
 *   achado[v]  : 1 se v já tem alguma distância conhecida
 *   fechado[v] : 1 se a distância de v já é definitiva
 *   pred[v]    : vértice anterior a v no melhor caminho encontrado
 */

#include <stdio.h>
#include <stdlib.h>
#include "caminho.h"

void Gcaminho(Grafo g, float *pesos, int a, int b) {
    int n, u, v, e, w, k, chegou;
    double d;
    double *dist;
    char *achado, *fechado;
    int *pred, *trajeto;

    if (!GBexisteIdVertice(g, a))
        return;

    n = GInumeroVerticesMax(g);
    dist    = (double *) calloc((size_t) n + 1, sizeof(double));
    achado  = (char *)   calloc((size_t) n + 1, sizeof(char));
    fechado = (char *)   calloc((size_t) n + 1, sizeof(char));
    pred    = (int *)    calloc((size_t) n + 1, sizeof(int));
    trajeto = (int *)    calloc((size_t) n + 1, sizeof(int));
    if (!dist || !achado || !fechado || !pred || !trajeto) {
        printf("%d\n", a);                  /* sem memória: devolve só a origem */
        free(dist); free(achado); free(fechado); free(pred); free(trajeto);
        return;
    }

    dist[a] = 0.0;
    achado[a] = 1;

    for (;;) {
        /* escolhe o vértice aberto de menor distância */
        u = 0;
        for (v = GVprimeiroVertice(g); v != 0; v = GVproximoVertice(g, v))
            if (achado[v] && !fechado[v] && (u == 0 || dist[v] < dist[u]))
                u = v;
        if (u == 0 || u == b)               /* acabou ou chegou ao destino */
            break;
        fechado[u] = 1;

        /* relaxa as arestas que saem de u */
        for (e = GAprimaSaida(g, u); e != 0; e = GAproxSaida(g, u, e)) {
            w = GVomega(g, e);
            d = dist[u] + pesos[e];
            if (!fechado[w] && (!achado[w] || d < dist[w])) {
                dist[w] = d;
                achado[w] = 1;
                pred[w] = u;
            }
        }
    }

    chegou = GBexisteIdVertice(g, b) && u == b;
    if (!chegou) {
        printf("%d\n", a);                  /* sem caminho: só a origem */
    } else {
        /* reconstrói o trajeto de b até a pelos predecessores */
        k = 0;
        for (v = b; v != a; v = pred[v])
            trajeto[k++] = v;
        trajeto[k++] = a;
        while (k > 0) {                     /* imprime de a até b */
            k--;
            printf("%d", trajeto[k]);
            if (k > 0)
                printf(" -> ");
        }
        printf("\n");
    }

    free(dist);
    free(achado);
    free(fechado);
    free(pred);
    free(trajeto);
}
