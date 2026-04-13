#include <stdio.h>
#include <stdlib.h>

int main() {
    int *lugares = NULL; //criando ponteiro sem apontar para nenhum endereco especifico
    int numero;
    int contador = 0;

    while (scanf("%d", &numero) == 1) { //quando le um numero, retorna 1
        //realloc tenta aumentar o bloco de memoria atual
        //se não tiver espaco onde ele esta, ele move tudo para um novo lugar sozinho
        int *novos_lugares = realloc(lugares, (contador + 1) * sizeof(int));

        if (novos_lugares == NULL) { //verifica pra evitar erros caso a memoria acabe, boa pratica
            free(lugares);
            return 1;
        }

        //agora o ponteiro lugares vai apontar para o novo endereco maior
        lugares = novos_lugares;
        lugares[contador] = numero; //adiciona o numero recebido na ultima posicao disponivel
        contador++; //atualiza o contador
    }

    printf("Mais um bom dia de trabalho!\n"); //print inicial

    //saida dos numeros impares
    for (int i = 0; i < contador; i++) {
        if (lugares[i] % 2 != 0) {
            printf("%d\n", lugares[i]);
        }
    }

    //saida dos numeros pares
    for (int i = 0; i < contador; i++) {
        if (lugares[i] % 2 == 0) {
            printf("%d\n", lugares[i]);
        }
    }

    printf("Vou visitar esses lugares de novo... algum dia.\n"); //print final

    //liberando o ponteiro lugares
    if (lugares != NULL) {
        free(lugares);
    }

    return 0;
}
