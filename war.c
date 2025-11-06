#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERRITORIO 5
#define TAM_STRING 100

struct Territorio {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int qntTropa;
};

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct Territorio mundo[MAX_TERRITORIO];

    printf("Cadastre os cinco territórios iniciais do jogo.\n");

    for (int i = 0; i < MAX_TERRITORIO; i++) {
        printf("\n---- Cadastro de Território %d ----\n", i + 1);

        printf("Nome do Território: ");
        scanf("%s", mundo[i].nome);
        limparBufferEntrada();

        printf("Cor do Exército: ");
        scanf("%s", mundo[i].cor);
        limparBufferEntrada();

        printf("Número de tropas: ");
        scanf("%d", &mundo[i].qntTropa);
        limparBufferEntrada();
    }

    printf("\n========================================\n");
    printf("       MAPA DO MUNDO - ESTADO ATUAL");
    printf("\n========================================\n");

    for (int i = 0; i < MAX_TERRITORIO; i++) {
        printf("\nTERRITÓRIO: %d\n", i + 1);
        printf("   - Nome: %s\n", mundo[i].nome);
        printf("   - Dominado por: Exército %s\n", mundo[i].cor);
        printf("   - Tropas: %d\n", mundo[i].qntTropa);
    }

    return 0;
}
