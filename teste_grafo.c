/*
 * Disciplina : Estruturas de Dados 2 - Trabalho Prático 1
 * Aluna      : Julia Cristina Martins de Almeida Nakano
 * Matrícula  : 0077414
 * Data       : 16/10/2026
 *
 * teste_grafo.c - Bateria de testes da TAD Grafo e do Gcaminho.
 * Cada CHECK imprime OK/FALHA; o programa retorna 0 só se tudo passou.
 * Os testes de Gcaminho imprimem o trajeto obtido e o esperado.
 * 
 * um debug
 */

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "caminho.h"

static int falhas = 0;
static int total = 0;

#define CHECK(cond, desc) do { \
    total++; \
    if (cond) printf("  OK    %s\n", desc); \
    else { printf("  FALHA %s\n", desc); falhas++; } \
} while (0)

/* Figura 1 do enunciado: 6 vértices, 8 arestas (digrafo com laço). */
static Grafo figura1(void) {
    Grafo g = GGcriaGrafo(6, 8);
    int i;
    for (i = 0; i < 6; i++)
        GVcriaVertice(g);
    GAcriaAresta(g, 6, 1);   /* 1 */
    GAcriaAresta(g, 6, 3);   /* 2 */
    GAcriaAresta(g, 3, 6);   /* 3 */
    GAcriaAresta(g, 1, 3);   /* 4 */
    GAcriaAresta(g, 1, 2);   /* 5 */
    GAcriaAresta(g, 2, 3);   /* 6 */
    GAcriaAresta(g, 2, 2);   /* 7 (laço) */
    GAcriaAresta(g, 5, 4);   /* 8 */
    return g;
}

static void testaCriacao(void) {
    Grafo g;
    int i;
    printf("[criacao e limites]\n");
    CHECK(GGcriaGrafo(0, 5) == NULL, "GGcriaGrafo(0,5) retorna NULL");
    CHECK(GGcriaGrafo(5, 0) == NULL, "GGcriaGrafo(5,0) retorna NULL");
    g = GGcriaGrafo(3, 2);
    CHECK(GInumeroVertices(g) == 0 && GInumeroArestas(g) == 0, "grafo novo vazio");
    CHECK(GInumeroVerticesMax(g) == 3 && GInumeroArestasMax(g) == 2, "maximos corretos");
    CHECK(GVprimeiroVertice(g) == 0 && GAprimeiraAresta(g) == 0, "iteradores vazios retornam 0");
    for (i = 1; i <= 3; i++)
        CHECK(GVcriaVertice(g) == i, "ids de vertice em ordem de criacao");
    CHECK(GVcriaVertice(g) == 0, "criar alem do maximo retorna 0");
    CHECK(GAcriaAresta(g, 1, 4) == 0, "aresta com vertice inexistente retorna 0");
    CHECK(GAcriaAresta(g, 1, 2) == 1, "primeira aresta tem id 1");
    CHECK(GAcriaAresta(g, 2, 2) == 2, "segunda aresta (laco) tem id 2");
    CHECK(GAcriaAresta(g, 1, 3) == 0, "criar aresta alem do maximo retorna 0");
    CHECK(GInumeroVertices(g) == 3 && GInumeroArestas(g) == 2, "contadores apos criacao");
    GGdestroiGrafo(g);
    CHECK(GGdestroiGrafo(NULL) == NULL, "destruir NULL e seguro");
}

static void testaConsultas(void) {
    Grafo g = figura1();
    int a, v, cont;
    printf("[consultas na figura 1]\n");
    CHECK(GBexisteIdVertice(g, 6) && !GBexisteIdVertice(g, 7) && !GBexisteIdVertice(g, 0),
          "existencia de vertices");
    CHECK(GBexisteIdAresta(g, 8) && !GBexisteIdAresta(g, 9) && !GBexisteIdAresta(g, 0),
          "existencia de arestas");
    CHECK(GBexisteArestaDir(g, 6, 3) && GBexisteArestaDir(g, 3, 6), "(6,3) e (3,6) existem");
    CHECK(GBexisteArestaDir(g, 1, 2) && !GBexisteArestaDir(g, 2, 1), "(1,2) existe, (2,1) nao");
    CHECK(GBexisteAresta(g, 2, 1) && !GBexisteAresta(g, 4, 1), "nao dirigida {2,1} existe, {4,1} nao");
    CHECK(GApegaArestaDir(g, 6, 3) == 2 && GApegaArestaDir(g, 3, 6) == 3, "ids de (6,3) e (3,6)");
    CHECK(GApegaArestaDir(g, 2, 1) == 0, "pegar aresta inexistente retorna 0");
    CHECK(GApegaAresta(g, 3, 6) == 2, "{3,6} retorna a de menor id (2)");
    CHECK(GValfa(g, 4) == 1 && GVomega(g, 4) == 3, "alfa/omega da aresta 4");
    CHECK(GValfa(g, 99) == 0 && GVomega(g, 99) == 0, "alfa/omega de aresta inexistente = 0");
    CHECK(GBarestaLaco(g, 7) && !GBarestaLaco(g, 5) && !GBarestaLaco(g, 99), "laco");
    CHECK(GVvizinho(g, 5, 1) == 2 && GVvizinho(g, 5, 2) == 1, "vizinho nas duas direcoes");
    CHECK(GVvizinho(g, 5, 3) == 0, "vizinho com vertice que nao e extremo = 0");
    CHECK(GVvizinho(g, 7, 2) == 2, "vizinho no laco e o proprio vertice");
    CHECK(GIpegaGrau(g, 2) == 4, "grau do vertice 2 = 4 (como no enunciado)");
    CHECK(GIpegaGrau(g, 4) == 1 && GIpegaGrau(g, 99) == 0, "grau de 4 = 1; inexistente = 0");

    cont = 0;
    for (v = GVprimeiroVertice(g); v != 0; v = GVproximoVertice(g, v))
        cont++;
    CHECK(cont == 6, "iteracao percorre os 6 vertices");
    cont = 0;
    for (a = GAprimeiraAresta(g); a != 0; a = GAproximaAresta(g, a))
        cont++;
    CHECK(cont == 8, "iteracao percorre as 8 arestas");
    GGdestroiGrafo(g);
}

static void testaEstrelas(void) {
    Grafo g = figura1();
    printf("[estrelas]\n");
    /* enunciado: entrada de 2 = {5,7}; saida de 2 = {6,7} */
    CHECK(GAprimaEntrada(g, 2) == 5 && GAproxEntrada(g, 2, 5) == 7 && GAproxEntrada(g, 2, 7) == 0,
          "estrela de entrada de 2 = {5,7}");
    CHECK(GAprimaSaida(g, 2) == 6 && GAproxSaida(g, 2, 6) == 7 && GAproxSaida(g, 2, 7) == 0,
          "estrela de saida de 2 = {6,7}");
    CHECK(GAprimaSaida(g, 6) == 1 && GAproxSaida(g, 6, 1) == 2 && GAproxSaida(g, 6, 2) == 0,
          "estrela de saida de 6 = {1,2}");
    CHECK(GAprimaSaida(g, 4) == 0 && GAprimaEntrada(g, 5) == 0, "estrelas vazias retornam 0");
    CHECK(GAproxSaida(g, 6, 3) == 0, "proxima com a1 fora da estrela usa 'menor id > a1'");
    CHECK(GAproxSaida(g, 1, 2) == 4, "a1 fora da estrela: 1 tem saida {4,5}, menor id > 2 e 4");
    /* estrela nao dirigida de 2: arestas 5,6,7 (laco uma so vez) */
    CHECK(GAprimaAresta(g, 2) == 5 && GAproxAresta(g, 2, 5) == 6 &&
          GAproxAresta(g, 2, 6) == 7 && GAproxAresta(g, 2, 7) == 0,
          "estrela nao dirigida de 2 = {5,6,7}, laco uma vez");
    CHECK(GAprimaAresta(g, 99) == 0, "estrela de vertice inexistente = 0");
    GGdestroiGrafo(g);
}

static void testaMultiplasELacos(void) {
    Grafo g = GGcriaGrafo(2, 4);
    printf("[arestas multiplas]\n");
    GVcriaVertice(g);
    GVcriaVertice(g);
    GAcriaAresta(g, 1, 2);
    GAcriaAresta(g, 1, 2);
    GAcriaAresta(g, 2, 1);
    CHECK(GApegaArestaDir(g, 1, 2) == 1, "multiplas: pega a de menor id");
    CHECK(GAprimaSaida(g, 1) == 1 && GAproxSaida(g, 1, 1) == 2, "ambas aparecem na estrela de saida");
    CHECK(GApegaAresta(g, 2, 1) == 1, "nao dirigida considera os dois sentidos");
    CHECK(GIpegaGrau(g, 1) == 3, "grau de 1 = 3");
    GGdestroiGrafo(g);
}

static void testaArquivo(void) {
    Grafo g = figura1(), h;
    int a;
    printf("[arquivo]\n");
    CHECK(GBsalvaGrafo(g, "tmp_fig1.txt") == 1, "salva grafo");
    h = GGcarregaGrafo("tmp_fig1.txt");
    CHECK(h != NULL, "carrega grafo salvo");
    CHECK(GInumeroVertices(h) == 6 && GInumeroArestas(h) == 8, "contadores do grafo carregado");
    for (a = 1; a <= 8; a++)
        if (GValfa(g, a) != GValfa(h, a) || GVomega(g, a) != GVomega(h, a))
            break;
    CHECK(a == 9, "todas as arestas identicas apos salvar/carregar");
    GGdestroiGrafo(h);
    CHECK(GGcarregaGrafo("nao_existe.txt") == NULL, "arquivo inexistente retorna NULL");
    GGdestroiGrafo(g);
    remove("tmp_fig1.txt");
}

static void testaRemocao(void) {
    Grafo g = figura1(), h;
    int v;
    printf("[remocao]\n");
    CHECK(GBremoveAresta(g, 99) == 0, "remover aresta inexistente retorna 0");
    CHECK(GBremoveAresta(g, 7) == 1, "remove o laco (aresta 7)");
    CHECK(!GBexisteIdAresta(g, 7) && GInumeroArestas(g) == 7, "laco sumiu e contador diminuiu");
    CHECK(GIpegaGrau(g, 2) == 2, "grau de 2 caiu para 2");
    CHECK(GAprimaSaida(g, 2) == 6 && GAproxSaida(g, 2, 6) == 0, "estrela de saida de 2 = {6}");
    CHECK(GAprimaAresta(g, 2) == 5 && GAproxAresta(g, 2, 5) == 6 && GAproxAresta(g, 2, 6) == 0,
          "estrela de 2 = {5,6}");
    CHECK(GAcriaAresta(g, 5, 5) == 7, "novo id reutiliza o menor id livre (7)");
    GBremoveAresta(g, 7);

    CHECK(GBremoveVertice(g, 99) == 0, "remover vertice inexistente retorna 0");
    CHECK(GBremoveVertice(g, 6) == 1, "remove vertice 6");
    CHECK(!GBexisteIdVertice(g, 6) && GInumeroVertices(g) == 5, "vertice 6 sumiu");
    /* arestas incidentes em 6: 1,2,3 -> restam 4,5,6,8 */
    CHECK(GInumeroArestas(g) == 4, "arestas incidentes em 6 foram removidas");
    CHECK(!GBexisteIdAresta(g, 1) && !GBexisteIdAresta(g, 2) && !GBexisteIdAresta(g, 3),
          "arestas 1,2,3 sumiram");
    CHECK(GIpegaGrau(g, 3) == 2, "grau de 3 caiu de 4 para 2");
    CHECK(GVproximoVertice(g, 5) == 0 && GVproximoVertice(g, 4) == 5, "iteracao pula o vertice removido");
    CHECK(GVcriaVertice(g) == 6, "novo vertice reutiliza o id 6");
    CHECK(GBexisteIdVertice(g, 6) && GIpegaGrau(g, 6) == 0, "vertice reutilizado nasce isolado");

    GBremoveVertice(g, 1);                  /* deixa buraco no id 1 */
    CHECK(GBsalvaGrafo(g, "tmp_rem.txt") == 1, "salva grafo com ids com buracos");
    h = GGcarregaGrafo("tmp_rem.txt");
    CHECK(h != NULL && GInumeroVertices(h) == GInumeroVertices(g) &&
          GInumeroArestas(h) == GInumeroArestas(g), "recarrega com renumeracao compacta");
    for (v = 1; h != NULL && v <= GInumeroVertices(h); v++)
        if (!GBexisteIdVertice(h, v))
            break;
    CHECK(h != NULL && v == GInumeroVertices(h) + 1, "ids do arquivo recarregado sao 1..n");
    GGdestroiGrafo(h);
    GGdestroiGrafo(g);
    remove("tmp_rem.txt");
}

static void testaCaminho(void) {
    Grafo g = figura1(), h;
    float um[9] = {0, 1, 1, 1, 1, 1, 1, 1, 1};
    float pesos[10];
    int i;
    printf("[Gcaminho] (confira visualmente: obtido / esperado)\n");

    printf("  3 -> 2 (enunciado)      esperado: 3 -> 6 -> 1 -> 2\n  obtido: ");
    Gcaminho(g, um, 3, 2);
    printf("  1 -> 4 (sem caminho)    esperado: 1\n  obtido: ");
    Gcaminho(g, um, 1, 4);
    printf("  2 -> 2 (origem=destino) esperado: 2\n  obtido: ");
    Gcaminho(g, um, 2, 2);
    printf("  6 -> 2                  esperado: 6 -> 1 -> 2\n  obtido: ");
    Gcaminho(g, um, 6, 2);
    printf("  1 -> 99 (inexistente)   esperado: 1\n  obtido: ");
    Gcaminho(g, um, 1, 99);
    printf("  99 -> 1 (origem inex.)  esperado: (nada)\n  obtido: ");
    Gcaminho(g, um, 99, 1);
    printf("(fim)\n");

    /* pesos diferentes: 6->3 direto custa 10, mas 6->1->3 custa 1+1 = 2 */
    for (i = 0; i < 9; i++)
        pesos[i] = um[i];
    pesos[2] = 10;                          /* aresta 2 = (6,3) */
    printf("  6 -> 3 com peso(6,3)=10 esperado: 6 -> 1 -> 3\n  obtido: ");
    Gcaminho(g, pesos, 6, 3);
    GGdestroiGrafo(g);

    /* arestas multiplas e laco: vence a de menor peso, laco e ignorado */
    h = GGcriaGrafo(3, 5);
    GVcriaVertice(h); GVcriaVertice(h); GVcriaVertice(h);
    GAcriaAresta(h, 1, 2);                  /* 1: peso 5 */
    GAcriaAresta(h, 1, 2);                  /* 2: peso 2 */
    GAcriaAresta(h, 2, 2);                  /* 3: laco, peso 1 */
    GAcriaAresta(h, 2, 3);                  /* 4: peso 4 */
    GAcriaAresta(h, 1, 3);                  /* 5: peso 7 */
    {
        float p2[6] = {0, 5, 2, 1, 4, 7};
        printf("  1 -> 3 com multiplas e laco: 1->2->3 (2+4=6) vence 1->3 (7)\n"
               "  esperado: 1 -> 2 -> 3\n  obtido: ");
        Gcaminho(h, p2, 1, 3);
    }
    GGdestroiGrafo(h);
}

int main(void) {
    testaCriacao();
    testaConsultas();
    testaEstrelas();
    testaMultiplasELacos();
    testaArquivo();
    testaRemocao();
    testaCaminho();
    printf("\nResultado: %d testes, %d falha(s)\n", total, falhas);
    return falhas == 0 ? 0 : 1;
}
