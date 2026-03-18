#include <stdio.h>

int main() {
    char entrada;

    if (scanf("%c", &entrada) != 1) return 0;

    int n = entrada - 'A' + 1; //quantidade de linhas da pirâmide

    for (int i = 0; i < n; i++) {
        char letra_linha = 'A' + i;
    

        for (int j = 0; j < (entrada - letra_linha); j++) { //pontos esquerda
            printf(".");
        }

        //sequência de letras até a letra da linha
        for (char sequencia_letras = 'A'; sequencia_letras <= letra_linha; sequencia_letras++) {
            printf("%c", sequencia_letras);
        }

        //continua a sequência, com as letras em ordem decrescente até a A
        for (char sequencia_letras = letra_linha - 1; sequencia_letras >= 'A'; sequencia_letras--) {
            printf("%c", sequencia_letras);
        }

        for (int j = 0; j < (entrada - letra_linha); j++) { //pontos direita
            printf(".");
        }

        printf("\n");
    }
    

    return 0;
}
