#include "matriz.h"

// Função para criar e alocar dinamicamente uma matriz de caracteres (char).
char** criaMatrizC(int linha, int coluna){
	
    // Aloca espaço para as linhas
    char** matC = (char**) malloc(linha * sizeof(char*));
    if (matC == NULL){ // Verifica falha na alocação
        return NULL;
    }

    // Aloca espaço para as colunas de cada linha
    for (int i = 0; i < linha; i++){
        matC[i] = (char*) malloc(coluna * sizeof(char));
        if (matC[i] == NULL){ // Verifica falha na alocação de uma linha
        
            liberarMatriz((void**)matC, i); // Libera as linhas já alocadas
            return NULL;
        }
    }
    return matC;
}

// Função para criar e alocar dinamicamente uma matriz de inteiros (int).
int** criaMatrizInt(int linha, int coluna){
    
	// Aloca espaço para as linhas
    int** matInt = (int**) malloc(linha * sizeof(int*));
    if (matInt == NULL){ // Verifica falha na alocação
        return NULL;
    }

    // Aloca espaço para as colunas de cada linha
    for (int i = 0; i < linha; i++){
        matInt[i] = (int*) malloc(coluna * sizeof(int));
        if (matInt[i] == NULL){ // Verifica falha na alocação de uma linha
            liberarMatriz((void**)matInt, i); // Libera as linhas já alocadas
            return NULL;
        }
    }
    return matInt;
}

// Função para imprimir a matriz de caracteres.
void imprimirMatC(char** matrizC, int linha, int coluna){
    printf("\n ");

    // Imprime os índices das colunas
    for (int j = 0; j < coluna; j++){
        printf("   %2d ", j + 1);
    }
    printf("\n");

    // Imprime a matriz de caracteres com os índices das linhas
    for (int i = 0; i < linha; i++){
        printf("\n%2d", i + 1); // Índice da linha
        for (int j = 0; j < coluna; j++){
            printf("%5c ", matrizC[i][j]); // Caractere na posição (i, j)
        }
        printf("\n");
    }
}

// Função para imprimir a matriz de inteiros.
void imprimirMatInt(int** matriz, int linha, int coluna){
    printf("\n ");

    // Imprime os índices das colunas
    for (int j = 0; j < coluna; j++){
        printf("   %2d ", j + 1);
    }
    printf("\n");

    // Imprime a matriz de inteiros com os índices das linhas
    for (int i = 0; i < linha; i++){
        printf("\n%2d", i + 1); // Índice da linha
        for (int j = 0; j < coluna; j++){
            if (matriz[i][j] == MINA){ // Verifica se é uma mina
                printf("%5d ", MINA);
            }else{
                printf("%5d ", matriz[i][j]); // Valor na posição (i, j)
            }
        }
        printf("\n");
    }
}

// Função para inicializar o campo com 'x'.
void iniciaCampo(char** matCampo, int linha, int coluna){
    for (int i = 0; i < linha; i++){
        for (int j = 0; j < coluna; j++){
            matCampo[i][j] = 'x'; // Preenche todas as posições com 'x'
        }
    }
}

// Função para verificar se uma coordenada já foi escolhida.
int repetidaXY(char** campoMinado, int x, int y){
    if (campoMinado[x][y] != 'x'){ // Se não for 'x', já foi escolhida
        printf("\nEssa coordenada já foi escolhida.\nPor favor, escolha outra.\n");
        return 1; // Coordenada repetida
    }
    return 0; // Coordenada nova
}

// Função para verificar se as coordenadas são válidas.
int coordenadasValidas(int x, int y, int linha, int coluna){
	
    // Verifica se a coordenada está dentro dos limites da matriz
    return (x >= 0 && x < linha && y >= 0 && y < coluna);
}

// Função para gerar minas aleatórias no campo e atualizar os números adjacentes.
void geraMina(int** campoMinado, int linha, int coluna, int quantMina){
    
	srand(time(NULL)); // Inicializa o gerador de números aleatórios
    int minasCont = 0; // Conta o número de minas geradas

    // Inicializa o campo com 0
    for (int i = 0; i < linha; i++){
        for (int j = 0; j < coluna; j++){
            campoMinado[i][j] = 0;
        }
    }

    // Gera minas aleatórias até atingir a quantidade necessária.
    while (minasCont < quantMina){
        int x = rand() % linha;
        int y = rand() % coluna;

        if (campoMinado[x][y] != MINA){ // Verifica se não há mina na posição
            campoMinado[x][y] = MINA; // Insere uma mina
            minasCont++;

            // Atualiza os números ao redor da mina
            for (int i = x - 1; i <= x + 1; i++){
                for (int j = y - 1; j <= y + 1; j++){
                    if ((i == x && j == y) || !coordenadasValidas(i, j, linha, coluna) || campoMinado[i][j] == MINA){
                        continue; // Ignora a posição da mina e coordenadas inválidas
                    }
                    campoMinado[i][j]++; // Incrementa o número adjacente
                }
            }
        }
    }
}

// Função de preenchimento para revelar células vazias.
void floodFill(int** campoMinado, char** campoM2, int linha, int coluna, int x, int y){
    if (!coordenadasValidas(x, y, linha, coluna) || campoM2[x][y] != 'x') {
        return; // Retorna se a posição for inválida ou já revelada
    }

    campoM2[x][y] = campoMinado[x][y] + '0'; // Revela o valor

    if (campoMinado[x][y] == 0) { // Se a célula for 0, continua a revelar
        floodFill(campoMinado, campoM2, linha, coluna, x - 1, y);
        floodFill(campoMinado, campoM2, linha, coluna, x + 1, y);
        floodFill(campoMinado, campoM2, linha, coluna, x, y - 1);
        floodFill(campoMinado, campoM2, linha, coluna, x, y + 1);
    }
}

// Função para processar uma jogada.
int jogada(int** campoMinado, char** campoM2, int linha, int coluna, int x, int y){
	
    if (campoMinado[x][y] == MINA) { // Jogador acertou uma mina
        printf("\nGAME OVER. VOCÊ PERDEU :/\n");
        imprimirMatInt(campoMinado, linha, coluna); // Mostra o campo completo
        return 1; // Jogo termina
    }else{
        if(campoMinado[x][y] == 0){ // Revela células adjacentes se for 0
           floodFill(campoMinado, campoM2, linha, coluna, x, y);
        }else{
            campoM2[x][y] = campoMinado[x][y] + '0';// Revela o valor da célula
        }
    }
    return 0; // Continua o jogo
}

// Função para verificar se o jogador venceu.
int verificaJogada(int** campoMinado, char** campoM2, int linha, int coluna){
	
    for (int i = 0; i < linha; i++){
        for (int j = 0; j < coluna; j++){
            if (campoMinado[i][j] != MINA && campoM2[i][j] == 'x'){
                return 0; // Ainda há células não reveladas
            }
        }
    }
    return 1; // Todas as células seguras foram reveladas
}

// Função para liberar a memória de uma matriz alocada
void liberarMatriz(void* matriz, int linha){
    void** mat = (void**) matriz;
    for (int i = 0; i < linha; i++){
        free(mat[i]); // Libera cada linha
    }
    free(mat); // Libera o vetor de ponteiros
}
