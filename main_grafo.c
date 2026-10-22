/*
 * Disciplina : Estruturas de Dados 2 - Trabalho Prático 1
 * Aluna      : Julia Cristina Martins de Almeida Nakano
 * Matrícula  : 0077414
 * Data       : 16/10/2026
 *
 * main_grafo.c - Programa principal: carrega um grafo dirigido de arquivo,
 * lê os pesos das arestas da entrada padrão e imprime o trajeto de a até b.
 *
 * Uso:   ./main_grafo grafo.txt a b < pesos.txt
 *   - pesos.txt traz |A| números (peso da aresta 1, 2, ...). Pesos que
 *     faltarem valem 1.
 *
 * Exemplo (figura 1 do enunciado):
 *   echo "1 1 1 1 1 1 1 1" | ./main_grafo grafo_fig1.txt 3 2   ->  3 -> 6 -> 1 -> 2
 *   echo "1 1 1 1 1 1 1 1" | ./main_grafo grafo_fig1.txt 1 4   ->  1
 */

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "caminho.h"

int main(int argc, char *argv[]) {
    Grafo g;
    float *pesos;
    int a, b, i, na;

    if (argc != 4) {
        fprintf(stderr, "Uso: %s arquivo_grafo vertice_a vertice_b < pesos\n", argv[0]);
        return 1;
    }
    g = GGcarregaGrafo(argv[1]);
    if (g == NULL) {
        fprintf(stderr, "Erro: nao foi possivel carregar o grafo '%s'\n", argv[1]);
        return 1;
    }
    a = atoi(argv[2]);
    b = atoi(argv[3]);

    na = GInumeroArestas(g);
    pesos = (float *) malloc(((size_t) na + 1) * sizeof(float));
    if (pesos == NULL) {
        GGdestroiGrafo(g);
        return 1;
    }
    pesos[0] = 0;                           /* posição 0 não é usada */
    for (i = 1; i <= na; i++)
        if (scanf("%f", &pesos[i]) != 1)
            pesos[i] = 1;                   /* peso ausente: 1 */

    Gcaminho(g, pesos, a, b);

    free(pesos);
    GGdestroiGrafo(g);
    return 0;
}
