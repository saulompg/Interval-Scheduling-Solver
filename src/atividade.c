#include "atividade.h"

int salvarAtividade(Atividade atividades[], int *qtd, Atividade novaAtividade) {
    if (*qtd >= 100) {
        return 0; // Falha: Limite atingido
    }
    
    // Regra de negócio: Geração do ID
    novaAtividade.id = (*qtd) + 1;
    
    // Manipulação dos dados
    atividades[*qtd] = novaAtividade;
    (*qtd)++;
    
    return 1; // Sucesso
}
