#include "matriz.h"

// Função para criar e alocar dinamicamente uma matriz de caracteres (char).
char** criaMatrizC(int linha, int coluna){
	
    // Aloca espaco para as linhas
    char** matC = (char**) malloc(linha * sizeof(char*));
    if (matC == NULL){ 
        return NULL;
    }

    // Aloca espaco para as colunas de cada linha
    for (int i = 0; i < linha; i++){
        matC[i] = (char*) malloc(coluna * sizeof(char));
        if (matC[i] == NULL){
        
            liberarMatriz((void**)matC, i); 
            return NULL;
        }
    }
    return matC;
}

// Funcao para criar e alocar dinamicamente uma matriz de inteiros (int).
int** criaMatrizInt(int linha, int coluna){
    
	// Aloca espaco para as linhas
    int** matInt = (int**) malloc(linha * sizeof(int*));
    if (matInt == NULL){ 
        return NULL;
    }

    // Aloca espaco para as colunas de cada linha
    for (int i = 0; i < linha; i++){
        matInt[i] = (int*) malloc(coluna * sizeof(int));
        if (matInt[i] == NULL){ // Verifica falha na alocao de uma linha
            liberarMatriz((void**)matInt, i); // Libera as linhas j alocadas
            return NULL;
        }
    }
    return matInt;
}

// Funcao para imprimir a matriz de caracteres.
void imprimirMatC(char** matrizC, int linha, int coluna){
    printf("\n ");

    // Imprime os indices das colunas
    for (int j = 0; j < coluna; j++){
        printf("   %2d ", j + 1);
    }
    printf("\n");

    // Imprime a matriz de caracteres com os indices das linhas
    for (int i = 0; i < linha; i++){
        printf("\n%2d", i + 1); // indice da linha
        for (int j = 0; j < coluna; j++){
            printf("%5c ", matrizC[i][j]); // Caractere na posicao (i, j)
        }
        printf("\n");
    }
}

// Funcao para imprimir a matriz de inteiros.
void imprimirMatInt(int** matriz, int linha, int coluna){
    printf("\n ");

    // Imprime os indices das colunas
    for (int j = 0; j < coluna; j++){
        printf("   %2d ", j + 1);
    }
    printf("\n");

    // Imprime a matriz de inteiros com os indices das linhas
    for (int i = 0; i < linha; i++){
        printf("\n%2d", i + 1); // indice da linha
        for (int j = 0; j < coluna; j++){
            if (matriz[i][j] == MINA){ // Verifica se eh uma mina
                printf("%5d ", MINA);
            }else{
                printf("%5d ", matriz[i][j]); // Valor na posicao (i, j)
            }
        }
        printf("\n");
    }
}

// Funcao para inicializar o campo com 'x'.
void iniciaCampo(char** matCampo, int linha, int coluna){
    for (int i = 0; i < linha; i++){
        for (int j = 0; j < coluna; j++){
            matCampo[i][j] = 'x'; // Preenche todas as posicoes com 'x'
        }
    }
}

// Funcao para verificar se uma coordenada j foi escolhida.
int repetidaXY(char** campoMinado, int x, int y){
    if (campoMinado[x][y] != 'x'){ // Se no for 'x', j foi escolhida
        printf("\nEssa coordenada ja foi escolhida.\nPor favor, escolha outra.\n");
        return 1; // Coordenada repetida
    }
    return 0; // Coordenada nova
}

// Funcao para verificar se as coordenadas so vlidas.
int coordenadasValidas(int x, int y, int linha, int coluna){
	
    // Verifica se a coordenada esta dentro dos limites da matriz
    return (x >= 0 && x < linha && y >= 0 && y < coluna);
}

// Funcao para gerar minas aleatorias no campo e atualizar os numeros adjacentes.
void geraMina(int** campoMinado, int linha, int coluna, int quantMina){
    
	srand(time(NULL)); // Inicializa o gerador de numeros aleatorios
    int minasCont = 0; // Conta o numero de minas geradas

    // Inicializa o campo com 0
    for (int i = 0; i < linha; i++){
        for (int j = 0; j < coluna; j++){
            campoMinado[i][j] = 0;
        }
    }

    // Gera minas aleatorias ate atingir a quantidade necessaria.
    while (minasCont < quantMina){
        int x = rand() % linha;
        int y = rand() % coluna;

        if (campoMinado[x][y] != MINA){ // Verifica se nao ha mina na posicao
            campoMinado[x][y] = MINA; // Insere uma mina
            minasCont++;

            // Atualiza os numeros ao redor da mina
            for (int i = x - 1; i <= x + 1; i++){
                for (int j = y - 1; j <= y + 1; j++){
                    if ((i == x && j == y) || !coordenadasValidas(i, j, linha, coluna) || campoMinado[i][j] == MINA){
                        continue; // Ignora a posicao da mina e coordenadas invalidas
                    }
                    campoMinado[i][j]++; // Incrementa o numero adjacente
                }
            }
        }
    }
}

// Funcao de preenchimento para revelar celulas vazias.
void floodFill(int** campoMinado, char** campoM2, int linha, int coluna, int x, int y){
    if (!coordenadasValidas(x, y, linha, coluna) || campoM2[x][y] != 'x') {
        return; // Retorna se a posicao for invalida ou ja revelada
    }

    campoM2[x][y] = campoMinado[x][y] + '0'; // Revela o valor

    if (campoMinado[x][y] == 0) { // Se a celula for 0, continua a revelar
        floodFill(campoMinado, campoM2, linha, coluna, x - 1, y);
        floodFill(campoMinado, campoM2, linha, coluna, x + 1, y);
        floodFill(campoMinado, campoM2, linha, coluna, x, y - 1);
        floodFill(campoMinado, campoM2, linha, coluna, x, y + 1);
    }
}

// Funcao para processar uma jogada.
int jogada(int** campoMinado, char** campoM2, int linha, int coluna, int x, int y){
	
    if (campoMinado[x][y] == MINA) { // Jogador acertou uma mina
        printf("\nGAME OVER. VOCE PERDEU :/\n");
        imprimirMatInt(campoMinado, linha, coluna); // Mostra o campo completo
        return 1; // Jogo termina
    }else{
        if(campoMinado[x][y] == 0){ // Revela celulas adjacentes se for 0
           floodFill(campoMinado, campoM2, linha, coluna, x, y);
        }else{
            campoM2[x][y] = campoMinado[x][y] + '0';// Revela o valor da celula
        }
    }
    return 0; // Continua o jogo
}

// Funcao para verificar se o jogador venceu.
int verificaJogada(int** campoMinado, char** campoM2, int linha, int coluna){
	
    for (int i = 0; i < linha; i++){
        for (int j = 0; j < coluna; j++){
            if (campoMinado[i][j] != MINA && campoM2[i][j] == 'x'){
                return 0; // Ainda ha celulas nao reveladas
            }
        }
    }
    return 1; // Todas as celulas seguras foram reveladas
}

// Funcao para liberar a memoria de uma matriz alocada
void liberarMatriz(void* matriz, int linha){
    void** mat = (void**) matriz;
    for (int i = 0; i < linha; i++){
        free(mat[i]); // Libera cada linha
    }
    free(mat); // Libera o vetor de ponteiros
}
