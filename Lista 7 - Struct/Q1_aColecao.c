#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct jogo{
        char titulo[100];
        char genero [100];
        char estudio [100];
        char console [100];
        int nota;
        int anoLancamento;
    };

    typedef struct jogo jogo;

int main(){

    int N;
    scanf ("%d", &N); //recebe a quantidade de entradas

    jogo colecao[100]; //vetor que armazena no maximo 100 jogos

    //catalogando os jogos
    for (int i = 0; i < N; i++){
        scanf("%s %s %s %s %d %d", 
              colecao[i].titulo, 
              colecao[i].genero, 
              colecao[i].estudio, 
              colecao[i].console, 
              &colecao[i].nota, 
              &colecao[i].anoLancamento);

        if (colecao[i].nota > 7) { //se tiver nota maior que 7
            printf("AWESOME! Mais um GOTY pra minha coleção!\n");

        } else if (colecao[i].nota < 4) { //se tiver nota menor que 4
            printf("Era melhor jogar mais um jogo de Mahjong.\n");
        }
    }

    char funcao [50]; //funçao que escolhe os jogos que vao ser printados

    while (scanf("%s", funcao) != EOF){ //recebe funcoes ate eof

        int jogos_achados = 0; //jogos encontrados com uma caracteristica especifica

        if (strcmp(funcao, "printAno") == 0){ //se a funcao for pra procurar jogos de um ano especifico
            int ano_especifico;
            scanf("%d", &ano_especifico); //recebe ano

            for (int i = 0; i < N; i++){
                if (colecao[i].anoLancamento == ano_especifico){
                    printf("%s\n", colecao[i].titulo); //printa todos os jogos desse ano
                    jogos_achados++; //vai incrementando a quantidade de jogos achados nesse ano
                }
            }
            if (jogos_achados > 0) printf("Tenho %d jogos || %d.\n", jogos_achados, ano_especifico);
            else printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
        }

        else if (strcmp(funcao, "printLetra") == 0){ //se a funcao for pra procurar jogos que comecam com uma letra especifica
            char letra;
            scanf(" %c", &letra); //recebe letra

            for (int i = 0; i < N; i++) {
                if (colecao[i].titulo[0] == letra) {
                    printf("%s\n", colecao[i].titulo); //printa todod os jogos com essa letra
                    jogos_achados++;//vai incrementando a quant de jogos com essa letra
                }
            }
            if (jogos_achados > 0) printf("Tenho %d jogos || %c.\n", jogos_achados, letra);
            else printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
        }

        else if (strcmp(funcao, "printStudio") == 0){ //se a funcao for pra procurar jogos de um estudio especifico
            char estudio_especifico[100];
            scanf("%s", estudio_especifico); //recebe o estudio

            for (int i = 0; i < N; i++){
                if (strcmp(colecao[i].estudio, estudio_especifico) == 0){
                    printf("%s\n", colecao[i].titulo); //printa todos os jogod desse estudio
                    jogos_achados++; //incrementa a quant de jogos desse estudio
                }
            }
            if (jogos_achados > 0) printf("Tenho %d jogos || %s.\n", jogos_achados, estudio_especifico);
            else printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
        }

        else if (strcmp(funcao, "printConsole") == 0){ //se a funcao for pra procurar jogos de um console especifico
            char console_especifico[100];
            scanf("%s", console_especifico); //recebe o console

            for(int i = 0; i < N; i++){
                if (strcmp(colecao[i].console, console_especifico) == 0){
                    printf("%s\n", colecao[i].titulo); //printa todos os jogos desse console
                    jogos_achados++; //incrementa a qnt de jogos desse console
                }
            }
            if (jogos_achados > 0) printf("Tenho %d jogos || %s.\n", jogos_achados, console_especifico);
            else printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
        }

        else if (strcmp(funcao, "printColecao") == 0){ //se a funcao for para printar todas as colecoes
            for (int i = 0; i < N; i++) {
                printf("%s %d\n", colecao[i].titulo, colecao[i].nota); //printa  todos os títulos e as notas
            }
        }
    }

    printf("Enjoei de jogar, agora vou ver TV.\n"); //print final, quando acabarem os jogos do catalogo

    return 0;
}
