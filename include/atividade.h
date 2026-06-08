#ifndef ATIVIDADE_H
#define ATIVIDADE_H

typedef struct {
    int id;
    char nome[50];
    float inicio;
    float fim;
    int prioridade;
    int participantes;
} Atividade;

int salvarAtividade(Atividade atividades[], int *qtd, Atividade nova);

#endif
