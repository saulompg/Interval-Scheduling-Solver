#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testes.h"

int carregarArquivoDeTestes(const char *caminhoArquivo, Atividade atividades[], int *qtd) {
	FILE *arquivo = fopen(caminhoArquivo, "r");
    
    if (arquivo == NULL) {
        return -1; // Sinaliza que o arquivo não foi encontrado
    }
    
    *qtd = 0;

    char linha[256];
    int lidas_nesta_execucao = 0;

    // Lê e descarta a primeira linha (cabeçalho do CSV)
    fgets(linha, sizeof(linha), arquivo);

    // Lê o arquivo linha por linha até o final
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (*qtd >= 100) {
            break; // Proteção contra estouro do array
        }

        // Remove a quebra de linha do final da string, se existir
        linha[strcspn(linha, "\n")] = 0;
        linha[strcspn(linha, "\r")] = 0; // Previne problemas com arquivos criados no Windows

        Atividade atividade;
        char *token;

        // Fatiamento (Tokenização) com strtok
        token = strtok(linha, ";");
        if (token == NULL) continue; // Pula a linha se estiver mal formatada
        atividade.id = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strncpy(atividade.nome, token, 49);
        atividade.nome[49] = '\0'; // Garante o fechamento da string

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        atividade.inicio = atof(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        atividade.fim = atof(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        atividade.prioridade = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        atividade.participantes = atoi(token);

        // Se chegou até aqui, a linha estava perfeita. Adiciona ao array.
        atividades[*qtd] = atividade;
        (*qtd)++;
        lidas_nesta_execucao++;
    }

    fclose(arquivo);
    return lidas_nesta_execucao;
}
