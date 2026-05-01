#include <stdio.h>
#include <stdlib.h>

int** alocar(int N, int M){ //funcao de alocacao
    int **matriz = (int**) malloc(N * sizeof(int*));

    for (int i = 0; i < N; i++){
        matriz[i] = (int*) malloc(M * sizeof(int));
    }
    return matriz;
}

void liberarMatriz(int **matriz, int N){ //funcao de liberacao de memoria
    for(int i = 0; i < N; i++){
        free(matriz[i]);
    }
    free(matriz);
}

void imprimirMatriz(int **matriz, int N, int M){ //funcao p imprimir a matriz
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

//funcoes dos filtros
int calibracao(int valor){
    return valor + 5;
}

int saturacao(int valor){
    if (valor >= 80){
        return 80;
    }
    else{
        return valor;
    }
}

int amplificador(int valor){
    return valor * 2;
}

//funcao pra aplicar o pipeline, a unica que modifica a matriz
void modificar(int** matriz, int N, int M, int (*pipeline[])(int), int k){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){

            for(int f = 0; f < k; f++){
                matriz[i][j] = pipeline[f](matriz[i][j]); //aplica cada filtro em sequencia
            }
        }
    }
}

int main(){

    int N, M;
    scanf("%d %d", &N, &M);

    int **matriz = alocar(N, M); //aloca a matriz

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            scanf("%d", &matriz[i][j]);
        }
    }

    //vetor de ponteiros para funcao
    int (*filtros[3])(int) = {calibracao, saturacao, amplificador}; //filtros disponiveis

    int comando;

    while(scanf("%d", &comando) && comando != 0){ //so para quando a entrada for 0

        int (**pipeline)(int) = malloc(100 * sizeof(int (*)(int))); //pipeline de filtros que vai aplicar
        int k = 0;

        if(comando == 4){ //se for pipeline
            scanf("%d", &k);

            for(int i = 0; i < k; i++){
                int id;
                
                scanf("%d", &id);
                pipeline[i] = filtros[id - 1]; //monta o pipeline com os filtros escolhidos
            }

        } else {
            pipeline[0] = filtros[comando - 1]; //pipeline de 1 filtro
            k = 1;
        }

        modificar(matriz, N, M, pipeline, k); //atualiza a matriz
        
        free(pipeline);
    }

    //sensor critico
    int maior = matriz[0][0];
    int linhaMax = 0, colunaMax = 0;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(matriz[i][j] > maior){
                maior = matriz[i][j];
                linhaMax = i;
                colunaMax = j;
            }
        }
    }

    printf("Matriz processada:\n");
    imprimirMatriz(matriz, N, M);
    printf("\n");
    printf("Sensor critico: %d\n", maior);
    printf("Posicao: (%d,%d)\n", linhaMax, colunaMax);

    liberarMatriz(matriz, N);

    return 0;
}
