#include <stdio.h>

int main(void) {
    int total, pa, pb, pc;
    int sobra = 0;
    int dinheiro_r = 3;
    int A, B, C;

    //vari�veis para controlar se ela investiu ou se foi possivel dividir o prêmio direto
    int investiu = 0;
    int dividiu = 0;

    scanf("%d %d %d %d", &total, &pa, &pb, &pc);

    A = total * pa / 100;
    B = total * pb / 100;
    C = total * pc / 100;

    //se as porcentagens de cada um forem em valores inteiros
    if ((total * pa % 100 == 0) && (total * pb % 100 == 0) && (total * pc % 100 == 0)){ 
        sobra = total - (A + B + C);
        investiu = 0;
        dividiu =1;
    }

    //se as porcentagens de cada um não forem valores inteiros
    else{
        int i1 = total + 1; //primeiro investimento
        int i2 = total + 2; //segundo investimento
        int i3 = total + 3; //terceiro investimento

        if ((i1 * pa % 100 == 0) && (i1 * pb % 100 == 0) && (i1 * pc % 100 == 0)){
            A = i1 * pa / 100;
            B = i1 * pb / 100;
            C = i1 * pc / 100;
            sobra = i1 - A - B - C;
            if (sobra > 1) {
                investiu = 1;
                dividiu = 1;
            }
        }
        else if ((i2 * pa % 100 == 0) && (i2 * pb % 100 == 0) && (i2 * pc % 100 == 0)){
            A = i2 * pa / 100;
            B = i2 * pb / 100;
            C = i2 * pc / 100;
            sobra = i2 - A - B - C;
            if (sobra > 2) {
                investiu = 2;
                dividiu = 1;
            }
        }
        else if ((i3 * pa % 100 == 0) && (i3 * pb % 100 == 0) && (i3 * pc % 100 == 0)){
            A = i3 * pa / 100;
            B = i3 * pb / 100;
            C = i3 * pc / 100;
            sobra = i3 - A - B - C;
            if (sobra > 3) {
                investiu = 3;
                dividiu = 1;
            }
        }
    }
        //se não for possível dividir
        if (dividiu == 0){
            puts("Nao foi dessa vez que Rebeka pode ajudar...");
        }
        //se der pra dividir
        else {
            printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", A, B, C);
        }

        //se investir 2 reais
        if (dividiu && investiu == 2){
            char c1, c2, c3;
            scanf(" %c %c %c", &c1, &c2, &c3);

            //vai somar as trÊs letras recebidas
            int soma = (c1 - 'a' + 1) + (c2 - 'a' + 1) + (c3 - 'a' + 1); //em c cada letra possui um valor, sendo o a = 97, b = 98...
            printf("%d\n", soma);
        }

        //se investir 3 reais
        else if (dividiu && investiu == 3){
            int x, y, z; //idade dos homens
            int parcelas = 0;
            scanf("%d %d %d", &y, &x, &z);

            //descobrindo a quantidade de parcelas
            if(x % 3 == 0){
                parcelas += x / 3;
            } 
            if (y % 3 == 0){
                parcelas += y / 3;
            }
            if (z % 3 == 0){
                parcelas += z / 3; //o total de parcelas vai sendo adicionado
            }
            printf("%d\n", parcelas);
        }
        
        //dinheiro final de rebeka
        if (dividiu > 0) {
            dinheiro_r += (sobra - investiu);
        }
        //frase final, se consegui ou não voltar pra casa
        if (dividiu && dinheiro_r >= 7) {
            puts("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!");
        }
        else {
            puts("E parece que Rebeka vai ter que voltar andando...");
        }
        return 0;
    }
