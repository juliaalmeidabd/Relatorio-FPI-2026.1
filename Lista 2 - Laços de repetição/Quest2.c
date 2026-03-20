#include <stdio.h>

int main (void){

    int N, K, P;
    int primeiro_achado = -1; //iniciando com valor impossível
    int Q = 0; //quantidade total

    scanf("%d %d %d", &N, &K, &P);

    for (int i = N; i < K; i++) {
        
        int numero = i;
        int fatores_impares = 0; //contador de fatores
        int valido = 1; //só pode aparecer uma vez

        
        if (numero > 0) {
            while (numero % 2 == 0) {
                numero = numero / 2; //o contador de fatores continua zerado, pois 2 é par
            }
        }

        for (int j = 3; (j * j <= numero) && (valido == 1); j += 2) { //testar os próximos números ímpares
            if (numero % j == 0) {
                fatores_impares += 1;
                numero = numero / j;

                if (numero % j == 0) { //se ainda for divisível por f, é inválido
                    valido = 0; //encerra o for
                }
            }
        }

         if (numero > 1 && valido == 1) {
            fatores_impares += 1;
        }

        if (valido == 1 && fatores_impares == P) {
            if (primeiro_achado == -1) {
                primeiro_achado = i;

            } else {
                Q++; //os que vierem depois do primeiro encontrado
            }
        }
    }

    if (primeiro_achado != -1) {
        printf("%d %d\n", primeiro_achado, Q);

    } else {
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");

    }
    return 0;
}
