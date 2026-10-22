/*
 * Disciplina : Estruturas de Dados 2 - Trabalho Prático 1
 * Aluna      : Julia Cristina Martins de Almeida Nakano
 * Matrícula  : 0077414
 * Data       : 16/10/2026
 *
 * grafo.c - Implementação da TAD Grafo.
 *
 * Representação (tudo pré-alocado em GGcriaGrafo, vetores indexados
 * diretamente pelos identificadores, posição 0 sem uso):
 *
 *   Vértices (índice v, 1..maxV)
 *     existeV[v] : 1 se o vértice existe
 *     primS[v]   : primeira aresta da estrela de saída de v   (0 = vazia)
 *     primE[v]   : primeira aresta da estrela de entrada de v (0 = vazia)
 *     grauS[v], grauE[v] : grau de saída e de entrada
 *
 *   Arestas (índice a, 1..maxA)
 *     alfa[a], omega[a] : vértices de partida e de chegada
 *                         (alfa[a] == 0 significa aresta inexistente)
 *     proxS[a] : próxima aresta na estrela de saída de alfa[a]
 *     proxE[a] : próxima aresta na estrela de entrada de omega[a]
 *
 * As estrelas são listas encadeadas EM VETOR, mantidas em ordem crescente
 * de identificador. Assim, "próxima aresta da estrela" é O(1) quando a1
 * pertence à estrela, e a estrela (não dirigida) é obtida intercalando a
 * estrela de saída com a de entrada.
 *
 * Exemplo (figura 1 do enunciado, vértice 2):
 *   primS[2] -> 6 -> 7 -> 0        (arestas que saem de 2)
 *   primE[2] -> 5 -> 7 -> 0        (arestas que chegam em 2)
 */

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

struct grafo {
    int maxV, maxA;      /* capacidades previstas */
    int nV, nA;          /* quantidades atuais */
    int livreV, livreA;  /* todo id menor que isso está em uso (busca de id livre) */
    char *existeV;
    int *grauS, *grauE;
    int *primS, *primE;
    int *alfa, *omega;
    int *proxS, *proxE;
};

/* ------------------------- Funções auxiliares ------------------------- */

static int ehVertice(Grafo g, int v) {
    return v >= 1 && v <= g->maxV && g->existeV[v];
}

static int ehAresta(Grafo g, int a) {
    return a >= 1 && a <= g->maxA && g->alfa[a] != 0;
}

/* Insere a aresta a na lista (prim[v]/prox[]) mantendo a ordem crescente. */
static void insereOrdenado(int *prim, int *prox, int v, int a) {
    int p;
    if (prim[v] == 0 || prim[v] > a) {      /* vira a primeira da lista */
        prox[a] = prim[v];
        prim[v] = a;
        return;
    }
    p = prim[v];
    while (prox[p] != 0 && prox[p] < a)
        p = prox[p];
    prox[a] = prox[p];
    prox[p] = a;
}

/* Remove a aresta a da lista (prim[v]/prox[]). */
static void desliga(int *prim, int *prox, int v, int a) {
    int p;
    if (prim[v] == a) {
        prim[v] = prox[a];
        return;
    }
    p = prim[v];
    while (p != 0 && prox[p] != a)
        p = prox[p];
    if (p != 0)
        prox[p] = prox[a];
}

/* Próxima aresta, com id > a1, da lista de v (extremo[] diz de qual vértice
 * cada aresta é membro da lista: alfa para saída, omega para entrada). */
static int proximaNaLista(Grafo g, const int *prim, const int *prox,
                          const int *extremo, int v, int a1) {
    int a;
    if (!ehVertice(g, v))
        return 0;
    if (ehAresta(g, a1) && extremo[a1] == v)
        return prox[a1];                    /* caminho rápido: a1 está na lista */
    a = prim[v];
    while (a != 0 && a <= a1)
        a = prox[a];
    return a;
}

/* ------------------- Operações relacionadas ao grafo ------------------- */

Grafo GGcriaGrafo(int v, int a) {
    Grafo g;
    size_t nv, na;
    if (v <= 0 || a <= 0)
        return NULL;
    g = (Grafo) calloc(1, sizeof(struct grafo));
    if (g == NULL)
        return NULL;
    g->maxV = v;
    g->maxA = a;
    g->livreV = 1;
    g->livreA = 1;
    nv = (size_t) v + 1;
    na = (size_t) a + 1;
    g->existeV = (char *) calloc(nv, sizeof(char));
    g->grauS = (int *) calloc(nv, sizeof(int));
    g->grauE = (int *) calloc(nv, sizeof(int));
    g->primS = (int *) calloc(nv, sizeof(int));
    g->primE = (int *) calloc(nv, sizeof(int));
    g->alfa  = (int *) calloc(na, sizeof(int));
    g->omega = (int *) calloc(na, sizeof(int));
    g->proxS = (int *) calloc(na, sizeof(int));
    g->proxE = (int *) calloc(na, sizeof(int));
    if (!g->existeV || !g->grauS || !g->grauE || !g->primS || !g->primE ||
        !g->alfa || !g->omega || !g->proxS || !g->proxE)
        return GGdestroiGrafo(g);           /* free(NULL) é seguro */
    return g;
}

Grafo GGdestroiGrafo(Grafo g) {
    if (g == NULL)
        return NULL;
    free(g->existeV);
    free(g->grauS);
    free(g->grauE);
    free(g->primS);
    free(g->primE);
    free(g->alfa);
    free(g->omega);
    free(g->proxS);
    free(g->proxE);
    free(g);
    return NULL;
}

int GVcriaVertice(Grafo g) {
    int v;
    if (g->nV >= g->maxV)
        return 0;
    v = g->livreV;
    while (g->existeV[v])                   /* existe id livre em 1..maxV */
        v++;
    g->existeV[v] = 1;
    g->nV++;
    g->livreV = v + 1;
    return v;
}

int GAcriaAresta(Grafo g, int v1, int v2) {
    int a;
    if (g->nA >= g->maxA || !ehVertice(g, v1) || !ehVertice(g, v2))
        return 0;
    a = g->livreA;
    while (g->alfa[a] != 0)
        a++;
    g->alfa[a] = v1;
    g->omega[a] = v2;
    insereOrdenado(g->primS, g->proxS, v1, a);
    insereOrdenado(g->primE, g->proxE, v2, a);
    g->grauS[v1]++;
    g->grauE[v2]++;
    g->nA++;
    g->livreA = a + 1;
    return a;
}

int GBexisteIdVertice(Grafo g, int v) {
    return ehVertice(g, v);
}

int GBexisteIdAresta(Grafo g, int a) {
    return ehAresta(g, a);
}

int GApegaArestaDir(Grafo g, int v1, int v2) {
    int a;
    if (!ehVertice(g, v1) || !ehVertice(g, v2))
        return 0;
    for (a = g->primS[v1]; a != 0; a = g->proxS[a])
        if (g->omega[a] == v2)
            return a;                       /* lista ordenada: menor id */
    return 0;
}

int GApegaAresta(Grafo g, int v1, int v2) {
    int a1 = GApegaArestaDir(g, v1, v2);
    int a2 = GApegaArestaDir(g, v2, v1);
    if (a1 == 0)
        return a2;
    if (a2 == 0)
        return a1;
    return (a1 < a2) ? a1 : a2;
}

int GBexisteArestaDir(Grafo g, int v1, int v2) {
    return GApegaArestaDir(g, v1, v2) != 0;
}

int GBexisteAresta(Grafo g, int v1, int v2) {
    return GApegaAresta(g, v1, v2) != 0;
}

int GVprimeiroVertice(Grafo g) {
    return GVproximoVertice(g, 0);
}

int GVproximoVertice(Grafo g, int v1) {
    int v;
    for (v = (v1 < 1) ? 1 : v1 + 1; v <= g->maxV; v++)
        if (g->existeV[v])
            return v;
    return 0;
}

int GAprimeiraAresta(Grafo g) {
    return GAproximaAresta(g, 0);
}

int GAproximaAresta(Grafo g, int a1) {
    int a;
    for (a = (a1 < 1) ? 1 : a1 + 1; a <= g->maxA; a++)
        if (g->alfa[a] != 0)
            return a;
    return 0;
}

int GInumeroVertices(Grafo g)    { return g->nV; }
int GInumeroVerticesMax(Grafo g) { return g->maxV; }
int GInumeroArestas(Grafo g)     { return g->nA; }
int GInumeroArestasMax(Grafo g)  { return g->maxA; }

Grafo GGcarregaGrafo(const char *f) {
    FILE *fp;
    Grafo g;
    int n, m, i, x, y;

    fp = fopen(f, "r");
    if (fp == NULL)
        return NULL;
    if (fscanf(fp, "%d %d", &n, &m) != 2 || n <= 0 || m < 0) {
        fclose(fp);
        return NULL;
    }
    g = GGcriaGrafo(n, (m > 0) ? m : 1);    /* a TAD exige capacidade > 0 */
    if (g == NULL) {
        fclose(fp);
        return NULL;
    }
    for (i = 0; i < n; i++)
        GVcriaVertice(g);
    for (i = 0; i < m; i++) {
        if (fscanf(fp, "%d %d", &x, &y) != 2 || GAcriaAresta(g, x, y) == 0) {
            GGdestroiGrafo(g);              /* arquivo inválido */
            fclose(fp);
            return NULL;
        }
    }
    fclose(fp);
    return g;
}

int GBsalvaGrafo(Grafo g, const char *f) {
    FILE *fp;
    int *novo;                              /* novo[v] = id compactado de v */
    int v, a, cont = 0, ok = 1;

    novo = (int *) calloc((size_t) g->maxV + 1, sizeof(int));
    if (novo == NULL)
        return 0;
    fp = fopen(f, "w");
    if (fp == NULL) {
        free(novo);
        return 0;
    }
    for (v = GVprimeiroVertice(g); v != 0; v = GVproximoVertice(g, v))
        novo[v] = ++cont;
    if (fprintf(fp, "%d %d\n", g->nV, g->nA) < 0)
        ok = 0;
    for (a = GAprimeiraAresta(g); a != 0; a = GAproximaAresta(g, a))
        if (fprintf(fp, "%d %d\n", novo[g->alfa[a]], novo[g->omega[a]]) < 0)
            ok = 0;
    if (fclose(fp) != 0)
        ok = 0;
    free(novo);
    return ok;
}

/* -------------- Operações relacionadas aos vértices do grafo -------------- */

int GIpegaGrau(Grafo g, int v) {
    if (!ehVertice(g, v))
        return 0;
    return g->grauS[v] + g->grauE[v];
}

int GAprimaAresta(Grafo g, int v) {
    return GAproxAresta(g, v, 0);
}

int GAproxAresta(Grafo g, int v, int a1) {
    /* estrela = estrela de saída U estrela de entrada (laço aparece uma vez,
     * pois pegamos sempre o menor id > a1 entre as duas listas) */
    int s = proximaNaLista(g, g->primS, g->proxS, g->alfa, v, a1);
    int e = proximaNaLista(g, g->primE, g->proxE, g->omega, v, a1);
    if (s == 0)
        return e;
    if (e == 0)
        return s;
    return (s < e) ? s : e;
}

int GAprimaEntrada(Grafo g, int v) {
    return GAproxEntrada(g, v, 0);
}

int GAproxEntrada(Grafo g, int v, int a1) {
    return proximaNaLista(g, g->primE, g->proxE, g->omega, v, a1);
}

int GAprimaSaida(Grafo g, int v) {
    return GAproxSaida(g, v, 0);
}

int GAproxSaida(Grafo g, int v, int a1) {
    return proximaNaLista(g, g->primS, g->proxS, g->alfa, v, a1);
}

/* -------------- Operações relacionadas às arestas do grafo -------------- */

int GBarestaLaco(Grafo g, int a) {
    return ehAresta(g, a) && g->alfa[a] == g->omega[a];
}

int GValfa(Grafo g, int a) {
    return ehAresta(g, a) ? g->alfa[a] : 0;
}

int GVomega(Grafo g, int a) {
    return ehAresta(g, a) ? g->omega[a] : 0;
}

int GVvizinho(Grafo g, int a, int v1) {
    if (!ehAresta(g, a))
        return 0;
    if (g->alfa[a] == v1)
        return g->omega[a];
    if (g->omega[a] == v1)
        return g->alfa[a];
    return 0;
}

/* ------------------------- Operações de remoção ------------------------- */

int GBremoveAresta(Grafo g, int a) {
    if (!ehAresta(g, a))
        return 0;
    desliga(g->primS, g->proxS, g->alfa[a], a);
    desliga(g->primE, g->proxE, g->omega[a], a);
    g->grauS[g->alfa[a]]--;
    g->grauE[g->omega[a]]--;
    g->alfa[a] = 0;                         /* marca como inexistente */
    g->omega[a] = 0;
    g->proxS[a] = 0;
    g->proxE[a] = 0;
    g->nA--;
    if (a < g->livreA)
        g->livreA = a;                      /* id volta a ficar disponível */
    return 1;
}

int GBremoveVertice(Grafo g, int v) {
    if (!ehVertice(g, v))
        return 0;
    while (g->primS[v] != 0)                /* arestas que saem de v */
        GBremoveAresta(g, g->primS[v]);
    while (g->primE[v] != 0)                /* arestas que chegam em v */
        GBremoveAresta(g, g->primE[v]);
    g->existeV[v] = 0;
    g->nV--;
    if (v < g->livreV)
        g->livreV = v;
    return 1;
}
