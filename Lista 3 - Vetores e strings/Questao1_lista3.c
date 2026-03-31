#include <stdio.h>

#define MAX_N 100 //definindo o limite maximo

int main() {
    int T; //número de casos teste

    scanf("%d", &T);

    for (int caso = 0; caso < T; caso++) { //loop principal, epete todo o processo T vezes.
        
        int N; //tamanho da sequência
        scanf("%d", &N);
        
        //criando o array e preenchendo com os valores da entrada
        int vet[MAX_N];
        for (int i = 0; i < N; i++) {
            scanf("%d", &vet[i]);
        }

        int maior_seq = 0;    //tamanho da maior sequência encontrada (o recorde)
        int maior_inicio = 0; //índice de onde a maior sequência começou
        int atual_tam = 1;  //tamanho da sequência atual
        int atual_inicio = 0; //onde a sequência atual começou

        //comparando cada elemento com o proximo do vetor 
        for (int i = 0; i < N - 1; i++) { //laço vai até N-1 para não tentar acessar um vizinho que não existe
            
            //se o atual for maior que o próximo, a sequência é decrescente
            if (vet[i] > vet[i + 1]) {
                atual_tam++; //aumentamos o contador da sequência atual

            } else { //se for o fim da seq decrescente (se o numero seguinte for maior)
                if (atual_tam > 1 && atual_tam > maior_seq) { //verificamos se essa descida que acabou é maior que o recorde anterior
                    maior_seq = atual_tam; //novo recorde de tamanho
                    maior_inicio = atual_inicio; //salvamos onde ela começou
                }
                //resetando o contador para 1 e marcando novo início como o próximo número
                atual_tam = 1;
                atual_inicio = i + 1;
            }
        }

        //se a maior sequência termina exatamente no último número, o 'else' acima não é executado. Por isso, fazemos uma última comparação aqui.
        if (atual_tam > 1 && atual_tam > maior_seq) {
            maior_seq = atual_tam;
            maior_inicio = atual_inicio;
        }

        //saida dos resultados
        if (maior_seq > 1) {
            printf("%d\n", maior_seq);
            
                for (int k = 0; k < maior_seq; k++) {

                    printf("%d ", vet[maior_inicio + k]);
            }
            printf("\n");


        } else {
            printf("0\n");
        }
    }

    return 0;
}
