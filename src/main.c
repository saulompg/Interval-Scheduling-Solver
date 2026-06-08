#include <stdio.h>
#include <stdlib.h>
#include "atividade.h"
#include "algoritmos.h"
#include "testes.h"
#include "telas.h"

const char *CARGA_1 = "./data/carga_1.csv";
const char *CARGA_2 = "./data/carga_2.csv";
const char *CARGA_3 = "./data/carga_3.csv";


int main() {
    Atividade atividades[100]; 
    int qtd_atual = 0;
    int opcao;

    do {
        exibirMenu();
        if (scanf(" %d", &opcao) != 1) {
            printf("\nEntrada invalida!\n");
            while(getchar() != '\n'); 
            continue;
        }

        switch (opcao) {
        	case 1:
                cadastrarAtividade(atividades, &qtd_atual);
                break;
            case 2: {
            	if (qtd_atual == 0) {
                	printf("\n[-] Nenhuma atividade cadastrada. Por favor, carregue um teste primeiro.\n");
                	break;
            	}
            	
            	int sub_opcao;
            	exibirCriterioOrdenacao();
            	
            	if (scanf(" %d", &sub_opcao) != 1) {
                    printf("\n[-] Entrada invalida! Listando na ordem atual...\n");
                    while(getchar() != '\n'); // Limpa o buffer
                } else {
                    // Chama o Merge Sort com o crit rio escolhido
                    switch (sub_opcao) {               
		               case 1:
		               		mergeSort(atividades, 0, qtd_atual - 1, POR_ID);
                            printf("\n[+] Ordenado por ID.\n");
                            break;
						case 2:
                            mergeSort(atividades, 0, qtd_atual - 1, POR_INICIO);
                            printf("\n[+] Ordenado por Horario de Inicio.\n");
                            break;
                        case 3:
                            mergeSort(atividades, 0, qtd_atual - 1, POR_FIM);
                            printf("\n[+] Ordenado por Horario de Termino.\n");
                            break;
                        case 4:
                            mergeSort(atividades, 0, qtd_atual - 1, POR_PRIORIDADE);
                            printf("\n[+] Ordenado por Prioridade.\n");
                            break;
                        default:
                            printf("\n[-] Opcao invalida. Mantendo ordem atual.\n");
                            break;
                    }
                }
                
                listarAtividades(atividades, qtd_atual);
            	
				break;
			}
            case 3: {
	            if (qtd_atual == 0) {
	                printf("\n[-] Nenhuma atividade para processar. Por favor, carregue um teste primeiro.\n");
	                break;
	            }
	            
                Atividade selecionadas[100];
                
                // Prepara os dados ordenados por fim
                mergeSort(atividades, 0, qtd_atual - 1, POR_FIM);
                
                // Executa a l gica de sele  o
                int qtd_selecionadas = executarGuloso(atividades, qtd_atual, selecionadas);
                
                // Exibe a tela
                exibirResultadoGuloso(selecionadas, qtd_selecionadas, qtd_atual);
	            
	            break;
	        }
            case 4: {
	            if (qtd_atual == 0) {
	                printf("\n[-] Nenhuma atividade para processar.  Por favor, carregue um teste primeiro.\n");
	                break;
	            }
	            
                Atividade selecionadas[100];
                int qtd_selecionadas;
                int sub_opcao;
                
                exibirCriterioMaximizacao();
                scanf("%d", &sub_opcao);
                
                if (sub_opcao == 1 || sub_opcao == 2) {
                	// Prepara os dados ordenados por fim
                	mergeSort(atividades, 0, qtd_atual - 1, POR_FIM);
				}

	            if (sub_opcao == 1) {
                	// Crit rio: Prioridade
                    qtd_selecionadas = executarPD(atividades, qtd_atual, selecionadas, PESO_PRIORIDADE);
                    exibirResultadoPD(selecionadas, qtd_selecionadas, "Prioridade");
                    
                } else if (sub_opcao == 2) {
                	// Crit rio: Participantes
                    qtd_selecionadas = executarPD(atividades, qtd_atual, selecionadas, PESO_PARTICIPANTES);
                    exibirResultadoPD(selecionadas, qtd_selecionadas, "Participantes");
                    
                } else {
					printf("\nOpcao invalida.\n");
                }

	            break;
	        }
            case 5: {
	            if (qtd_atual == 0) {
	                printf("\n[-] Nenhuma atividade carregada. Por favor, carregue um teste primeiro.\n");
	                break;
	            }
	            
                printf("\nProcessando Benchmarking com %d atividades...\n", qtd_atual);
                
                // processamentos na camada de algoritmos
                RelatorioDesempenho rg = gerarRelatorioGuloso(atividades, qtd_atual);
                RelatorioDesempenho rpd = gerarRelatorioPD(atividades, qtd_atual, PESO_PRIORIDADE);
                
                exibirComparacaoDesempenho(rg, rpd);
                
	            break;
	        }
            case 7: {
			 	// Tenta carregar o arquivo CSV
			    int lidas = carregarArquivoDeTestes(CARGA_1, atividades, &qtd_atual);
			    
			    if (lidas == -1) {
			        printf("\n[-] Erro: Arquivo '%s' nao encontrado no diretorio.\n", CARGA_1);
			    } else {
			        printf("\n[+] Teste 1 carregado com sucesso: %d novas atividades importadas.\n", lidas);
			    }
                break;
			}
            case 8: {
			 	// Tenta carregar o arquivo CSV
			    int lidas = carregarArquivoDeTestes(CARGA_2, atividades, &qtd_atual);
			    
			    if (lidas == -1) {
			        printf("\n[-] Erro: Arquivo '%s' nao encontrado no diretorio.\n", CARGA_2);
			    } else {
			        printf("\n[+] Teste 2 carregado com sucesso: %d novas atividades importadas.\n", lidas);
			    }
                break;
			}
            case 9: {
			 	// Tenta carregar o arquivo CSV
			    int lidas = carregarArquivoDeTestes(CARGA_3, atividades, &qtd_atual);
			    
			    if (lidas == -1) {
			        printf("\n[-] Erro: Arquivo '%s' nao encontrado no diretorio.\n", CARGA_3);
			    } else {
			        printf("\n[+] Teste 3 carregado com sucesso: %d novas atividades importadas.\n", lidas);
			    }
                break;
			}
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

	system("pause");
    return 0;
}
