#include <stdio.h>

int main (void){

    int x, N, entradas_seq; //número fornecido pelo site, quant de canais, 2 números iniciais de cada sequencia de canal
    
    scanf("%d %d", &x, &N);

    int melhor_canal = -1;
    int melhor_min = -1;
    int menor_dist = -1;
    int melhor_num = -1;

    for (int i = 1; i <= N; i++){

        int n1, n2; // números iniciais do canal
        scanf("%d %d", &n1, &n2);

        int num_min_recente = n2; //numero do min mais próximo do atual
        int num_min_antigo = n1; //numero de 2 min atrás

        for (int min = 1; min <= 90; min++){
            int num_min_atual; //numero do minuto que está sendo analisado

            if (min == 1){
                num_min_atual = n1;
            }
            else if (min == 2){
                num_min_atual = n2;
            }

            else{
                num_min_atual = num_min_antigo + num_min_recente; //atualizando o min atual
                
                //atualizado os minutos anteriores
                num_min_antigo = num_min_recente;
                num_min_recente = num_min_atual;
            }

            int dist = x - num_min_atual; //distância entre a senha de xupenio e o numero do minuto atual
            if (dist < 0) dist = -dist; //o que importa é o módulo

            if (melhor_canal == -1 || dist < menor_dist){ //quando encontra uma distância menor, atualiza
                
                menor_dist = dist;
                melhor_canal = i;
                melhor_min = min;
                melhor_num = num_min_atual;
            }

            else if (dist == menor_dist) { //em caso de empate de distâncias em canais diferentes

                if (i > melhor_canal) { //vence o canal com maior índice

                    menor_dist = dist;
                    melhor_canal = i;
                    melhor_min = min;
                    melhor_num = num_min_atual;
                }
                else if (i == melhor_canal && num_min_atual < melhor_num) { //mesmo canal, menor número vence
                    melhor_num = num_min_atual;
                    melhor_min = min;
                }
            }
    }
}

//calculo da soma dos algarismos
int soma = 0;
int numero_vencedor = melhor_num;

while (numero_vencedor > 0){
    soma += (numero_vencedor % 10);
    numero_vencedor = numero_vencedor / 10;
}

printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d", melhor_canal, melhor_min);
    
if (soma > 10) {
    printf(" e com o VIP garantido!!!\n");

} else {
    printf(", mas o ingresso VIP não vai rolar :(\n");
}

return 0;
}
