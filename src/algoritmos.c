#include "algoritmos.h"
#include <windows.h>
#include <stdlib.h>

/* =========================================================================
   IMPLEMENTACAO DO MERGE SORT
========================================================================= */

void merge(Atividade arr[], int l, int m, int r, CriterioOrdenacao criterio) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Atividade L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    
    while (i < n1 && j < n2) {
        int condicao = 0;
        
        // Avalia qual campo deve ser comparado com base no parâmetro
        switch (criterio) {
        	case POR_ID:
                condicao = (L[i].id <= R[j].id);
                break;
            case POR_INICIO:
                condicao = (L[i].inicio <= R[j].inicio);
                break;
            case POR_FIM:
                condicao = (L[i].fim <= R[j].fim);
                break;
            case POR_PRIORIDADE:
                condicao = (L[i].prioridade <= R[j].prioridade);
                break;
        }

        if (condicao) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }
}

void mergeSort(Atividade arr[], int l, int r, CriterioOrdenacao criterio) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, criterio);
        mergeSort(arr, m + 1, r, criterio);
        merge(arr, l, m, r, criterio);
    }
}

/* =========================================================================
   IMPLEMENTACAO DO ALGORITMO GULOSO
========================================================================= */

int executarGuloso(Atividade atividades[], int qtd, Atividade selecionadas[]) {
    // Retorna 0 se não houver dados
    if (qtd == 0) return 0; 

    int count = 0;
    
    // A primeira atividade (após a ordenação) é sempre escolhida
    selecionadas[count] = atividades[0];
    count++;
    
    int index_ultima_selecionada = 0;

    // Itera verificando a sobreposição
    for (int j = 1; j < qtd; j++) {
        if (atividades[j].inicio >= atividades[index_ultima_selecionada].fim) {
            selecionadas[count] = atividades[j];
            count++;
            index_ultima_selecionada = j; 
        }
    }

    // Retorna a quantidade de atividades que couberam na agenda
    return count;
}

/* =========================================================================
   IMPLEMENTACAO DA PROGRAMACAO DINAMICA (Weighted Interval Scheduling)
========================================================================= */

int buscarUltimoNaoConflitante(Atividade atividades[], int i) {
    // Busca de trás para frente a primeira atividade que termina antes de 'i' começar
    for (int j = i - 1; j >= 0; j--) {
        if (atividades[j].fim <= atividades[i].inicio) {
            return j;
        }
    }
    return -1; // Retorna -1 se todas as anteriores conflitarem
}

int executarPD(Atividade atividades[], int qtd, Atividade selecionadas[], CriterioPeso pesoEscolhido) {
    if (qtd == 0) return 0;

    // Tabela de Memoization para armazenar o benefício máximo (peso) até 'i'
    int *M = (int *)malloc(qtd * sizeof(int));
    
	// Define o peso base da primeira atividade
	M[0] = (pesoEscolhido == PESO_PRIORIDADE) ? (6 - atividades[0].prioridade) : atividades[0].participantes;

    // Preenchendo a tabela
    for (int i = 1; i < qtd; i++) {
    	// Seleciona o peso da atividade atual com base na estratégia
		int pesoAtual = (pesoEscolhido == PESO_PRIORIDADE) ? (6 - atividades[i].prioridade) : atividades[i].participantes; 
		       
        // Opção A: Incluir a atividade atual
        int pesoInclusao = pesoAtual;
        int l = buscarUltimoNaoConflitante(atividades, i);
        if (l != -1) {
            pesoInclusao += M[l];
        }

        // Opção B: Excluir a atividade atual (pegar o melhor resultado anterior)
        int pesoExclusao = M[i - 1];

        // Guarda o melhor cenário na tabela
        M[i] = (pesoInclusao > pesoExclusao) ? pesoInclusao : pesoExclusao;
    }

    // Backtracking: Descobrindo quais atividades foram selecionadas
    int count = 0;
    int i = qtd - 1;
    Atividade temp[qtd]; // Array temporário porque o backtrack acha os itens de trás pra frente

    while (i >= 0) {
        // Se for o primeiro elemento, ele entra direto
        if (i == 0) {
            temp[count++] = atividades[i];
            break;
        }

		int pesoAtual = (pesoEscolhido == PESO_PRIORIDADE) ? (6 - atividades[i].prioridade) : atividades[i].participantes;
        int pesoInclusao = pesoAtual;
        
        int l = buscarUltimoNaoConflitante(atividades, i);
        if (l != -1) pesoInclusao += M[l];

        // Se o peso incluindo a atividade atual for estritamente MAIOR que a exclusão dela, 
        // significa que ela faz parte da solução ótima.
        if (pesoInclusao > M[i - 1]) {
            temp[count++] = atividades[i];
            i = l; // Pula para a próxima atividade não conflitante
        } else {
            i--; // Não faz parte da solução, desce um degrau
        }
    }

    // Inverte o array temporário para entregar em ordem cronológica à interface
    for (int j = 0; j < count; j++) {
        selecionadas[j] = temp[count - 1 - j];
    }

    free(M); // Prevenção de vazamento de memória (Memory Leak)
    return count;
}

/* =========================================================================
   MÓDULO DE BENCHMARKING E DESEMPENHO (ALTA PRECISÃO)
========================================================================= */

RelatorioDesempenho gerarRelatorioGuloso(Atividade atividades[], int qtd) {
    RelatorioDesempenho relatorio = {0, 0, 0.0};
    if (qtd == 0) return relatorio;

    Atividade copia[100];
    Atividade selecionadas[100];
    for(int i = 0; i < qtd; i++) copia[i] = atividades[i];

	// ORDENA ANTES DO CRONÔMETRO
    mergeSort(copia, 0, qtd - 1, POR_FIM);

    // Variáveis de alta precisão do Windows
    LARGE_INTEGER frequencia, inicio, fim;
    QueryPerformanceFrequency(&frequencia); // Pega a frequência do processador

    // Cronometragem isolada de alta precisão
    QueryPerformanceCounter(&inicio);
    relatorio.atividades_selecionadas = executarGuloso(copia, qtd, selecionadas);
    QueryPerformanceCounter(&fim);

    // Calcula o tempo exato em milissegundos
    relatorio.tempo_execucao_ms = (double)(fim.QuadPart - inicio.QuadPart) * 1000.0 / frequencia.QuadPart;

    // Extração da métrica de prioridade
    for(int i = 0; i < relatorio.atividades_selecionadas; i++) {
        relatorio.soma_peso += selecionadas[i].prioridade;
    }

    return relatorio;
}

RelatorioDesempenho gerarRelatorioPD(Atividade atividades[], int qtd, CriterioPeso pesoEscolhido) {
    RelatorioDesempenho relatorio = {0, 0, 0.0};
    if (qtd == 0) return relatorio;

    Atividade copia[100];
    Atividade selecionadas[100];
    for(int i = 0; i < qtd; i++) copia[i] = atividades[i];
    
    // ORDENA ANTES DO CRONÔMETRO
    mergeSort(copia, 0, qtd - 1, POR_FIM);

    // Variáveis de alta precisão do Windows
    LARGE_INTEGER frequencia, inicio, fim;
    QueryPerformanceFrequency(&frequencia);

    // Cronometragem isolada de alta precisão
    QueryPerformanceCounter(&inicio);
    relatorio.atividades_selecionadas = executarPD(copia, qtd, selecionadas, pesoEscolhido);
    QueryPerformanceCounter(&fim);

    // Calcula o tempo exato em milissegundos
    relatorio.tempo_execucao_ms = (double)(fim.QuadPart - inicio.QuadPart) * 1000.0 / frequencia.QuadPart;

    // Extração da métrica de prioridade
    for(int i = 0; i < relatorio.atividades_selecionadas; i++) {
        relatorio.soma_peso += selecionadas[i].prioridade;
    }

    return relatorio;
}
