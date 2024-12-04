#include "matriz.h"

// Fun��o para criar e alocar dinamicamente uma matriz de caracteres (char).
char** criaMatrizC(int linha, int coluna){
	
    // Aloca espa�o para as linhas
    char** matC = (char**) malloc(linha * sizeof(char*));
    if (matC == NULL){ // Verifica falha na aloca��o
        return NULL;
    }

    // Aloca espa�o para as colunas de cada linha
    for (int i = 0; i < linha; i++){
        matC[i] = (char*) malloc(coluna * sizeof(char));
        if (matC[i] == NULL){ // Verifica falha na aloca��o de uma linha
        
            liberarMatriz((void**)matC, i); // Libera as linhas j� alocadas
            return NULL;
        }
    }
    return matC;
}

// Fun��o para criar e alocar dinamicamente uma matriz de inteiros (int).
int** criaMatrizInt(int linha, int coluna){
    
	// Aloca espa�o para as linhas
    int** matInt = (int**) malloc(linha * sizeof(int*));
    if (matInt == NULL){ // Verifica falha na aloca��o
        return NULL;
    }

    // Aloca espa�o para as colunas de cada linha
    for (int i = 0; i < linha; i++){
        matInt[i] = (int*) malloc(coluna * sizeof(int));
        if (matInt[i] == NULL){ // Verifica falha na aloca��o de uma linha
            liberarMatriz((void**)matInt, i); // Libera as linhas j� alocadas
            return NULL;
        }
    }
    return matInt;
}

// Fun��o para imprimir a matriz de caracteres.
void imprimirMatC(char** matrizC, int linha, int coluna){
    printf("\n ");

    // Imprime os �ndices das colunas
    for (int j = 0; j < coluna; j++){
        printf("   %2d ", j + 1);
    }
    printf("\n");

    // Imprime a matriz de caracteres com os �ndices das linhas
    for (int i = 0; i < linha; i++){
        printf("\n%2d", i + 1); // �ndice da linha
        for (int j = 0; j < coluna; j++){
            printf("%5c ", matrizC[i][j]); // Caractere na posi��o (i, j)
        }
        printf("\n");
    }
}

// Fun��o para imprimir a matriz de inteiros.
void imprimirMatInt(int** matriz, int linha, int coluna){
    printf("\n ");

    // Imprime os �ndices das colunas
    for (int j = 0; j < coluna; j++){
        printf("   %2d ", j + 1);
    }
    printf("\n");

    // Imprime a matriz de inteiros com os �ndices das linhas
    for (int i = 0; i < linha; i++){
        printf("\n%2d", i + 1); // �ndice da linha
        for (int j = 0; j < coluna; j++){
            if (matriz[i][j] == MINA){ // Verifica se � uma mina
                printf("%5d ", MINA);
            }else{
                printf("%5d ", matriz[i][j]); // Valor na posi��o (i, j)
            }
        }
        printf("\n");
    }
}

// Fun��o para inicializar o campo com 'x'.
void iniciaCampo(char** matCampo, int linha, int coluna){
    for (int i = 0; i < linha; i++){
        for (int j = 0; j < coluna; j++){
            matCampo[i][j] = 'x'; // Preenche todas as posi��es com 'x'
        }
    }
}

// Fun��o para verificar se uma coordenada j� foi escolhida.
int repetidaXY(char** campoMinado, int x, int y){
    if (campoMinado[x][y] != 'x'){ // Se n�o for 'x', j� foi escolhida
        printf("\nEssa coordenada j� foi escolhida.\nPor favor, escolha outra.\n");
        return 1; // Coordenada repetida
    }
    return 0; // Coordenada nova
}

// Fun��o para verificar se as coordenadas s�o v�lidas.
int coordenadasValidas(int x, int y, int linha, int coluna){
	
    // Verifica se a coordenada est� dentro dos limites da matriz
    return (x >= 0 && x < linha && y >= 0 && y < coluna);
}

// Fun��o para gerar minas aleat�rias no campo e atualizar os n�meros adjacentes.
void geraMina(int** campoMinado, int linha, int coluna, int quantMina){
    
	srand(time(NULL)); // Inicializa o gerador de n�meros aleat�rios
    int minasCont = 0; // Conta o n�mero de minas geradas

    // Inicializa o campo com 0
    for (int i = 0; i < linha; i++){
        for (int j = 0; j < coluna; j++){
            campoMinado[i][j] = 0;
        }
    }

    // Gera minas aleat�rias at� atingir a quantidade necess�ria.
    while (minasCont < quantMina){
        int x = rand() % linha;
        int y = rand() % coluna;

        if (campoMinado[x][y] != MINA){ // Verifica se n�o h� mina na posi��o
            campoMinado[x][y] = MINA; // Insere uma mina
            minasCont++;

            // Atualiza os n�meros ao redor da mina
            for (int i = x - 1; i <= x + 1; i++){
                for (int j = y - 1; j <= y + 1; j++){
                    if ((i == x && j == y) || !coordenadasValidas(i, j, linha, coluna) || campoMinado[i][j] == MINA){
                        continue; // Ignora a posi��o da mina e coordenadas inv�lidas
                    }
                    campoMinado[i][j]++; // Incrementa o n�mero adjacente
                }
            }
        }
    }
}

// Fun��o de preenchimento para revelar c�lulas vazias.
void floodFill(int** campoMinado, char** campoM2, int linha, int coluna, int x, int y){
    if (!coordenadasValidas(x, y, linha, coluna) || campoM2[x][y] != 'x') {
        return; // Retorna se a posi��o for inv�lida ou j� revelada
    }

    campoM2[x][y] = campoMinado[x][y] + '0'; // Revela o valor

    if (campoMinado[x][y] == 0) { // Se a c�lula for 0, continua a revelar
        floodFill(campoMinado, campoM2, linha, coluna, x - 1, y);
        floodFill(campoMinado, campoM2, linha, coluna, x + 1, y);
        floodFill(campoMinado, campoM2, linha, coluna, x, y - 1);
        floodFill(campoMinado, campoM2, linha, coluna, x, y + 1);
    }
}

// Fun��o para processar uma jogada.
int jogada(int** campoMinado, char** campoM2, int linha, int coluna, int x, int y){
	
    if (campoMinado[x][y] == MINA) { // Jogador acertou uma mina
        printf("\nGAME OVER. VOC� PERDEU :/\n");
        imprimirMatInt(campoMinado, linha, coluna); // Mostra o campo completo
        return 1; // Jogo termina
    }else{
        if(campoMinado[x][y] == 0){ // Revela c�lulas adjacentes se for 0
           floodFill(campoMinado, campoM2, linha, coluna, x, y);
        }else{
            campoM2[x][y] = campoMinado[x][y] + '0';// Revela o valor da c�lula
        }
    }
    return 0; // Continua o jogo
}

// Fun��o para verificar se o jogador venceu.
int verificaJogada(int** campoMinado, char** campoM2, int linha, int coluna){
	
    for (int i = 0; i < linha; i++){
        for (int j = 0; j < coluna; j++){
            if (campoMinado[i][j] != MINA && campoM2[i][j] == 'x'){
                return 0; // Ainda h� c�lulas n�o reveladas
            }
        }
    }
    return 1; // Todas as c�lulas seguras foram reveladas
}

// Fun��o para liberar a mem�ria de uma matriz alocada
void liberarMatriz(void* matriz, int linha){
    void** mat = (void**) matriz;
    for (int i = 0; i < linha; i++){
        free(mat[i]); // Libera cada linha
    }
    free(mat); // Libera o vetor de ponteiros
}
