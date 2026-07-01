/*
 * ============================================================
 *  Nome: Pedro Riquelme de Oliveira Uchôa
 *  Curso: Tecnologia em Analise e Desenvolvimento de Sistemas
 *  Modulo: III
 *  Disciplina: Estruturas de Dados II
 *  Lista de Exercicios 01 - Conteudo: Arvores Genericas
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* ============================================================
 *  PARTE 1 - QUESTOES CONCEITUAIS
 * ============================================================
 *
 * Questao 1  - c) Nao linear
 * Questao 2  - b) Raiz
 * Questao 3  - c) Folhas
 * Questao 4  - c) Maior caminho da raiz ate uma folha
 * Questao 5  - b) Quantidade de filhos
 * Questao 6  - a) Altura 0
 * Questao 7  - d) Arvores
 * Questao 8  - a) Sistema de arquivos
 *
 * Questao 9:
 *   Uma arvore e uma estrutura nao linear e hierarquica composta por nos
 *   conectados por arestas. Existe um no raiz (sem pai) e os demais nos
 *   possuem exatamente um pai. Nos sem filhos sao folhas.
 *
 * Questao 10:
 *   No raiz    - no superior, sem pai.
 *   No folha   - no terminal, sem filhos.
 *   No interno - no com pelo menos um filho (excluindo a raiz).
 *
 * Questao 11:
 *   Ancestral    - qualquer no acima de X, no caminho ate a raiz.
 *   Descendente  - qualquer no abaixo de X, alcancavel descendo arestas.
 *
 * Questao 12:
 *   Profundidade e o numero de arestas da raiz ate o no. Raiz = 0.
 *
 * Questao 13:
 *   Grau do no    - quantidade de filhos daquele no.
 *   Grau da arvore - maior grau entre todos os nos.
 *
 * Questao 14:
 *   Arvores sao essenciais por organizarem dados hierarquicamente,
 *   permitindo buscas, insercoes e remocoes eficientes. Usadas em
 *   bancos de dados, sistemas de arquivos, compiladores e roteadores.
 *
 * Questao 15:
 *                A              <- Nivel 0 (raiz, grau 3)
 *              / | \
 *            B   C   D          <- Nivel 1
 *          / \  |   |
 *         E   F G   H          <- Nivel 2
 *        /
 *       I                      <- Nivel 3
 *
 *   Folhas: E, F, G, H, I
 *   Altura: 3
 *   Grau da arvore: 3
 *
 * ============================================================ */

/* ============================================================
 *  PARTE 2 - IMPLEMENTACAO (Questoes 16 a 25)
 * ============================================================ */

/* --- Estrutura de no (filho-esquerdo / proximo-irmao) --- */
struct No {
    int dado;
    struct No *primeiroFilho;
    struct No *proximoIrmao;
};

/* Cria um no com alocacao dinamica */
struct No* criarNo(int valor) {
    struct No *novo = (struct No*) malloc(sizeof(struct No));
    if (novo == NULL) {
        printf("Erro de alocacao.\n");
        exit(1);
    }
    novo->dado = valor;
    novo->primeiroFilho = NULL;
    novo->proximoIrmao = NULL;
    return novo;
}

/* Busca um no pelo valor e retorna seu ponteiro.
   Percorre primeiro o filho e depois o irmao (DFS). */
struct No* buscarNo(struct No *raiz, int valor) {
    if (raiz == NULL)
        return NULL;
    if (raiz->dado == valor)
        return raiz;
    struct No *resultado = buscarNo(raiz->primeiroFilho, valor);
    if (resultado != NULL)
        return resultado;
    return buscarNo(raiz->proximoIrmao, valor);
}

/* Questao 17 - Inicializa arvore vazia */
struct No* inicializarArvore() {
    return NULL;
}

/* Questao 18 - Insere um filho no no-pai identificado pelo valor.
   Navegacao e feita por buscarNo(), sem encadeamento fragil. */
void inserirFilho(struct No *raiz, int valorPai, int valorFilho) {
    struct No *pai = buscarNo(raiz, valorPai);
    if (pai == NULL) {
        printf("Pai %d nao encontrado.\n", valorPai);
        return;
    }
    struct No *novo = criarNo(valorFilho);
    if (pai->primeiroFilho == NULL) {
        pai->primeiroFilho = novo;
    } else {
        struct No *irmao = pai->primeiroFilho;
        while (irmao->proximoIrmao != NULL)
            irmao = irmao->proximoIrmao;
        irmao->proximoIrmao = novo;
    }
}

/* Questao 19 - Conta o total de nos da subarvore.
   Funcao unica: percorre filhos e irmaos recursivamente. */
int contarNos(struct No *raiz) {
    if (raiz == NULL)
        return 0;
    return 1 + contarNos(raiz->primeiroFilho) + contarNos(raiz->proximoIrmao);
}

/* Questao 20 - Calcula a altura da arvore */
int calcularAltura(struct No *raiz) {
    if (raiz == NULL)
        return -1;
    int max = -1;
    struct No *filho = raiz->primeiroFilho;
    while (filho != NULL) {
        int h = calcularAltura(filho);
        if (h > max)
            max = h;
        filho = filho->proximoIrmao;
    }
    return max + 1;
}

/* Questao 21 - Conta a quantidade de folhas */
int contarFolhas(struct No *raiz) {
    if (raiz == NULL)
        return 0;
    if (raiz->primeiroFilho == NULL)
        return 1;
    int total = 0;
    struct No *filho = raiz->primeiroFilho;
    while (filho != NULL) {
        total += contarFolhas(filho);
        filho = filho->proximoIrmao;
    }
    return total;
}

/* Questao 22 - Verifica se um valor existe na arvore */
int existe(struct No *raiz, int valor) {
    return buscarNo(raiz, valor) != NULL;
}

/* Questao 23 - Imprime os nos por nivel */
void imprimirNivel(struct No *raiz, int nivel) {
    if (raiz == NULL)
        return;
    if (nivel == 0) {
        printf("%d ", raiz->dado);
    } else {
        struct No *filho = raiz->primeiroFilho;
        while (filho != NULL) {
            imprimirNivel(filho, nivel - 1);
            filho = filho->proximoIrmao;
        }
    }
}

void imprimirPorNivel(struct No *raiz) {
    int h = calcularAltura(raiz);
    int i;
    for (i = 0; i <= h; i++) {
        printf("  Nivel %d: ", i);
        imprimirNivel(raiz, i);
        printf("\n");
    }
}

/* Pre-ordem para arvore generica */
void preOrdem(struct No *raiz) {
    if (raiz == NULL)
        return;
    printf("%d ", raiz->dado);
    struct No *filho = raiz->primeiroFilho;
    while (filho != NULL) {
        preOrdem(filho);
        filho = filho->proximoIrmao;
    }
}

/* Questao 24 - Por que recursao?
 *
 * A definicao de arvore e recursiva: uma arvore e um no conectado a
 * zero ou mais subarvores. A recursao trata o caso base (no NULL ou
 * folha) e aplica a si mesma em cada subarvore, gerando codigo
 * natural, conciso e correto para percurso, contagem e liberacao.
 */

/* Questao 25 - Libera toda a memoria da arvore */
void destruirArvore(struct No *raiz) {
    if (raiz == NULL)
        return;
    struct No *filho = raiz->primeiroFilho;
    while (filho != NULL) {
        struct No *proximo = filho->proximoIrmao;
        destruirArvore(filho);
        filho = proximo;
    }
    free(raiz);
}

/* ============================================================
 *  MAIN
 * ============================================================ */
int main() {
    struct No *raiz;

    printf("========================================\n");
    printf("  Lista 01 - Arvores Genericas\n");
    printf("  Nome: Adriel Barros Teixeira\n");
    printf("  Modulo III - ADS\n");
    printf("========================================\n\n");

    /*       1
     *      / | \
     *     2  3  4
     *    / \    |
     *   5   6   7
     *  /
     * 8
     */
    raiz = criarNo(1);
    inserirFilho(raiz, 1, 2);
    inserirFilho(raiz, 1, 3);
    inserirFilho(raiz, 1, 4);
    inserirFilho(raiz, 2, 5);
    inserirFilho(raiz, 2, 6);
    inserirFilho(raiz, 4, 7);
    inserirFilho(raiz, 5, 8);

    printf("Pre-ordem: ");
    preOrdem(raiz);
    printf("\n\n");

    printf("Impressao por nivel:\n");
    imprimirPorNivel(raiz);

    printf("\nTotal de nos: %d\n", contarNos(raiz));
    printf("Altura: %d\n", calcularAltura(raiz));
    printf("Folhas: %d\n\n", contarFolhas(raiz));

    printf("Buscar 6: %s\n", existe(raiz, 6) ? "Encontrado" : "Nao encontrado");
    printf("Buscar 9: %s\n\n", existe(raiz, 9) ? "Encontrado" : "Nao encontrado");

    destruirArvore(raiz);
    printf("Memoria liberada com sucesso.\n");

    return 0;
}
