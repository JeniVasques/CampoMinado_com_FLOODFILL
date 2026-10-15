#include "matriz.h"
#include "log.h"

int main(){
    int linha, coluna, quantMinas, restoMinas, x, y, nivel;
    int perdeu = 0;
    int** campoMinado;
    char** campoM2;
   
    //Inicializa o log para registrar as jogadas
    Log* log = iniciar_log("log.txt");
    if (log == NULL){
        printf("Erro ao iniciar o log.\n");
        return 1;
    }

	
	/*Aqui dentro do while escolhe o nivel de dificuldade e verifica se ele eh valido ou nao, 
	se no for ele imprime uma mensagem que manda a pessoa escolher de novo.
	*/
    while(1){
    	printf("Digite o numero do nivel de dificuldade que voce deseja:\n");
    	printf("\n");
    	printf("1 = Facil\n");
		printf("2 = Medio\n");
		printf("3 = Dificil\n");
		printf("\n");
    	scanf("%d", &nivel);
    	printf("ATENCAO: As coordenadas devem ser digitadas no formato (x,y)\n");
		printf("Exemplo: 1,2\n");
    	
    	if(nivel == 1){ 
    		linha = coluna = 10;
    		quantMinas = 15;
    		break;
		}else if(nivel == 2){ 
			linha = coluna = 20;
			quantMinas = 60;
			break;
		}else if(nivel == 3){ 
			linha = coluna = 30;
			quantMinas = 135;
			break;
		}else{ 
			printf("Nivel de dificuldade invalido. Por Favor, tente novamente.\n");
		}
	}
	
	
	//Cria a matriz de inteiro e de char.
	campoMinado = criaMatrizInt(linha, coluna);
	if(campoMinado == NULL){
		printf("Erro ao alocar memoria para Campo Minado (campoMinado).\n");
		finalizar_log(log);
		return 1;
	}
	
	campoM2 = criaMatrizC(linha, coluna);
	if(campoM2 == NULL){
		printf("Erro ao alocar memoria para Campo Minado (campoM2).\n");
		finalizar_log(log);
		return 1;
	}
	
	//inicializa o campo minado com 'x'
	iniciaCampo(campoM2, linha, coluna); 
	
	// gera as minas no campo minado e atualiza os numeros proximos
	geraMina(campoMinado, linha, coluna, quantMinas);
	
	// Quantidade de espacos sem mina que o jogador ainda precisa descobrir
	restoMinas = linha * coluna - quantMinas;
	
	/*Dentro desse while acontece o processamento de cada jogada, a cada interacao do jogador solicitado uma coordenada e
	e se ela for valida, o loop verifica se foi revelado uma mina ou nao. Caso nao for revelado o contador "restoMinas" decrementado 
	e assim o loop vai verificando cada jogada ate que o jogador acerte uma mina ou ganhe e assim exibindo uma mensagem de vitria. 
	*/
	while(!perdeu && restoMinas > 0){
		
		imprimirMatC(campoM2, linha, coluna); // Exibe o campo visivel para o jogador
		
		printf("\n");
		printf("Digite as coordendas (x,y): \n");
		scanf("%d,%d", &x, &y);
		
		// ajusta as coordenadas para os indices da matriz
		x --;
		y --;
		
		// Verifica se a coordenada eh valida
		if(!coordenadasValidas(x, y, linha, coluna)){
		printf("\n");
		printf("Coordenada invalida.\n");
		printf("Por favor, digite outra coordenada.\n");
		registrar_jogada(log, campoM2, linha, coluna, x, y); // Registra a tentativa invalida no log
		continue;
	}
		
		registrar_jogada(log, campoM2, linha, coluna, x, y); // Registra a jogada no log
		
		// Verifica se a coordenada j foi escolhida anteriormente
		if(repetidaXY(campoM2, x, y)){
			continue;
		}
    	
    	// processa a jogada e verifica se o jogador perdeu
  		perdeu = jogada(campoMinado, campoM2, linha, coluna, x, y);
  		
  		
	
		// se no perdeu e a coordenada escolhida no contm mina ento decrementa o nmero de posies restantes
		if(!perdeu && campoMinado[x][y] != MINA){
			restoMinas--;
		}
		
		 // Verifica se o jogador revelou todas as celulas seguras
		if(verificaJogada(campoMinado, campoM2, linha, coluna)){
			printf("\n");
			printf("!!PARABENS!!. VOCE EH FERA!:) \n");
  			imprimirMatInt(campoMinado, linha, coluna); // Mostra o campo minado completo
  			break;
		}
  	}
  	
  	
	finalizar_log(log); // Finaliza o registro de jogadas no log
	
	//libera a memoria das matriz que foram alocadas dinamicamente
	liberarMatriz((void**)campoMinado, linha);
    liberarMatriz((void**)campoM2, linha);
    
    return 0;
}
