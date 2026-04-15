#include <stdio.h>
#include <stdlib.h>

//funçao pra ver se ainda tem letras repetidas pra fundir
int tem_repetido(char *str, int tam){
    for(int i = 0; i < tam - 1; i++){
        if(str[i] == str[i + 1]){
            return 1;
        }
    }
    return 0;
}

//funçao para a fusao
int fusao(char *str, int tam){

    int w = 0;

    for(int i = 0; i < tam - 1; i++){

        if(str[w] == str[w + 1]){

            //regra do z com z vira a
            if(str[w] == 'z'){
                str[w] = 'a';
            } else {
                str[w] = str[w] + 1;
            }

            //desloca pra a esquerda removendo o caractere fundido
            for(int j = w + 1; j < tam - 1; j++){
                str[j] = str[j + 1];
            }

            tam--;

            //retrocede pra ver se forma nova fusao
            if(w > 0){
                w--;
                i--;
            }

        } else {
            w++;
        }
    }

    return tam;
}

int main(){

    int N;
    scanf("%d", &N);

    char *todas = NULL;
    int *inicio = malloc(N * sizeof(int));
    int *tamanho_str = malloc(N * sizeof(int));

    int total = 0;

    for(int i = 0; i < N; i++){

        char buffer[1000];
        scanf("%s", buffer);

        int j = 0;
        inicio[i] = total;

        while(buffer[j] != '\0'){

            char *temp = realloc(todas, (total + 1) * sizeof(char));

            if(temp == NULL){
                free(todas);
                return 1;
            }

            todas = temp;
            todas[total] = buffer[j];

            total++;
            j++;
        }

        tamanho_str[i] = j;
    }

    //mesclagem
    char *merged = NULL;
    int tamanho = 0;

    for(int pos = 0;; pos++){

        int adicionou = 0;

        for(int i = 0; i < N; i++){

            if(pos < tamanho_str[i]){

                char *temp = realloc(merged, (tamanho + 1) * sizeof(char));

                if(temp == NULL){
                    free(merged);
                    return 1;
                }

                merged = temp;
                merged[tamanho] = todas[inicio[i] + pos];

                tamanho++;
                adicionou = 1;
            }
        }

        if(!adicionou) break;
    }

    //print merged
    for(int i = 0; i < tamanho; i++){
        printf("%c", merged[i]);
    }
    printf("\n");

    int novo_tam = tamanho;

    while(tem_repetido(merged, novo_tam)){
        novo_tam = fusao(merged, novo_tam);
    }

    for(int i = 0; i < novo_tam; i++){
        printf("%c", merged[i]);
    }
    
    //limpeza
    free(todas);
    free(inicio);
    free(tamanho_str);
    free(merged);

    return 0;
}
