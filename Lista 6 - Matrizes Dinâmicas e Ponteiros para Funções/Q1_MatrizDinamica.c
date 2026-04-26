#include <stdio.h>
#include <stdlib.h>

//funçoes obrigatorias

int** alocarMatriz(int L, int C);
void lerMatriz(int **matriz, int L, int C);
void imprimirMatriz(int** matriz, int L, int C);
void liberarMem(int** matriz, int L, int C);
void aplicarOper(int** matriz, int L, int C, int (*func)(int));

//funcoes para as operacoes

int dobro(int x);
int quadrado(int x);
int valorAbsoluto(int x);

int main(){

    int L, C, op; //entradas da quant de linhas e colunas e a operacao escolhida
    int **matriz; //ponteiro pra ponteiro de int
    int (*operacao)(int); //ponteiro pra funcao

    scanf("%d %d", &L, &C); //recebe a as quant de linhas e colunas

    //alocacao
    matriz = alocarMatriz(L, C);

    //leitura dos elementos
    lerMatriz(matriz, L, C);

    //recebendo a operacao
    scanf("%d", &op);

    //escolha da operacao
    if (op == 1){
        operacao = dobro;
    }
    else if (op == 2){
        operacao = quadrado;
    }
    else if (op == 3){
        operacao = valorAbsoluto;
    }
    else {
        liberarMem(matriz, L, C);
        return 0;
    }

    //aplicando a operacao
    aplicarOper(matriz, L, C, operacao);

    //imprimindo o resultado
    imprimirMatriz(matriz, L, C);

    //libreando memoria
    liberarMem(matriz, L, C);
    return 0; //deu erro
}

//funcoes

int** alocarMatriz(int L, int C){
    int **matriz = (int**) malloc(L * sizeof(int*));

    for (int i = 0; i < L; i++){
        matriz[i] = (int*) malloc(C * sizeof(int));
    }
    return matriz;
}

void lerMatriz(int **matriz, int L, int C){
    for (int i = 0; i < L; i++){
        for (int j = 0; j < C; j++){
            scanf("%d", &matriz[i][j]);
        }
    }
}

void imprimirMatriz(int** matriz, int L, int C){
    for (int i = 0; i < L; i ++){
        for (int j = 0; j < C; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void liberarMem(int** matriz, int L, int C){
    for (int i = 0; i < L; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void aplicarOper(int** matriz, int L, int C, int (*func)(int)){
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            matriz[i][j] = func(matriz[i][j]);
        }
    }
}

//operacoes

int dobro(int x) {
    return 2 * x;
}

int quadrado(int x) {
    return x * x;
}

int valorAbsoluto(int x) {
    if (x < 0) return -x;
    return x;
}
