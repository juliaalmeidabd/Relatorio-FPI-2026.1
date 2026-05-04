#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct cidadela {
    char nome[100];
    int quant_habitantes;
    int periculosidade;
    char funcao[100];
} cidadela;

int main(){

    cidadela lista_cidades [200];
    int total_cidades = 0;
    int chave = -1; //ainda nao achei nenhuma chave
    char mensagem [200];

    //lendo as entradas linha por linha
    while (fgets(mensagem, 200, stdin) != NULL){

        int exclamacao = 0;
        
        for (int i = 0; mensagem[i] != '\0'; i++) { //verificando se tem exclamacao (se e especial)
            if (mensagem[i] == '!') {
                exclamacao = 1; 
                break;
            }
        }

        if (exclamacao == 1){ //se for especial, os numeros não são a quant de pessoas, mas sim a chave
            int numChave = 0;
            
            for (int i = 0; mensagem[i] != '\0'; i++) {

                if (isdigit(mensagem[i])) { //se for um numero
                    numChave = numChave * 10 + (mensagem[i] - '0');
                }
            }
            chave = numChave; //a chave vai ser a uniao dos algarismos encontrados
        }

        else{
           //inicializando a quant de habitantes e a periculosidade como 0 e o nome e a funcao como strings vazias
           lista_cidades[total_cidades].quant_habitantes = 0;
           lista_cidades[total_cidades].periculosidade = 0;
           lista_cidades[total_cidades].nome[0] = '\0';
           lista_cidades[total_cidades].funcao[0] = '\0';

           int nome_idx = 0; //indice dos caracteres do nome
           int funcao_idx = 0; //indice dos caracteres da funcao
           int ja_processou_funcao = 0; //flag pra controlar se ja formou a funcao (ja pegou todas as letras depois de espacos duplos)

           for (int i = 0; mensagem[i] != '\0'; i++) { //adicionando as informacoes da cidadela

                //guardando o nome (tudo maiusculo ainda)
                if (isupper(mensagem[i])) { //se achar letras maiusculas
                    lista_cidades[total_cidades].nome[nome_idx++] = mensagem[i];
                }

                //guardando a populacao
                if (isdigit(mensagem[i])) { //se forem numeros (sem ser especial)
                    lista_cidades[total_cidades].quant_habitantes = 
                        lista_cidades[total_cidades].quant_habitantes * 10 + (mensagem[i] - '0');
                }

                //guardando a periculosidade
                if (mensagem[i] == '*') { //se achar asteriscos
                    lista_cidades[total_cidades].periculosidade++;
                }

                //detectando o espaco duplo e pegando apenas a primeira letra depois dele, ate terminar de formar a funcao
                if (mensagem[i] == ' ' && mensagem[i+1] == ' ' && !ja_processou_funcao) {
                    ja_processou_funcao = 1; //terminaram os espacos duplos
            
                    for (int j = i + 1; mensagem[j] != '\0'; j++) {
                        
                        if (isalpha(mensagem[j]) && isspace(mensagem[j-1])) {
                            lista_cidades[total_cidades].funcao[funcao_idx++] = mensagem[j];
                        }
                    }
                
                }
            }
            
            //fim do nome e da funcao
            lista_cidades[total_cidades].nome[nome_idx] = '\0';
            lista_cidades[total_cidades].funcao[funcao_idx] = '\0';

            if (nome_idx > 0) { //formatando o nome
                lista_cidades[total_cidades].nome[0] = toupper(lista_cidades[total_cidades].nome[0]);
                for (int k = 1; k < nome_idx; k++) {
                    lista_cidades[total_cidades].nome[k] = tolower(lista_cidades[total_cidades].nome[k]);
                }
                
                if (funcao_idx > 0) { //formatando a funcao
                    lista_cidades[total_cidades].funcao[0] = toupper(lista_cidades[total_cidades].funcao[0]);
                    for (int k = 1; k < funcao_idx; k++) {
                        lista_cidades[total_cidades].funcao[k] = tolower(lista_cidades[total_cidades].funcao[k]);
                    }
                }
                
                total_cidades++; //passa pra proxima posicao do vetor
            }
        }
    }

    //se nao recebeu chave
    if (chave == -1) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
    }

    else {

        //evita acessar posição inválida
        if (chave > total_cidades) chave = total_cidades;

        //ordenando por bubble sort
        for (int i = 0; i < total_cidades - 1; i++) {
            for (int j = 0; j < total_cidades - i - 1; j++) {
                int trocar = 0;

                //criterio 1 - habitantes (decrescente)
                if (lista_cidades[j].quant_habitantes < lista_cidades[j+1].quant_habitantes) {
                    trocar = 1;
                } 
                else if (lista_cidades[j].quant_habitantes == lista_cidades[j+1].quant_habitantes) {
                    //critério 2 - periculosidade (decrescente)
                    if (lista_cidades[j].periculosidade < lista_cidades[j+1].periculosidade) {
                        trocar = 1;
                    } 
                    else if (lista_cidades[j].periculosidade == lista_cidades[j+1].periculosidade) {
                        //critério 3 - nome (ordem alfabetica)
                        if (strcmp(lista_cidades[j].nome, lista_cidades[j+1].nome) > 0) {
                            trocar = 1;
                        }
                    }
                }

                if (trocar) {
                    cidadela temp = lista_cidades[j];
                    lista_cidades[j] = lista_cidades[j+1];
                    lista_cidades[j+1] = temp;
                }
            }
        }

        //saidas
        cidadela g = lista_cidades[chave - 1];
        
        printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade ", 
                g.nome, g.quant_habitantes, g.funcao);
        
        for(int i = 0; i < g.periculosidade; i++) printf("*");
        printf(".");

        int denso = (g.quant_habitantes >= 1000);
        int perigoso = (g.periculosidade > 3);

        if (denso && perigoso) printf(" Talvez seja melhor desistir...\n");
        else if (denso) printf(" Um lugar denso, vai ser difícil achar ela.\n");
        else if (perigoso) printf(" Vai ser complicado entrar lá.\n");
        else printf("\n");
    }

    return 0;
}
