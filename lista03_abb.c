/*
 * ============================================================
 *  Nome: Adriel Barros Teixeira
 *  Curso: Tecnologia em Analise e Desenvolvimento de Sistemas
 *  Modulo: III
 *  Disciplina: Estruturas de Dados II
 *  Lista de Exercicios 03 - Conteudo: Arvores Binarias de Busca
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  /* Necessario para LONG_MIN e LONG_MAX */

/* ============================================================
 *  QUESTOES CONCEITUAIS
 * ============================================================
 *
 * Questao 1  - c) Menores a esquerda, maiores a direita
 * Questao 2  - c) Em ordem
 * Questao 3  - b) O(log n)
 * Questao 4  - b) Se comporta como lista encadeada
 *
 * Questao 5:
 *   Insercao: compara o valor com o no atual. Se menor, vai a
 *   esquerda; se maior, vai a direita. Repete ate encontrar NULL,
 *   onde o novo no e criado.
 *
 * Questao 6:
 *   Busca: compara o valor com o no atual. Se igual, encontrou.
 *   Se menor, busca a esquerda; se maior, a direita. Se NULL,
 *   nao existe.
 *
 * Questao 7:
 *   Folha       - remove diretamente, pai aponta NULL.
 *   Um filho    - substitui pelo unico filho.
 *   Dois filhos - copia o sucessor em ordem (menor da subarvore
 *                 direita) e remove o sucessor.
 *
 * Questao 8:
 *   Ordenacao dos dados: busca, insercao e remocao em O(log n)
 *   no caso medio, versus O(n) na arvore binaria comum.
 *
 * Questao 9:
 *   Insercoes sequenciais (ja ordenadas) degeneram a ABB em
 *   lista encadeada, levando as operacoes de O(log n) a O(n).
 *
 * ============================================================ */

/* ============================================================
 *  ESTRUTURA E FUNCOES AUXILIARES
 * ============================================================ */

struct No {
    int dado;
    struct No *esquerda;
    struct No *direita;
};

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

/* ============================================================
 *  IMPLEMENTACAO (Questoes 10 a 19)
 * ============================================================ */

/* Questao 10 - Insercao recursiva */
struct No* inserir(struct No *raiz, int valor) {
    if (raiz == NULL)
        return criarNo(valor);
    if (valor < raiz->dado)
        raiz->esquerda = inserir(raiz->esquerda, valor);
    else if (valor > raiz->dado)
        raiz->direita = inserir(raiz->direita, valor);
    return raiz;
}

/* Questao 11 - Busca recursiva */
struct No* buscar(struct No *raiz, int valor) {
    if (raiz == NULL)
        return NULL;
    if (valor == raiz->dado)
        return raiz;
    if (valor < raiz->dado)
        return buscar(raiz->esquerda, valor);
    return buscar(raiz->direita, valor);
}

/* Questao 12 - Em ordem */
void emOrdem(struct No *raiz) {
    if (raiz == NULL)
        return;
    emOrdem(raiz->esquerda);
    printf("%d ", raiz->dado);
    emOrdem(raiz->direita);
}

/* Funcao auxiliar: menor no da subarvore */
struct No* encontrarMinimo(struct No *raiz) {
    while (raiz->esquerda != NULL)
        raiz = raiz->esquerda;
    return raiz;
}

/* Questao 13 - Remocao de folha (apenas folhas) */
struct No* removerFolha(struct No *raiz, int valor) {
    if (raiz == NULL)
        return NULL;
    if (valor < raiz->dado)
        raiz->esquerda = removerFolha(raiz->esquerda, valor);
    else if (valor > raiz->dado)
        raiz->direita = removerFolha(raiz->direita, valor);
    else if (raiz->esquerda == NULL && raiz->direita == NULL) {
        free(raiz);
        return NULL;
    }
    return raiz;
}

/* Questao 14 - Remocao de no com um filho */
struct No* removerUmFilho(struct No *raiz, int valor) {
    if (raiz == NULL)
        return NULL;
    if (valor < raiz->dado)
        raiz->esquerda = removerUmFilho(raiz->esquerda, valor);
    else if (valor > raiz->dado)
        raiz->direita = removerUmFilho(raiz->direita, valor);
    else {
        if (raiz->esquerda == NULL) {
            struct No *temp = raiz->direita;
            free(raiz);
            return temp;
        }
        if (raiz->direita == NULL) {
            struct No *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
    }
    return raiz;
}

/* Questao 15 - Remocao completa (3 casos, sucessor em ordem) */
struct No* remover(struct No *raiz, int valor) {
    if (raiz == NULL)
        return NULL;
    if (valor < raiz->dado)
        raiz->esquerda = remover(raiz->esquerda, valor);
    else if (valor > raiz->dado)
        raiz->direita = remover(raiz->direita, valor);
    else {
        /* Caso 1: folha */
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }
        /* Caso 2: um filho (direita) */
        if (raiz->esquerda == NULL) {
            struct No *temp = raiz->direita;
            free(raiz);
            return temp;
        }
        /* Caso 2: um filho (esquerda) */
        if (raiz->direita == NULL) {
            struct No *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        /* Caso 3: dois filhos -> usar sucessor em ordem */
        struct No *sucessor = encontrarMinimo(raiz->direita);
        raiz->dado = sucessor->dado;
        raiz->direita = remover(raiz->direita, sucessor->dado);
    }
    return raiz;
}

/* Questao 16 - Menor e maior valor */
int encontrarMenor(struct No *raiz) {
    if (raiz == NULL) return -1;
    while (raiz->esquerda != NULL)
        raiz = raiz->esquerda;
    return raiz->dado;
}

int encontrarMaior(struct No *raiz) {
    if (raiz == NULL) return -1;
    while (raiz->direita != NULL)
        raiz = raiz->direita;
    return raiz->dado;
}

/* Questao 17 - Verifica se e uma ABB valida */
int ehABB(struct No *raiz, long min, long max) {
    if (raiz == NULL)
        return 1;
    if ((long)raiz->dado <= min || (long)raiz->dado >= max)
        return 0;
    return ehABB(raiz->esquerda, min, (long)raiz->dado) &&
           ehABB(raiz->direita, (long)raiz->dado, max);
}

int verificarABB(struct No *raiz) {
    return ehABB(raiz, LONG_MIN, LONG_MAX);
}

/* Questao 18 - Contar niveis (altura + 1) */
int contarNiveis(struct No *raiz) {
    if (raiz == NULL)
        return 0;
    int altEsq = contarNiveis(raiz->esquerda);
    int altDir = contarNiveis(raiz->direita);
    return (altEsq > altDir ? altEsq : altDir) + 1;
}

/* Percursos auxiliares */
void preOrdem(struct No *raiz) {
    if (raiz == NULL) return;
    printf("%d ", raiz->dado);
    preOrdem(raiz->esquerda);
    preOrdem(raiz->direita);
}

void posOrdem(struct No *raiz) {
    if (raiz == NULL) return;
    posOrdem(raiz->esquerda);
    posOrdem(raiz->direita);
    printf("%d ", raiz->dado);
}

void liberarArvore(struct No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

/* ============================================================
 *  DESAFIOS (Questoes 20 a 24)
 * ============================================================ */

/* Questao 20 - Insercao iterativa */
struct No* inserirIterativo(struct No *raiz, int valor) {
    struct No *novo = criarNo(valor);
    if (raiz == NULL) return novo;
    struct No *atual = raiz, *pai = NULL;
    while (atual != NULL) {
        pai = atual;
        if (valor < atual->dado)
            atual = atual->esquerda;
        else if (valor > atual->dado)
            atual = atual->direita;
        else {
            free(novo);  /* valor ja existe */
            return raiz;
        }
    }
    if (valor < pai->dado)
        pai->esquerda = novo;
    else
        pai->direita = novo;
    return raiz;
}

/* Busca iterativa */
struct No* buscarIterativo(struct No *raiz, int valor) {
    struct No *atual = raiz;
    while (atual != NULL) {
        if (valor == atual->dado)
            return atual;
        atual = (valor < atual->dado) ? atual->esquerda : atual->direita;
    }
    return NULL;
}

/* Em ordem iterativo com pilha */
#define MAX_PILHA 100

struct Pilha {
    struct No *dados[MAX_PILHA];
    int topo;
};

void empilhar(struct Pilha *p, struct No *no) {
    if (p->topo < MAX_PILHA - 1)
        p->dados[++(p->topo)] = no;
}

struct No* desempilhar(struct Pilha *p) {
    return (p->topo >= 0) ? p->dados[(p->topo)--] : NULL;
}

void emOrdemIterativo(struct No *raiz) {
    struct Pilha pilha;
    pilha.topo = -1;
    struct No *atual = raiz;
    while (atual != NULL || pilha.topo >= 0) {
        while (atual != NULL) {
            empilhar(&pilha, atual);
            atual = atual->esquerda;
        }
        atual = desempilhar(&pilha);
        printf("%d ", atual->dado);
        atual = atual->direita;
    }
}

/* Questao 22 - Espelhar in-place */
void espelharInPlace(struct No *raiz) {
    if (raiz == NULL) return;
    struct No *temp = raiz->esquerda;
    raiz->esquerda = raiz->direita;
    raiz->direita = temp;
    espelharInPlace(raiz->esquerda);
    espelharInPlace(raiz->direita);
}

/* Questao 23 - Verificar balanceamento */
int verificarBalanceamento(struct No *raiz) {
    if (raiz == NULL) return 0;
    int altEsq = verificarBalanceamento(raiz->esquerda);
    if (altEsq == -1) return -1;
    int altDir = verificarBalanceamento(raiz->direita);
    if (altDir == -1) return -1;
    int dif = altEsq - altDir;
    if (dif < 0) dif = -dif;
    return (dif > 1) ? -1 : ((altEsq > altDir ? altEsq : altDir) + 1);
}

int ehBalanceada(struct No *raiz) {
    return verificarBalanceamento(raiz) != -1;
}

/* Questao 24 - Pesquisa sobre estruturas avancadas:
 *
 * AVL: Arvore BST auto-balanceada. O fator de balanceamento de cada no
 *   (diferenca de altura entre subarvores) e no maximo 1. Rotacoes
 *   simples e duplas mantem a propriedade. Garante O(log n) no pior caso.
 *
 * Rubro-Negra: BST auto-balanceada com nos coloridos (vermelho/preto).
 *   Raiz e preta; no vermelho nao pode ter filho vermelho; todo caminho
 *   ate folha NULL tem o mesmo numero de nos pretos. O(log n) garantido.
 *   Usada em TreeMap (Java), map/set (C++).
 *
 * B-Tree: Arvore balanceada para acesso em blocos. Cada no armazena
 *   multiplas chaves e tem multiplos filhos. Padrao para indices de
 *   bancos de dados e sistemas de arquivos. B+ Tree: dados so nas folhas.
 */

/* ============================================================
 *  MAIN - Questao 19: Menu interativo
 * ============================================================ */
int main() {
    struct No *raiz = NULL;
    int opcao, valor;

    printf("========================================\n");
    printf("  Lista 03 - Arvores Binarias de Busca\n");
    printf("  Nome: Adriel Barros Teixeira\n");
    printf("  Modulo III - ADS\n");
    printf("========================================\n\n");

    do {
        printf("\n========== MENU ABB ==========\n");
        printf("  1. Inserir\n");
        printf("  2. Buscar\n");
        printf("  3. Remover\n");
        printf("  4. Imprimir em ordem\n");
        printf("  5. Mostrar altura\n");
        printf("  6. Encerrar\n");
        printf("==============================\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Valor: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                printf("Inserido: %d\n", valor);
                break;
            case 2:
                printf("Valor: ");
                scanf("%d", &valor);
                if (buscar(raiz, valor) != NULL)
                    printf("%d encontrado.\n", valor);
                else
                    printf("%d nao encontrado.\n", valor);
                break;
            case 3:
                printf("Valor: ");
                scanf("%d", &valor);
                if (buscar(raiz, valor) != NULL) {
                    raiz = remover(raiz, valor);
                    printf("Removido: %d\n", valor);
                } else {
                    printf("Valor %d nao encontrado. Nada removido.\n", valor);
                }
                break;
            case 4:
                printf("Em ordem: ");
                emOrdem(raiz);
                printf("\n");
                break;
            case 5:
                printf("Altura: %d\n", contarNiveis(raiz) - 1);
                printf("Niveis: %d\n", contarNiveis(raiz));
                break;
            case 6:
                liberarArvore(raiz);
                printf("Encerrado.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 6);

    return 0;
}
