#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Função para iniciar o log, criando o arquivo e registrando a data e hora do início do jogo.
Log* iniciar_log(const char *nome_arquivo) {
    
	Log *log = malloc(sizeof(Log));// Aloca memória para a estrutura de Log
    if (log == NULL){
        return NULL;
    }

    log->arquivo = fopen(nome_arquivo, "w"); // Abre o arquivo para escrita ('w' - cria um novo arquivo ou sobrescreve se já existir)
    if (log->arquivo == NULL) {
        free(log);
        return NULL;
    }
	
	// Obtém o tempo atual
    time_t agora = time(NULL);
    struct tm *tempo_info = localtime(&agora);
    char data_formatada[20];
    strftime(data_formatada, sizeof(data_formatada), "%Y-%m-%d %H:%M:%S", tempo_info); // Formata a data e hora no formato "YYYY-MM-DD HH:MM:SS"

    fprintf(log->arquivo, "Início do jogo: %s\n", data_formatada);// Registra no arquivo a data e hora do início do jogo
    return log;
}

//Função para registrar a jogada, incluindo a coordenada escolhida e o estado da matriz.
void registrar_jogada(Log *log, char **matriz, int linhas, int colunas, int x, int y){
    
    // Verifica se o arquivo de log está aberto antes de registrar
	if (log->arquivo == NULL){
        return;
    }

    // Registra as coordenadas escolhidas pelo jogador (aumento de 1 para formatar de forma legível)
    fprintf(log->arquivo, "Escolheu as coordenadas: (%d, %d):\n", x + 1, y + 1);
    
    // Imprime a matriz no arquivo
    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            fprintf(log->arquivo, "%c ", matriz[i][j]);
        }
        fprintf(log->arquivo, "\n");
    }

 
    fprintf(log->arquivo, "\n");
}

//Função para finalizar o log, fechando o arquivo e liberando a memória.
void finalizar_log(Log *log){
	
	// Verifica se o arquivo de log está aberto
    if (log->arquivo != NULL){
        fclose(log->arquivo); // Fecha o arquivo
    }
    free(log);// Libera a memória alocada para a estrutura de log
}

