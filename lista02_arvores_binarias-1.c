/*
 * ============================================================
 *  Nome: Pedro Riquelme de Oliveira Uchôa
 *  Curso: Tecnologia em Analise e Desenvolvimento de Sistemas
 *  Modulo: III
 *  Disciplina: Estruturas de Dados II
 *  Lista de Exercicios 02 - Conteudo: Arvores Binarias
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* ============================================================
 *  QUESTOES CONCEITUAIS
 * ============================================================
 *
 * Questao 1  - b) Cada no pode ter no maximo dois filhos
 * Questao 2  - c) Cada no pode ter filho esquerdo e direito
 * Questao 3  - c) Pre-ordem  (Raiz -> Esquerda -> Direita)
 * Questao 4  - b) Em ordem   (Esquerda -> Raiz -> Direita)
 * Questao 5  - a) Pos-ordem  (Esquerda -> Direita -> Raiz)
 * Questao 6  - b) Todos os niveis completos, exceto possivelmente o ultimo
 *
 * Questao 7:
 *   Cheia    - todo no possui 0 ou 2 filhos (nenhum com 1 filho).
 *   Completa - todos os niveis cheios, exceto o ultimo, preenchido
 *              da esquerda para a direita.
 *
 * Questao 8:
 *   Pre-ordem  - Raiz primeiro.  Util para copiar arvores.
 *   Em ordem   - Raiz no meio.   Em ABB gera ordem crescente.
 *   Pos-ordem  - Raiz por ultimo. Util para liberar memoria.
 *
 * Questao 9:
 *   Arvores sao mais eficientes que vetores quando se precisa de
 *   insercao/remocao frequentes (O(log n) balanceada vs O(n)) e
 *   de acesso ordenado sem reordenacao.
 *
 * Questao 10:
 *              50
 *            /    \
 *          30      70
 *         /  \    /  \
 *       20   40  60   80
 *       /  \     \
 *      10   25    55
 *
 *   Pre-ordem:  50 30 20 10 25 40 70 60 55 80
 *   Em ordem:   10 20 25 30 40 50 55 60 70 80
 *   Pos-ordem:  10 25 20 40 30 55 60 80 70 50
 *
 * ============================================================ */

/* ============================================================
 *  IMPLEMENTACAO (Questoes 36 a 45)
 * ============================================================ */

/* Questao 36 - Estrutura do no */
struct No {
    int dado;
    struct No *esquerda;
    struct No *direita;
};

/* Funcao auxiliar: cria no com alocacao dinamica */
struct No* criarNo(int valor) {
    struct No *novo = (struct No*) malloc(sizeof(struct No));
    if (novo == NULL) {
        printf("Erro de alocacao.\n");
        exit(1);
    }
    novo->dado = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

/* Questao 37 - Insercao manual sem vazamento de memoria.
   Verifica se a posicao esta livre ANTES de alocar.
   Retorna 1 em sucesso, 0 em falha. */
int inserirManual(struct No *pai, int valor, char posicao) {
    if (pai == NULL) {
        printf("Pai invalido.\n");
        return 0;
    }
    if (posicao == 'e' || posicao == 'E') {
        if (pai->esquerda != NULL) {
            printf("Filho esquerdo de %d ja ocupado.\n", pai->dado);
            return 0;
        }
        pai->esquerda = criarNo(valor);
        return 1;
    }
    if (posicao == 'd' || posicao == 'D') {
        if (pai->direita != NULL) {
            printf("Filho direito de %d ja ocupado.\n", pai->dado);
            return 0;
        }
        pai->direita = criarNo(valor);
        return 1;
    }
    printf("Posicao invalida. Use 'e' ou 'd'.\n");
    return 0;
}

/* Questao 38 - Pre-ordem */
void preOrdem(struct No *raiz) {
    if (raiz == NULL)
        return;
    printf("%d ", raiz->dado);
    preOrdem(raiz->esquerda);
    preOrdem(raiz->direita);
}

/* Questao 39 - Em ordem */
void emOrdem(struct No *raiz) {
    if (raiz == NULL)
        return;
    emOrdem(raiz->esquerda);
    printf("%d ", raiz->dado);
    emOrdem(raiz->direita);
}

/* Questao 40 - Pos-ordem */
void posOrdem(struct No *raiz) {
    if (raiz == NULL)
        return;
    posOrdem(raiz->esquerda);
    posOrdem(raiz->direita);
    printf("%d ", raiz->dado);
}

/* Questao 41 - Contar nos */
int contarNos(struct No *raiz) {
    if (raiz == NULL)
        return 0;
    return 1 + contarNos(raiz->esquerda) + contarNos(raiz->direita);
}

/* Questao 42 - Calcular altura */
int calcularAltura(struct No *raiz) {
    if (raiz == NULL)
        return -1;
    int altEsq = calcularAltura(raiz->esquerda);
    int altDir = calcularAltura(raiz->direita);
    return (altEsq > altDir ? altEsq : altDir) + 1;
}

/* Questao 43 - Contar folhas */
int contarFolhas(struct No *raiz) {
    if (raiz == NULL)
        return 0;
    if (raiz->esquerda == NULL && raiz->direita == NULL)
        return 1;
    return contarFolhas(raiz->esquerda) + contarFolhas(raiz->direita);
}

/* Questao 44 - Espelhar arvore (cria copia espelhada) */
struct No* espelhar(struct No *raiz) {
    if (raiz == NULL)
        return NULL;
    struct No *novo = criarNo(raiz->dado);
    novo->esquerda = espelhar(raiz->direita);
    novo->direita  = espelhar(raiz->esquerda);
    return novo;
}

/* Questao 45 - Verificar se duas arvores sao iguais */
int saoIguais(struct No *a, struct No *b) {
    if (a == NULL && b == NULL)
        return 1;
    if (a == NULL || b == NULL)
        return 0;
    if (a->dado != b->dado)
        return 0;
    return saoIguais(a->esquerda, b->esquerda) &&
           saoIguais(a->direita, b->direita);
}

/* Libera memoria em pos-ordem */
void liberarArvore(struct No *raiz) {
    if (raiz == NULL)
        return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

/* ============================================================
 *  MAIN
 * ============================================================ */
int main() {
    struct No *raiz;
    struct No *espelho;

    printf("========================================\n");
    printf("  Lista 02 - Arvores Binarias\n");
    printf("  Nome: Adriel Barros Teixeira\n");
    printf("  Modulo III - ADS\n");
    printf("========================================\n\n");

    /*          50
     *        /    \
     *      30      70
     *     /  \    /  \
     *   20   40  60   80
     */
    raiz = criarNo(50);
    inserirManual(raiz, 30, 'e');
    inserirManual(raiz, 70, 'd');
    inserirManual(raiz->esquerda, 20, 'e');
    inserirManual(raiz->esquerda, 40, 'd');
    inserirManual(raiz->direita, 60, 'e');
    inserirManual(raiz->direita, 80, 'd');

    /* Teste de seguranca: posicao ja ocupada */
    printf("[Teste] Inserir 99 na esquerda de 30 (ocupada por 20):\n");
    inserirManual(raiz->esquerda, 99, 'e');
    printf("\n");

    printf("Pre-ordem:  ");
    preOrdem(raiz);
    printf("\n");

    printf("Em ordem:   ");
    emOrdem(raiz);
    printf("\n");

    printf("Pos-ordem:  ");
    posOrdem(raiz);
    printf("\n\n");

    printf("Nos: %d\n", contarNos(raiz));
    printf("Altura: %d\n", calcularAltura(raiz));
    printf("Folhas: %d\n\n", contarFolhas(raiz));

    espelho = espelhar(raiz);
    printf("Espelho (em ordem): ");
    emOrdem(espelho);
    printf("\n\n");

    printf("Original == Original? %s\n", saoIguais(raiz, raiz) ? "Sim" : "Nao");
    printf("Original == Espelho?  %s\n", saoIguais(raiz, espelho) ? "Sim" : "Nao");

    liberarArvore(raiz);
    liberarArvore(espelho);

    return 0;
}
