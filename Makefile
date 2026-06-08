# Nome do compilador
CC = gcc

# Flags de compilação (-I para a pasta de headers, -Wall para mostrar todos os alertas)
CFLAGS = -I./include -Wall -Wextra

# Pastas do projeto
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

# Encontra todos os arquivos .c e define como devem ser os .o
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Nome do arquivo final
EXEC = $(BIN_DIR)/interval-scheduling-solver.exe

# Regra principal (o que roda quando você digita apenas 'make')
all: $(EXEC)

# Regra para compilar o executável final juntando os objetos
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Regra para compilar cada arquivo .c em um .o separadamente
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados (make clean)
clean:
	del /Q $(OBJ_DIR)\*.o
	del /Q $(BIN_DIR)\*.exe