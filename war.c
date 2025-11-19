#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_STRING 100
#define NUM_MISSOES 5

typedef struct {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int qntTropa;
} Territorio;

typedef struct {
    char* missao;
} Jogador;

void limparBufferEntrada();
void cadastrarTerritorios(Territorio *mapa, int n);
void exibirMapa(Territorio *mapa, int n);
void atacar(Territorio *atacante, Territorio *defensor);
void liberarMemoria(Territorio *mapa);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);

int main() {
    srand(time(NULL));

    int qntTerritorios;
    printf("Quantos territórios deseja cadastrar? ");
    while (scanf("%d", &qntTerritorios) != 1 || qntTerritorios <= 0) {
        printf("Entrada inválida. Digite um número positivo: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();

    Territorio *mundo = calloc(qntTerritorios, sizeof(Territorio));
    if (mundo == NULL) return 1;

    cadastrarTerritorios(mundo, qntTerritorios);
    exibirMapa(mundo, qntTerritorios);

    char* missoes[NUM_MISSOES] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Possuir todos os territórios pares",
        "Ter mais tropas que todos os outros",
        "Controlar 2 territórios de cores diferentes"
    };

    Jogador jogador1, jogador2;
    jogador1.missao = malloc(TAM_STRING);
    jogador2.missao = malloc(TAM_STRING);

    atribuirMissao(jogador1.missao, missoes, NUM_MISSOES);
    atribuirMissao(jogador2.missao, missoes, NUM_MISSOES);

    printf("Missão do Jogador 1: %s\n", jogador1.missao);
    printf("Missão do Jogador 2: %s\n", jogador2.missao);

    int atacante, defensor;
    char continuarAtaque;

    do {
        printf("\n--- NOVO ATAQUE ---\n");

        printf("Escolha o território atacante (1 a %d): ", qntTerritorios);
        while (scanf("%d", &atacante) != 1) limparBufferEntrada();
        limparBufferEntrada();

        printf("Escolha o território defensor (1 a %d): ", qntTerritorios);
        while (scanf("%d", &defensor) != 1) limparBufferEntrada();
        limparBufferEntrada();

        if (atacante < 1 || atacante > qntTerritorios || defensor < 1 || defensor > qntTerritorios) {
            printf("Seleção de território inválida. Tente novamente.\n");
            continuarAtaque = 'S';
            continue;
        }

        atacante--;
        defensor--;

        if (atacante == defensor) {
            printf("Um território não pode atacar a si mesmo!\n");
        } else if (mundo[atacante].qntTropa <= 1) {
            printf("Território atacante precisa de pelo menos 2 tropas para atacar.\n");
        } else {
            atacar(&mundo[atacante], &mundo[defensor]);
        }

        exibirMapa(mundo, qntTerritorios);

        if (verificarMissao(jogador1.missao, mundo, qntTerritorios)) {
            printf("Jogador 1 cumpriu sua missão e venceu!\n");
            break;
        }
        if (verificarMissao(jogador2.missao, mundo, qntTerritorios)) {
            printf("Jogador 2 cumpriu sua missão e venceu!\n");
            break;
        }

        printf("Deseja realizar outro ataque? (S/N): ");
        scanf(" %c", &continuarAtaque);
        limparBufferEntrada();

    } while (continuarAtaque == 's' || continuarAtaque == 'S');

    liberarMemoria(mundo);
    free(jogador1.missao);
    free(jogador2.missao);

    return 0;
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarTerritorios(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome do Território: ");
        scanf("%99s", mapa[i].nome);
        limparBufferEntrada();

        printf("Cor do Exército: ");
        scanf("%99s", mapa[i].cor);
        limparBufferEntrada();

        printf("Número de tropas: ");
        while (scanf("%d", &mapa[i].qntTropa) != 1 || mapa[i].qntTropa < 1) limparBufferEntrada();
        limparBufferEntrada();
    }
}

void exibirMapa(Territorio *mapa, int n) {
    printf("\n==== MAPA DO MUNDO ====\n");
    for (int i = 0; i < n; i++)
        printf("%d. %s (Exército: %s, Tropas: %d)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].qntTropa);
    printf("\n");
}

void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado do atacante: %d | Dado do defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        defensor->qntTropa -= 1;
        if (defensor->qntTropa <= 0) {
            strcpy(defensor->cor, atacante->cor);
            defensor->qntTropa = atacante->qntTropa - 1;
            atacante->qntTropa = 1;
            printf("Território atacante conquistou!\n");
        } else {
            printf("Território atacante venceu a batalha!\n");
        }
    } else {
        atacante->qntTropa -= 1;
        printf("Território defensor venceu a batalha!\n");
    }
}

void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strstr(missao, "tropas da cor vermelha") != NULL) {
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].qntTropa > 0) return 0;
        return 1;
    }
    if (strstr(missao, "3 territórios seguidos") != NULL) {
        int cont = 1;
        for (int i = 1; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, mapa[i-1].cor) == 0) cont++;
            else cont = 1;
            if (cont >= 3) return 1;
        }
        return 0;
    }
    return 0;
}
