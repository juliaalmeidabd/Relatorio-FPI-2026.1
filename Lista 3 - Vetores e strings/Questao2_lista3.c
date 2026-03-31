#include <stdio.h>

int main() {
    int n, x, y;
    scanf("%d %d %d", &n, &x, &y);

    int compras[1001]; //quant de latas que cada cliente comprou

    //inicializando tudo como 0, pra ir adicionando dps
    for (int i = 1; i <= n; i++) {
        compras[i] = 0;
    }

    //clientes y (que compraram mais de 1 lata)
    for (int i = 0; i < y; i++) {
        int h, m, z; //hora, minutos, latas compradas

        scanf("%d:%d %d", &h, &m, &z);

        //calcula numero do cliente na fila
        int posicao_fila = ((h - 7) * 60 + m) / 3;

        compras[posicao_fila] = z;
    }

    //testando se e multiplo de x (se for, o cliente comprou 1 lata)
    for (int i = 1; i <= n; i++) {
        if (compras[i] == 0 && x > 0 && i % x == 0) { //se nao for cliente y, se x for diferente de 0 e se for multiplo de x
            compras[i] = 1;
        }
    }

    //soma das latas para achar o vencedor (quem comprou a 50*)
    int soma_latas = 0;
    int posicao_vencedor = -1; //ainda nao achou o vencedor

    for (int i = 1; i <= n; i++) {
        soma_latas += compras[i];

        if (posicao_vencedor == -1 && soma_latas >= 50) { //quando achar quem comprou a 50* lata
            posicao_vencedor = i;
        }
    }

    //saida final
    if (soma_latas < 50) { //se nao tiver vencedor
        int faltam = 50 - soma_latas;

        if (faltam == 1) {
            printf("Ainda nao foram vendidas latas suficientes. Falta 1 lata.\n");
        } else {
            printf("Ainda nao foram vendidas latas suficientes. Faltam %d latas.\n", faltam);
        }

    } else {
        int h = 7 + (posicao_vencedor * 3) / 60;
        int m = (posicao_vencedor * 3) % 60;

        if (compras[posicao_vencedor] > 1) { //plural
            printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d latas.\n",
                   posicao_vencedor, h, m, compras[posicao_vencedor]);
        } else { //singular
            printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d lata.\n",
                   posicao_vencedor, h, m, compras[posicao_vencedor]);
        }
    }

    return 0;
}
