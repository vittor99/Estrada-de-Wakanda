#include <stdio.h>
#include "cidades.h"

int main() {
    const char *nomeArquivo = "teste01.txt";

    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada) {
        printf("Estrada inicializada com sucesso.\n");
        printf("Comprimento da estrada: %d\n", estrada->T);
        printf("Número de cidades: %d\n", estrada->N);
        for (int i = 0; i < estrada->N; i++) {
            printf("Cidade: %s, Posição: %d\n", estrada->C[i].Nome, estrada->C[i].Posicao);
        }
    } else {
        printf("Falha ao inicializar a estrada.\n");
    }

    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    if (menorVizinhanca >= 0) {
        printf("Menor vizinhança: %.2f\n", menorVizinhanca);
    } else {
        printf("Falha ao calcular a menor vizinhança.\n");
    }

    char *cidade = cidadeMenorVizinhanca(nomeArquivo);
    if (cidade) {
        printf("Cidade com menor vizinhança: %s\n", cidade);
        free(cidade);
    } else {
        printf("Falha ao determinar a cidade com menor vizinhança.\n");
    }

    if (estrada) {
        free(estrada->C);
        free(estrada);
    }

    return 0;
}