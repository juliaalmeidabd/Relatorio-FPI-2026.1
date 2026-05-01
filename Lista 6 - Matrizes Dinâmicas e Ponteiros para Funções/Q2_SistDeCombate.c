#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

int** alocar(int M, int N){
    int** matriz = (int**) malloc(M * sizeof(int*));

    for (int i = 0; i < M; i++){
        matriz[i] = (int*) malloc(N * sizeof(int));
    }
    return matriz;
}

void liberarMatriz(int** matriz, int M){ //libera memoria da matriz
    for(int i = 0; i < M; i++){
        free(matriz[i]);
    }
    free(matriz);
}

void imprimirMatriz (int** matriz, int M, int N){
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int** copiaMatriz(int **matriz, int M, int N){ //pra nao modificar a original
    int **matrizCopia = alocar(M, N);

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            matrizCopia[i][j] = matriz[i][j];
        }
    }

    return matrizCopia;
}

//mapa de camadas (0 = fora, 1 = camada 1, 2 = camada 2)
int** montarCamadas(int M, int N, int x, int y){
    int **camadas = alocar(M, N);

    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            camadas[i][j] = 0;

    //camada 1: centro e a cruz
    int posLinha[5] = {0, -1, 1, 0, 0};
    int posColuna[5] = {0, 0, 0, -1, 1};

    for(int k = 0; k < 5; k++){
        int nl = x + posLinha[k];
        int nc = y + posColuna[k];
        if(nl >= 0 && nl < M && nc >= 0 && nc < N)
            camadas[nl][nc] = 1;
    }

    //camada 2: vizinhos em 8 direcoes de cada celula da camada 1, menos as que ja foram marcadas
    int dl[] = {-1,-1,-1,0,0,1,1,1};
    int dc[] = {-1,0,1,-1,1,-1,0,1};

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            if(camadas[i][j] == 1){
                for(int k = 0; k < 8; k++){
                    int nl = i + dl[k];
                    int nc = j + dc[k];

                    if(nl >= 0 && nl < M && nc >= 0 && nc < N)
                        if(camadas[nl][nc] == 0)
                            camadas[nl][nc] = 2;
                }
            }
        }
    }
    return camadas;
}

//funcao para o ataque de explosao
void explosao(int** matriz, int M, int N, int x, int y){

    int **matrizCopia = copiaMatriz(matriz, M, N); //gera a copia da matriz
    int **camadas = montarCamadas(M, N, x, y);

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            int dano = 0;
            if(camadas[i][j] == 1) dano = 50; //camada 1 recebe 50 de dano
            else if(camadas[i][j] == 2) dano = 25; //camada 2 recebe 25 de dano

            if(dano > 0){
                matrizCopia[i][j] -= dano;
                if(matrizCopia[i][j] < 0) matrizCopia[i][j] = 0; //nunca negativo
            }
        }
    }

    //print da matriz pos ataque de explosao
    printf("Estado do mapa após usar a Explosão Arcana:\n");
    imprimirMatriz(matrizCopia, M, N);

    liberarMatriz(camadas, M);
    liberarMatriz(matrizCopia, M); //libera copia da explosao
}

int temVivos(int** m, int M, int N, int **camadas){ //funcao para saber se ainda tem algum jogador vivo na area
    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            if(camadas[i][j] > 0 && m[i][j] > 0)
                return 1;
    return 0;
}

void nuvemVenenosa(int** matriz, int M, int N, int x, int y){

    int **matrizCopia = copiaMatriz(matriz, M, N); //gera a copia da matriz
    int **camadas = montarCamadas(M, N, x, y);

    printf("Estado do mapa, por turno, após usar a Nuvem Venenosa:\n");

    int turno = 1;

    while(turno <= 3){ //no maximo 3 turnos

        int **proxima = copiaMatriz(matrizCopia, M, N);

        for(int i = 0; i < M; i++){
            for(int j = 0; j < N; j++){

                if(camadas[i][j] != 0){; //so afeta celulas da area de efeito

                int novaLinha = i;
                int novaColuna = j;
                int vizinhos = 0;

                for(int a = -1; a <= 1; a++){
                    for(int b = -1; b <= 1; b++){

                        if(a != 0 || b != 0){ //ignora a propria celula

                            int linhaVizinho = novaLinha + a;
                            int colunaVizinho = novaColuna + b;

                            if(linhaVizinho >= 0 && linhaVizinho < M && colunaVizinho >= 0 && colunaVizinho < N){

                                if(matrizCopia[linhaVizinho][colunaVizinho] > 0)
                                    vizinhos++;
                            }
                        }
                    }
                }

                int dano = 5 + (8 * vizinhos);

                proxima[novaLinha][novaColuna] -= dano;

                if(proxima[novaLinha][novaColuna] < 0)
                    proxima[novaLinha][novaColuna] = 0;
            }
        }
    }

        imprimirMatriz(proxima, M, N);
        printf("\n");

        if(temVivos(proxima, M, N, camadas) == 0){
            liberarMatriz(matrizCopia, M);
            liberarMatriz(proxima, M);
            liberarMatriz(camadas, M);
            return;
        }

        liberarMatriz(matrizCopia, M); //libera matriz antiga do turno

        matrizCopia = copiaMatriz(proxima, M, N);

        liberarMatriz(proxima, M);

        turno++;
    }

    liberarMatriz(matrizCopia, M);
    liberarMatriz(camadas, M);
}

int main(){

    int M, N;
    int** matriz;
    int x, y;
    char tipo_explosao[15];

    scanf("%d %d", &M, &N);

    matriz = alocar(M, N);

    for (int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            scanf("%d", &matriz[i][j]);
        }
    }

    scanf("%d %d", &x, &y);
    scanf("%s", tipo_explosao);

    printf("Estado inicial do mapa:\n");
    imprimirMatriz(matriz, M, N);
    printf("\n");

    void (*ataque)(int**, int, int, int, int) = NULL; //ponteiro para funcao de ataque
    if (strcmp(tipo_explosao, "EXPLOSAO_ARCANA") == 0){
        ataque = explosao;
    }
    else{
        ataque = nuvemVenenosa;
    }

    ataque(matriz, M, N, x, y); //chama o ataque selecionado via ponteiro

    liberarMatriz(matriz, M); //libera matriz principal

    return 0;
}
