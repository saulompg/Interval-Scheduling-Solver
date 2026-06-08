#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "atividade.h"

// Definindo os critérios de ordenação
typedef enum {
	POR_ID,
    POR_INICIO,
    POR_FIM,
    POR_PRIORIDADE
} CriterioOrdenacao;

// Definindo as estratégias de peso para a PD
typedef enum {
    PESO_PARTICIPANTES,
    PESO_PRIORIDADE
} CriterioPeso;

// DTO para trafegar as métricas de desempenho entre as camadas
typedef struct {
    int atividades_selecionadas;
    int soma_peso;
    double tempo_execucao_ms;
} RelatorioDesempenho;

// Merge Sort
void mergeSort(Atividade arr[], int l, int r, CriterioOrdenacao criterio);
void merge(Atividade arr[], int l, int m, int r, CriterioOrdenacao criterio);

// Algoritmo Guloso
int executarGuloso(Atividade atividades[], int qtd, Atividade selecionadas[]);

// Programação Dinâmica
int buscarUltimoNaoConflitante(Atividade atividades[], int i);
int executarPD(Atividade atividades[], int qtd, Atividade selecionadas[], CriterioPeso pesoEscolhido);

// Métricas de desempenho
RelatorioDesempenho gerarRelatorioGuloso(Atividade atividades[], int qtd);
RelatorioDesempenho gerarRelatorioPD(Atividade atividades[], int qtd, CriterioPeso pesoEscolhido);

#endif
