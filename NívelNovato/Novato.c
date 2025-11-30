#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// STRUCT: Representação da sala
// Cada sala contém:
// - nome: identificação da sala
// - esq: ponteiro para a sala à esquerda
// - dir: ponteiro para a sala à direita

typedef struct sala {
    char nome[50];
    struct sala *esq;
    struct sala *dir;
} Sala;



// FUNÇÃO: criarSala
// Objetivo: criar dinamicamente uma sala.
// Entrada: nome da sala (string)
// Saída: ponteiro para a sala 

Sala* criarSala(char nome[]) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));

    if (nova == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    strcpy(nova->nome, nome);
    nova->esq = NULL;
    nova->dir = NULL;

    return nova;
}



// FUNÇÃO: explorarSalas
// Objetivo: permitir que o jogador explore a mansão.
// Navegação:
//  e → esquerda
//  d → direita
//  s → sair
// A exploração termina quando o jogador chega a um nó sem saída.

void explorarSalas(Sala *atual) {
    char escolha;

    while (atual != NULL) {

        printf("\nVocê está na sala: %s\n", atual->nome);

        // Se for um nó-folha, acaba o jogo
        if (atual->esq == NULL && atual->dir == NULL) {
            printf("Você chegou ao fim do caminho!\n");
            return;
        }

        printf("Escolha um caminho:\n");
        if (atual->esq != NULL) printf(" e - ir para a esquerda\n");
        if (atual->dir != NULL) printf(" d - ir para a direita\n");
        printf(" s - sair da exploração\n");
        printf("\n");

        scanf(" %c", &escolha);   // espaço antes do %c para ignora o ENTER

        if (escolha == 'e' && atual->esq != NULL) {
            atual = atual->esq;
        }
        else if (escolha == 'd' && atual->dir != NULL) {
            atual = atual->dir;
        }
        else if (escolha == 's') {
            printf("Exploração encerrada pelo usuário.\n");
            return;
        }
        else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}



// FUNÇÃO: liberarArvore
// Objetivo: liberar toda a memória alocada para a árvore binária.

void liberarArvore(Sala *atual) {
    if (atual == NULL) return;

    liberarArvore(atual->esq);
    liberarArvore(atual->dir);
    free(atual);
}



// FUNÇÃO: main
// Objetivo: montar o mapa da mansão,
// iniciar a exploração e liberar memória no final.

int main() {

    // Criação da estrutura da mansão (árvore binária)
    Sala *hall        = criarSala("Hall de Entrada");
    Sala *salaEstar   = criarSala("Sala de Estar");
    Sala *cozinha     = criarSala("Cozinha");
    Sala *jardim      = criarSala("Jardim");
    Sala *biblioteca  = criarSala("Biblioteca");

    // Montagem do mapa
    hall->esq = salaEstar;
    hall->dir = cozinha;

    salaEstar->esq = jardim;
    salaEstar->dir = biblioteca;

    // Início da exploração
    printf("=== EXPLORAÇÃO DA MANSÃO ===\n");
    explorarSalas(hall);

    // Libera memória
    liberarArvore(hall);

    return 0;
}
