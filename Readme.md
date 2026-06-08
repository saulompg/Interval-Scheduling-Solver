# 📅 Sistema Inteligente de Agendamento de Atividades Corporativas

Este projeto é uma aplicação em **C** desenvolvida para resolver o problema clássico de seleção de intervalos (*Interval Scheduling* e *Weighted Interval Scheduling*). O objetivo do sistema é otimizar a agenda de um evento corporativo ou dia de trabalho, alocando reuniões, palestras e treinamentos de forma a não haver sobreposição de horários.

Para solucionar os conflitos de agenda, o sistema implementa, analisa e compara duas abordagens algorítmicas distintas:
* **Algoritmo Guloso (Greedy):** Focado em maximizar a *quantidade absoluta* de atividades no dia.
* **Programação Dinâmica (Dynamic Programming):** Focada em maximizar o *valor estratégico* (Prioridade) ou o *público total* (Participantes), utilizando técnicas de *Memoization* e *Backtracking*.

---

## 📂 Estrutura do Projeto

O projeto segue a arquitetura padrão da indústria para aplicações em C/C++:

```text
gerenciamento_atividades/
├── bin/          # Executável gerado após a compilação
├── build/        # Arquivos objeto (.o) gerados durante a compilação
├── data/         # Arquivos CSV contendo as cargas de dados reais (Testes)
├── include/      # Arquivos de cabeçalho (.h) com as interfaces
├── src/          # Código-fonte (.c) com as implementações lógicas
├── Makefile      # Script de automação de compilação
└── README.md     # Documentação do projeto
```

## ⚙️ Pré-requisitos
Para compilar e executar este projeto localmente no Windows, você precisará do compilador GCC e da ferramenta Make.

1. Instalação do MinGW (Minimalist GNU for Windows):

- Você pode instalar o MinGW baixando o instalador direto pelo site oficial ou utilizando um gerenciador de pacotes como o MSYS2.

- Se você utiliza a IDE Dev-C++ ou Code::Blocks, é muito provável que o MinGW já esteja instalado na sua máquina.

2. Variáveis de Ambiente (PATH):

- Certifique-se de que o caminho para a pasta bin da sua instalação do MinGW (ex: C:\MinGW\bin ou C:\msys64\mingw64\bin) esteja adicionado à variável de ambiente PATH do seu sistema operacional. Isso permite que o terminal reconheça os comandos de compilação.

## 🛠️ Como Compilar (Build)
O projeto utiliza um Makefile para automatizar o processo de compilação, recompilando apenas os arquivos que sofreram alterações.

1. Abra o seu terminal (CMD, PowerShell ou Git Bash).

2. Navegue até a pasta raiz do projeto:

```Bash
cd caminho/para/gerenciamento atividades
```

3. Execute a ferramenta de build. Dependendo de como o seu MinGW foi instalado, o comando pode ter dois nomes diferentes. Tente um dos seguintes:

```Bash
make
```
ou

```Bash
mingw32-make
```

> Nota: Para limpar os arquivos compilados (se quiser forçar uma compilação 100% nova e limpa da próxima vez), execute make clean ou mingw32-make clean.

🚀 Como Executar
Após a compilação bem-sucedida, o executável será gerado dentro da pasta bin. Para rodá-lo, ainda no terminal na raiz do projeto, digite:

- No PowerShell ou Git Bash:

```Bash
./bin/gerenciamento_atividades.exe
```

- No CMD clássico:

```DOS
bin\gerenciamento_atividades.exe
```

## 🎮 Como Utilizar o Sistema
Ao iniciar o programa, você verá um Menu Principal no terminal. O fluxo ideal de utilização para demonstração das capacidades da ferramenta é:

1. Carregar Dados: As funcionalidades 7, 8 ou 9 permitem importar os arquivos de teste CSV (pequeno, médio ou grande) para a memória do programa.

2. Visualização Dinâmica: Pressione 2 para listar as atividades. Você poderá testar o motor do Merge Sort, escolhendo listar as atividades ordenadas por Horário, ID ou Prioridade.

3. Seleção Gulosa: Pressione 3 para ver o algoritmo priorizar as atividades mais curtas e preencher a agenda com o maior número de eventos possível.

4. Programação Dinâmica: Pressione 4 e escolha qual parâmetro otimizar. Focar na Prioridade (onde Nível 1 é o mais alto) fará o algoritmo varrer as tarefas e sacrificar quantidade para garantir que apenas os eventos mais cruciais (como conselhos e diretorias) sejam marcados. Escolha a opção Participantes para otimizar a escolha das atividades maximizando a quantidade de participantes.

5. Benchmarking: Pressione 5 para a prova real. O sistema executará ambos os algoritmos lado a lado e utilizará o High-Resolution Performance Counter do Windows para medir o tempo de execução (em milissegundos precisos) e exibir o ganho estratégico da Programação Dinâmica em relação ao Algoritmo Guloso.

## 🛠️ Tecnologias Utilizadas
- Linguagem: C
- Bibliotecas Nativas: <stdio.h>, <stdlib.h>, <string.h>
- Medição de Alta Performance: <windows.h> (QueryPerformanceCounter)
- Automação: Makefile / MinGW
