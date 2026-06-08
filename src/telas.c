#include <stdio.h>
#include <time.h>
#include <string.h>
#include "telas.h"
#include "algoritmos.h"

void exibirMenu() {
    printf("\n=================================================\n");
    printf("   SISTEMA DE AGENDAMENTO DE ATIVIDADES\n");
    printf("=================================================\n");
    printf("1. Cadastrar Atividade Manualmente\n");
    printf("2. Listar Atividades Carregadas\n");
    printf("3. Executar Algoritmo Guloso\n");
    printf("4. Executar Programacao Dinamica\n");
    printf("5. Comparar Solucoes\n");
    printf("7. Carregar Teste 1 (Pequeno - 10 atividades)\n");
    printf("8. Carregar Teste 2 (Medio - 25 atividades)\n");
    printf("9. Carregar Teste 3 (Maior - 50 atividades)\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

void exibirCriterioMaximizacao() {
	printf("\n=======================================\n");
    printf("         CRITERIO DA MAXIMIZACAO       \n");
    printf("=======================================\n");
    printf("1. Maxima Prioridade\n");
    printf("2. Maximo de Participantes\n");
    printf("Escolha uma opcao: ");
}

void exibirCriterioOrdenacao() {
	printf("\n=======================================\n");
    printf("        ORDENACAO DA LISTAGEM          \n");
    printf("=======================================\n");
    printf("1. Ordenar por ID\n");
    printf("2. Horario de Inicio (Mais cedo primeiro)\n");
    printf("3. Horario de Termino (Mais cedo primeiro)\n");
    printf("4. Prioridade (Mais importantes primeiro)\n");
    printf("Escolha uma opcao: ");
}

void listarAtividades(Atividade atividades[], int qtd) {
    if (qtd == 0) {
        printf("\n[-] Nenhuma atividade carregada. Por favor, carregue um teste primeiro.\n");
        return;
    }
    
    printf("\nID | Nome                                               | Inicio |  Fim  | Prioridade | Participantes\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < qtd; i++) {
    	
    	// convers o para formato hh:mm
    	int h_inicio = (int)atividades[i].inicio;
		int m_inicio = (int)((atividades[i].inicio - h_inicio) * 60 + 0.5);
		
		int h_fim = (int)atividades[i].fim;
		int m_fim = (int)((atividades[i].fim - h_fim) * 60 + 0.5);
    	
        printf("%02d | %-50s | %02d:%02d  | %02d:%02d | %-10d | %d\n", 
               atividades[i].id, 
               atividades[i].nome, 
               h_inicio, m_inicio,
               h_fim, m_fim,
               atividades[i].prioridade, 
               atividades[i].participantes);
    }
}

void cadastrarAtividade(Atividade atividades[], int *qtd) {
	// Vari veis tempor rias
	Atividade atividade;
    int horas, minutos;
	   
    printf("\n--- CADASTRO MANUAL DE ATIVIDADE ---\n");
    
    // Limpeza do buffer do teclado
    while(getchar() != '\n'); 
    
    printf("Nome da atividade (ou digite '0' para cancelar): ");
    fgets(atividade.nome, 50, stdin);
    atividade.nome[strcspn(atividade.nome, "\n")] = 0; 
    
    // Verifica  o do cancelamento r pido
    if (strcmp(atividade.nome, "0") == 0) {
        printf("\n[-] Cadastro cancelado.\n");
        return;
    }
    
    printf("Horario de inicio (formato HH:MM, ex: 08:30): ");
    scanf("%d:%d", &horas, &minutos);
    atividade.inicio = horas + (minutos / 60.0); 	// Converte padr o de hor rio em float
    
    printf("Horario de fim (formato HH:MM, ex: 10:00): ");
    scanf("%d:%d", &horas, &minutos);
    atividade.fim = horas + (minutos / 60.0); 		// Converte padr o de hor rio em float
    
    printf("Prioridade: ");
    scanf("%d", &atividade.prioridade);
    
    printf("Quantidade de participantes: ");
    scanf("%d", &atividade.participantes);
    
    // Confirma  o final
    char confirmacao;
    printf("\nConfirma os dados e deseja salvar a atividade? (S/N): ");
    scanf(" %c", &confirmacao);
    
    if (confirmacao == 'S' || confirmacao == 's') {
    	
		int sucesso = salvarAtividade(atividades, qtd, atividade);
        
        if (sucesso) 
			printf("\n[+] Atividade '%s' cadastrada com sucesso!\n", atividade.nome);
        else
			printf("\n[-] Erro: Limite maximo de atividades atingido.\n");
        
    } else {
        printf("\n[-] Cadastro cancelado. A atividade foi descartada.\n");
    }
}

void exibirResultadoGuloso(Atividade selecionadas[], int qtd_selecionadas, int qtd_total) {
    printf("\n=================================================================================\n");
    printf("   RESULTADO DA SELECAO GULOSA (Foco: Quantidade de Atividades)\n");
    printf("=================================================================================\n");

    for (int i = 0; i < qtd_selecionadas; i++) {
        Atividade a = selecionadas[i];
        
        int h_inicio = (int)a.inicio;
        int m_inicio = (int)(((a.inicio - h_inicio) * 60) + 0.5);
        int h_fim = (int)a.fim;
        int m_fim = (int)(((a.fim - h_fim) * 60) + 0.5);

        printf("%02d. [ID: %02d] %-50s | %02d:%02d as %02d:%02d\n", 
               i + 1, a.id, a.nome, h_inicio, m_inicio, h_fim, m_fim);
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("[+] TOTAL DE ATIVIDADES SELECIONADAS: %d (de %d disponiveis)\n", qtd_selecionadas, qtd_total);
    printf("=================================================================================\n");
}

void exibirResultadoPD(Atividade selecionadas[], int qtd_selecionadas, const char *tipo_foco) {
    printf("\n===============================================================================================\n");
    printf("   RESULTADO DA PROGRAMACAO DINAMICA (Foco: Maximo de %s)\n", tipo_foco);
    printf("===============================================================================================\n");

    int soma_total = 0;
    
    // Flag booleana simples para evitar rodar o strcmp repetidas vezes no la o
    int eh_prioridade = (strcmp(tipo_foco, "Prioridade") == 0);

    for (int i = 0; i < qtd_selecionadas; i++) {
        Atividade a = selecionadas[i];
        
        // Decide qual valor extrair da struct baseado na flag
        int valor_peso = eh_prioridade ? a.prioridade : a.participantes;
        soma_total += valor_peso;
        
        // Convers o com arredondamento seguro para o In cio e Fim
        int h_inicio = (int)a.inicio;
        int m_inicio = (int)(((a.inicio - h_inicio) * 60) + 0.5);
        int h_fim = (int)a.fim;
        int m_fim = (int)(((a.fim - h_fim) * 60) + 0.5);

        // Imprime a linha com o r tulo e o valor correspondentes   escolha do usu rio
        printf("%02d. [ID: %02d] %-50s | %02d:%02d as %02d:%02d | %s: %d\n", 
               i + 1, a.id, a.nome, h_inicio, m_inicio, h_fim, m_fim, tipo_foco, valor_peso);
    }

    printf("-------------------------------------------------------------------------------------\n");
    printf("[+] TOTAL DE ATIVIDADES SELECIONADAS: %d\n", qtd_selecionadas);
    printf("[+] SOMA TOTAL (%s) ATINGIDA: %d\n", tipo_foco, soma_total);
    printf("=====================================================================================\n");
}

void exibirComparacaoDesempenho(RelatorioDesempenho rg, RelatorioDesempenho rpd) {
    printf("\n=======================================================================\n");
    printf("                  QUADRO COMPARATIVO DE DESEMPENHO\n");
    printf("=======================================================================\n");
    printf(" METRICA                    | ALGORITMO GULOSO    | PROG. DINAMICA\n");
    printf("-----------------------------------------------------------------------\n");
    printf(" Foco de Otimizacao         | Maxima Quantidade   | Maxima Prioridade\n");
    printf(" Atividades Selecionadas    | %-19d | %-15d\n", rg.atividades_selecionadas, rpd.atividades_selecionadas);
    printf(" Soma das Prioridades (*)   | %-19d | %-15d\n", rg.soma_peso, rpd.soma_peso);
    printf(" Tempo de Execucao (ms)     | %-19.4f | %-15.4f\n", rg.tempo_execucao_ms, rpd.tempo_execucao_ms);
    printf("=======================================================================\n");
    printf(" (*) Nota: Na escala de prioridade, valores MENORES sao MELHORES (1 a 5).\n");
    printf("=======================================================================\n");
}
