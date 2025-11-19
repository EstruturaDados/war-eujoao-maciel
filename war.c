#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIO 5
#define TAM_STRING 100

typedef struct {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int qntTropa;
} Territorio;

void cadastrarTerritorios(Territorio *mapa, int n);
void exibirMapa(Territorio *mapa, int n);
void atacar(Territorio *atacante, Territorio *defensor);
void liberarMemoria(Territorio *mapa);

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    srand(time(NULL));

    int qntTerritorios;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qntTerritorios);

    Territorio *mundo = calloc(qntTerritorios, sizeof(Territorio));

    cadastrarTerritorios(mundo, qntTerritorios);
    exibirMapa(mundo, qntTerritorios);

    int atacante, defensor;

    printf("Escolha o território atacante (1, 2, 3...): ");
    scanf("%d", &atacante);

    printf("Escolha o território defensor (1, 2, 3...): ");
    scanf("%d", &defensor);

    atacante--;
    defensor--;

    atacar(&mundo[atacante], &mundo[defensor]);
    exibirMapa(mundo, qntTerritorios);

    liberarMemoria(mundo);
    return 0;
}


void cadastrarTerritorios(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("Nome do Território: ");
        scanf("%s", mapa[i].nome);
        limparBufferEntrada();

        printf("Cor do Exercito: ");
        scanf("%s", mapa[i].cor);
        limparBufferEntrada();

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].qntTropa);
        limparBufferEntrada();
    }
}


void exibirMapa(Territorio *mapa, int n) {
    printf("\n==== MAPA DO MUNDO ====\n");

    for (int i = 0; i < n; i++) {
        printf("%d. %s (Exército: %s, Tropas: %d)\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].qntTropa);
    }

    printf("\n");
}


void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor  = (rand() % 6) + 1;

    if (dadoAtacante > dadoDefensor) {
        int tropasTransferidas = atacante->qntTropa / 2;

        strcpy(defensor->cor, atacante->cor);
        atacante->qntTropa = tropasTransferidas;
        defensor->qntTropa = tropasTransferidas;

        printf("\nTerritório atacante venceu!\n");

    } else if (dadoDefensor > dadoAtacante) {
        atacante->qntTropa -= 1;
        if (atacante->qntTropa < 1)
            atacante->qntTropa = 1;

        printf("\nTerritório defensor venceu!\n");
    }
}


void liberarMemoria(Territorio *mapa) {
    free(mapa);
}
