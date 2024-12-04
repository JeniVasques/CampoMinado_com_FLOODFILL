#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MINA -1

   char** criaMatrizC(int linha, int coluna);
/* Função para criar e alocar dinamicamente uma matriz de caracteres.
   Exemplo de uso:
   char **matriz = criaMatrizC(10, 10);
*/ 

   int** criaMatrizInt(int linha, int coluna);
/* Função para criar e alocar dinamicamente uma matriz de inteiros.
   Exemplo de uso:
   int **matriz = criaMatrizInt(10, 10);
*/

   void imprimirMatC(char** matrizC, int linha, int coluna);
/* Função para imprimir a matriz de caracteres.
   Exemplo de uso:
   imprimirMatC(matriz, 10, 10);
*/

   void imprimirMatInt(int** matriz, int linha, int coluna);
/* Função para imprimir a matriz de inteiros. 
   Exemplo de uso:
   imprimirMatInt(matriz, 10, 10);
*/

   void iniciaCampo(char** matCampo, int linha, int coluna);
/* Função que inicializa o campo minado preenchendo com 'x'.
   Exemplo de uso:
   iniciaCampo(matriz, 10, 10);
*/

   int repetidaXY(char** campoMinado, int x, int y);
/* Função para verificar se a jogada é repetida.
   Exemplo de uso:
   int repetida = repetidaXY(matriz, 2, 3);
*/

   int coordenadasValidas(int x, int y, int linha, int coluna);
/* Função para verificar se as coordenadas são válidas.
   Exemplo de uso:
   int valido = coordenadasValidas(2, 3, 10, 10);
*/

   void geraMina(int** campoMinado, int linha, int coluna, int quantMina);
/* Função que gera minas aleatoriamente no campo e atualiza os números ao redor.
   Exemplo de uso:
   geraMina(campo, 10, 10, 20);
*/

  void floodfill(int** campoMinado, char**campoM2, int linha, int coluna, int x, int y);
/* Função que revela minas seguras no campo minado usando o algoritmo flood-fill. 
   Exemplo de uso:
   floodfill(campoInt, campoChar, 10, 10, 2, 3);
*/

  int jogada(int** campoMinado, char** campoM2, int linha, int coluna, int x, int y);
/* Função para processar a jogada e verificar se o jogador acertou uma mina.
   Exemplo de uso:
   int resultado = jogada(campoInt, campoChar, 10, 10, 2, 3);
*/

   int verificaJogada(int** campoMinado, char** campoM2, int linha, int coluna);
/* Função para verificar se todas as células seguras foram reveladas.
   Exemplo de uso:
   int venceu = verificaJogada(campoInt, campoChar, 10, 10);
*/

   void liberarMatriz(void* matriz, int linha);
/* Função para liberar a memória alocada para uma matriz.
   Exemplo de uso:
   liberarMatriz(matriz, 10);
*/
