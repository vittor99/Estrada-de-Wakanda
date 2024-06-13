#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

int compararCidades(const void *a, const void *b) {
    return ((Cidade *)a)->Posicao - ((Cidade *)b)->Posicao;
}

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Erro: Não foi possível abrir o arquivo.\n");
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (!estrada) {
        printf("Erro: Não foi possível alocar memória para Estrada.\n");
        fclose(file);
        return NULL;
    }

    fscanf(file, "%d %d", &estrada->T, &estrada->N);

    if (estrada->T < 3 || estrada->T > 1000000 || estrada->N < 2 || estrada->N > 10000) {
        printf("Erro: Restrições dos parâmetros T ou N não são atendidas.\n");
        free(estrada);
        fclose(file);
        return NULL;
    }

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) {
        printf("Erro: Não foi possível alocar memória para o vetor de cidades.\n");
        free(estrada);
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        if (fscanf(file, "%d %[^\n]", &estrada->C[i].Posicao, estrada->C[i].Nome) != 2) {
            printf("Erro: Falha ao ler dados da cidade.\n");
            free(estrada->C);
            free(estrada);
            fclose(file);
            return NULL;
        }
        if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= estrada->T) {
            printf("Erro: Posição da cidade fora dos limites. Cidade: %s, Posição: %d\n", estrada->C[i].Nome, estrada->C[i].Posicao);
            free(estrada->C);
            free(estrada);
            fclose(file);
            return NULL;
        }
    }

    qsort(estrada->C, estrada->N, sizeof(Cidade), compararCidades);

    fclose(file);
    return estrada;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return -1.0;

    double menorVizinhanca = (double)estrada->T;

    menorVizinhanca = estrada->C[0].Posicao < menorVizinhanca ? estrada->C[0].Posicao : menorVizinhanca;

    for (int i = 1; i < estrada->N; i++) {
        double vizinhanca = (double)(estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    double vizinhancaUltimaCidade = estrada->T - estrada->C[estrada->N - 1].Posicao;
    if (vizinhancaUltimaCidade < menorVizinhanca) {
        menorVizinhanca = vizinhancaUltimaCidade;
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return NULL;

    double menorVizinhanca = (double)estrada->T;
    int index = -1;

    if (estrada->C[0].Posicao < menorVizinhanca) {
        menorVizinhanca = estrada->C[0].Posicao;
        index = 0;
    }

    for (int i = 1; i < estrada->N; i++) {
        double vizinhanca = (double)(estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            index = i;
        }
    }

    if (estrada->T - estrada->C[estrada->N - 1].Posicao < menorVizinhanca) {
        menorVizinhanca = estrada->T - estrada->C[estrada->N - 1].Posicao;
        index = estrada->N - 1;
    }

    char *result = (char *)malloc(strlen(estrada->C[index].Nome) + 1);
    if (result) {
        strcpy(result, estrada->C[index].Nome);
    }

    free(estrada->C);
    free(estrada);
    return result;
}
