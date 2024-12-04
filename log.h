#include <stdio.h>
#ifndef LOG_H
#define LOG_H


//Estrutura para gerenciar o sistema de log.
typedef struct {
    FILE *arquivo;
} Log;

   Log* iniciar_log(const char *nome_arquivo);
/* Inicia o log, criando o arquivo e registrando a data e hora do início do jogo.
   Exemplo de uso:
   Log *log = iniciar_log("log.txt");
   if (log == NULL) {
       printf("Erro ao iniciar o log.\n");
    }  
*/

   void registrar_jogada(Log *log, char **matriz, int linhas, int colunas, int x, int y);
/* Registra o estado da matriz e a coordenada escolhida pelo jogador.
   Exemplo de uso:
   registrar_jogada(log, matriz, 10, 10, 3, 4);
*/

   void finalizar_log(Log *log);
/* Finaliza o log, fechando o arquivo e liberando memória. 
   Exemplo de uso:
   finalizar_log(log);
*/
#endif
