Campo Minado com Flood Fill

Como executar o jogo

1. Abra o terminal e acesse o diretório onde estão os arquivos do projeto.
2. Execute o seguinte comando para compilar o programa:

   ```bash
   gcc -g CampoMinado_com_FLOODFILL.c matriz.c log.c -o CampoMinado.exe
   ```

3. Após a compilação, execute o jogo com o comando:

   ```bash
   .\CampoMinado.exe
   ```
Como jogar

1. Ao iniciar o jogo, escolha um dos três níveis de dificuldade disponíveis:
   - Fácil: matriz de 10 × 10, com 15 minas.
   - Médio: matriz de 20 × 20, com 60 minas.
   - Difícil: matriz de 30 × 30, com 135 minas.
2. Para selecionar uma posição no campo, digite as coordenadas no formato solicitado pelo programa, separando os valores por vírgula. Por exemplo: "3,5".
3. O objetivo é revelar todas as posições que não contêm minas.
4. O jogador perde ao selecionar uma posição que contém uma mina, representada pelo valor "-1'.
5. O jogador vence ao revelar todas as posições livres de minas.

Atenção: digite as coordenadas respeitando os limites da matriz do nível escolhido. No nível fácil, por exemplo, as linhas e colunas variam de 1 a 10.

Arquivos do projeto

- `CampoMinado_com_FLOODFILL.c`: contém a função principal e a lógica do jogo.
- `matriz.c` e `matriz.h`: contêm as funções relacionadas à criação, manipulação e exibição das matrizes.
- `log.c` e `log.h`: contêm as funções responsáveis pelo registro das jogadas em arquivo de log.
