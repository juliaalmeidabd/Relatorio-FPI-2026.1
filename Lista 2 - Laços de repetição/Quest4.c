#include <stdio.h>

int main(void){

    int q; //quantidade de instruções
    int L = 0; //linha
    int col = 0; //coluna 
    char C; //direção
    int x; //quantidade de passos
    int primeiro_mov = 1; //controla se é o primeiro movimento horizontal
    int valido = 1; //se for valida

    scanf("%d", &q); //recebendo a entrada

    for (int i = 1; i <= q; i++){

        scanf("%d %c", &x, &C); 

        if (valido == 1){

            if ((C == 'E') && ((col - x) < 0)){ //quando ultrapassar o limite para esquerda
                printf("Informacao invalida");
                return 0; //encerra a execução
            }

            else{

                if (C == 'D'){ //quando o comando for D

                    int espacos;

                    if (primeiro_mov == 1)
                        espacos = col;
                    else //nos movimentos seguintes
                        espacos = col - 1;

                    if (espacos < 0) espacos = 0;

                    for (int a = 0; a < espacos; a++){
                        printf(" "); //espaços antes do caminho
                    }

                    int pontos;

                    if (primeiro_mov == 1)
                        pontos = x; //no primeiro movimento imprime x pontos
                    else
                        pontos = x + 1; //nos movimentos seguintes

                    for (int b = 0; b < pontos; b++){
                        printf("."); //imprimindo os pontos do caminho
                    }

                    printf("\n");

                    col += x; //atualiza a posição na coluna
                    primeiro_mov = 0; //atualiza o movimento
                }
                
                else if (C == 'E'){ //quando o comando for E

                    col -= x; //pra esquerda

                    for (int j = 0; j < col-1; j++){
                        printf(" "); //espaços até o ponto atual
                    }

                    for (int k = 0; k <= x; k++){
                        printf(".");
                    }

                    printf("\n");

                    primeiro_mov = 0;
                }

                else if (C == 'B'){ //quando o comando for B

                    int linhas;

                    if (i == q) //quando o B for o último comando
                        linhas = x;
                    else
                        linhas = x - 1;

                    for(int t = 0; t < linhas; t++){

                        for (int w = 0; w < col-1; w++){
                            printf(" "); //espaços até a coluna atual
                        }

                        printf(".\n"); //pontos pra baixo
                    }

                    primeiro_mov = 0;
                }
            }
        }
    }

    return 0;
}
