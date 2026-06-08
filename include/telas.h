#ifndef TELAS_H
#define TELAS_H

#include "atividade.h"
#include "algoritmos.h"

void exibirMenu();

void exibirCriterioMaximizacao();

void exibirCriterioOrdenacao();

void cadastrarAtividade(Atividade atividades[], int *qtd);

void listarAtividades(Atividade atividades[], int qtd);

void exibirResultadoGuloso(Atividade selecionadas[], int qtd_selecionadas, int qtd_total);

void exibirResultadoPD(Atividade selecionadas[], int qtd_selecionadas, const char *tipo_foco);

void exibirComparacaoDesempenho(RelatorioDesempenho rg, RelatorioDesempenho rpd);

#endif
