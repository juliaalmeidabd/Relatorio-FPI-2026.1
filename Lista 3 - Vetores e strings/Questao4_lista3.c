#include <stdio.h>

int main() {
    int R; //numero de casos de teste
    scanf("%d", &R);

    char Sf[100000]; //string gigante que vai unir todos os fios
    int tamanhoSf = 0; //controla quantos caracteres já existem em Sf

    //laço para processar cada fio
    for (int teste = 0; teste < R; teste++) {
        char S[100]; //string do fio atual
        int F;       //numero de flashes testados (clocks) do fio atual

        scanf("%s %d", S, &F);

        //descobrindo tamanho do fio
        int tamanhoS = 0;
        while (S[tamanhoS] != '\0') {
            tamanhoS++;
        }

        for (int flash = 0; flash < F; flash++) {
            int sempre_troca = 1; //o primeiro led sempre troca

            for (int pos = 0; pos < tamanhoS; pos++) {
                int trocar_prox = 0; //controla se o próximo led precisa trocar

                if (sempre_troca) {
                    if (S[pos] == 'O') {
                        S[pos] = 'X'; //desliga o le
                        trocar_prox = 1; // próximo led deve trocar

                    } else { //estava desligado
                        S[pos] = 'O'; //liga o led
                        trocar_prox = 0; //para aqui, próximo não troca
                    }
                }
                //define se o próximo led deve trocar
                sempre_troca = trocar_prox;
            }
        }

        //printa o estado final deste fio
        printf("%s\n", S);

        //juntando na luz gigante
        if (teste > 0) {
            char ultimoSf = Sf[tamanhoSf - 1];
            char primeiroS = S[0];
            char ornamento;

            //definindo o ornamento baseado na paridade e comparação dos leds
            if (tamanhoSf % 2 == 0) { //tamanho par
                if (ultimoSf == primeiroS)
                    ornamento = '@';

                else
                    ornamento = '$';

            } else { //tamanho ímpar
                if (ultimoSf == primeiroS)
                    ornamento = '#';

                else
                    ornamento = '%';
            }

            //adicionando ornamento à luz gigante
            Sf[tamanhoSf] = ornamento;
            tamanhoSf++;
        }

        //copiando S para Sf
        for (int pos = 0; pos < tamanhoS; pos++) {
            Sf[tamanhoSf] = S[pos];
            tamanhoSf++;
        }

        //garantindo o fim da string
        Sf[tamanhoSf] = '\0';
    }

    //imprimindo a luz gigante formada por todos os fios
    printf("%s\n", Sf);

    return 0;
}
