#include <math.h>
#include <stdio.h>

int main()
{
    int da1, da2, da3, dn1, dn2, dn3;
    scanf("%d/%d/%d %d/%d/%d", &da1, &da2, &da3, &dn1, &dn2, &dn3);

    //porcentagem de amor
    int p_amor = ((da1 + da2 + da3 + dn1 + dn2 + dn3) * 7)%101;

    printf("Amor: %d%% ", p_amor);

    //condições para cada frase de amor

    if (p_amor < 20){
        puts("Pessimo dia para se apaixonar.");
    }else if (p_amor >= 20 && p_amor <= 40){
        puts("Melhor manter o coracao <3 longe de perigo.");
    }else if (p_amor >= 41 && p_amor <= 69){
        puts("Se o papo e as ideias baterem, esta liberado pensar em algo.");
    }else if (p_amor >=70 && p_amor <= 80){
        puts("Saia com o coracao aberto, mas lembre, nem toda troca de olhar em onibus e sinal de romance.");
    }else if (p_amor > 80){
        puts("Um dia deslumbrantemente lindo para amar. Ps: Cuidado com a intensidade.");
    }

    //porcentagem de sorte
    int dif_anos;

    if (da3 > dn3){
        dif_anos = da3 - dn3;
    }else {
        dif_anos = dn3 - da3;
    }

    int p_sorte = ((da1 + da2 + dn1 + dn2) * 9 + dif_anos) %101;

    printf("Sorte: %d%% ", p_sorte);

    //condições para cada frase de sorte

    if (p_sorte < 30){
        printf("Nem jogue moedas pra cima hoje.");
    }else if (p_sorte >= 30 && p_sorte <= 50){
        printf("Melhor nao arriscar.");
    }else if (p_sorte >= 51 && p_sorte <= 79){
        printf("Por sua conta em risco.");
    }else if (p_sorte >=80 && p_sorte <= 90){
        printf("Hoje vale a pena arriscar.");
    }else if (p_sorte > 90){
        printf("Nao tenha medo de virar cartas hoje.");
    }
    puts(" Sem tigrinho nem jogos de azar, por favor!");

    //porcentagem de trabalho

    int p_trabalho = ((da3 + dn3) - ((da1 + da2 + dn1 + dn2) * 8)) %101;

    printf ("Trabalho: %d%% ", p_trabalho);

    //condições para cada frase de trabalho

    if (p_trabalho < 40){
        puts("Hoje nao sera um dia tao proveitoso, keep calm e faca o basico.");
    }else if (p_trabalho >= 40 && p_trabalho <= 50){
        puts("Segura a emocao, nao xinga ninguem, nao esquece de beber agua.");
    }else if (p_trabalho >= 51 && p_trabalho <= 69){
        puts("Um dia proveitoso com certeza, leve sua simpatia consigo.");
    }else if (p_trabalho >=70 && p_trabalho <= 84){
        puts("Boas vibracoes hoje, chances podem estar ao seu redor.");
    }else {
        puts("Use do maximo de networking possível hoje, dia bom para negocios.");
    }

    //número de cor

    int n_cor = ((da1 * da1) + (da2 * da2) + (da3 * da3) + (dn1 * dn1) + (dn2 * dn2) + (dn3 * dn3)) %11;

    printf ("Cor: ");

    if (n_cor == 0){
        puts ("Cinza.");
    }else if (n_cor == 1){
        puts ("Vermelho.");
    }else if (n_cor == 2){
        puts("Laranja.");
    }else if (n_cor == 3){
        puts("Amarelo.");
    }else if (n_cor == 4){
        puts("Verde.");
    }else if (n_cor == 5){
        puts("Azul.");
    }else if (n_cor == 6){
        puts("Roxo.");
    }else if (n_cor == 7){
        puts("Marrom.");
    }else if (n_cor == 8){
        puts("Rosa.");
    }else if (n_cor == 9){
        puts("Preto.");
    }else if (n_cor == 10){
        puts("Branco.");
    }

    return 0;
}
