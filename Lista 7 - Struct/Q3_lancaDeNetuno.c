#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estruturas obrigatorias
typedef struct Mecha Mecha; //permite usar Mecha* antes da struct existir

typedef struct {
    char nome[30];  //nome do sistema
    int atrib1; //depende do tipo (A: dano base, D: blindagem fixa, U: recuperação base)
    int atrib2; //depende do tipo (A: custo de energia, D: bonus por slot, U: multiplicador)

    //ponteiro de função para a sub-rotina, define o comportamento do sist
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

//struct do mecha com FAM
struct Mecha {
    int id; //identificador unico
    char modelo[50];  //nome do mecha
    int energia_atual; //energia atual (muda durante execucao)
    int num_sistemas; //quant de subsistemas
    int valor_wintermute; //dano recebido
    SubSistema sistemas[]; // Flexible Array Member (FAM), sera alocado dinamicamente
};

//prototipos das funcoes
void rotina_defesa(Mecha *m, int slot, int input, int *output);
void rotina_utilidade(Mecha *m, int slot, int input, int *output);
void rotina_ataque(Mecha *m, int slot, int input, int *output);

//main
int main() {
    int N;
    scanf("%d", &N); //le a quant de mechas

    //vetor de ponteiros para mecha
    Mecha **esquadrao = malloc(N * sizeof(Mecha *));

    for (int i = 0; i < N; i++) {
        int id, energia, Q;
        char modelo[50];

        scanf("%d %s %d %d", &id, modelo, &energia, &Q); //le os dados principais

        //alocacao
        Mecha *novo = malloc(sizeof(Mecha) + (Q * sizeof(SubSistema)));
        
        //preenchendo dados
        (*novo).id = id;
        strcpy((*novo).modelo, modelo);
        (*novo).energia_atual = energia;
        (*novo).num_sistemas = Q;

        //leitura dos subsistemas
        for (int j = 0; j < Q; j++) {
            char tipo;
            //lendo o tipo + dados
            scanf(" %c %s %d %d", &tipo, (*novo).sistemas[j].nome, &(*novo).sistemas[j].atrib1, &(*novo).sistemas[j].atrib2);
            
            //logica da funcao correta
            if (tipo == 'A') (*novo).sistemas[j].subrotina = rotina_ataque;
            else if (tipo == 'D') (*novo).sistemas[j].subrotina = rotina_defesa;
            else if (tipo == 'U') (*novo).sistemas[j].subrotina = rotina_utilidade;
        }
        
        scanf("%d", &(*novo).valor_wintermute); //le o valor do dano do wintermute
        esquadrao[id] = novo; //armazena na posição do id, ordenando automaticamente
    }

    //relatorio
    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");

    for (int i = 0; i < N; i++) { //percorre em ordem crescente de id
        Mecha *m = esquadrao[i];
        //cabecalho do mecha
        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", (*m).id, (*m).modelo, (*m).energia_atual);

        int output; //variavel para resultados das subrotinas
        
        //prioridade 1, defesa
        for (int j = 0; j < (*m).num_sistemas; j++) {
            if ((*m).sistemas[j].subrotina == rotina_defesa) {
                (*m).sistemas[j].subrotina(m, j, (*m).valor_wintermute, &output);
                printf("-> [DEFESA] %s | Dano final sofrido: %d\n", (*m).sistemas[j].nome, output);
            }
        }

        //prioridade 2, utilidade
        for (int j = 0; j < (*m).num_sistemas; j++) {
            // identifica pelo ponteiro de função
            if ((*m).sistemas[j].subrotina == rotina_utilidade) {
                // executa a função
                (*m).sistemas[j].subrotina(m, j, (*m).valor_wintermute, &output);
                printf("-> [UTILIDADE] %s | Energia atual: %d\n", (*m).sistemas[j].nome, output);
            }
        }

        //prioridade 3, ataque
        for (int j = 0; j < (*m).num_sistemas; j++) {
            if ((*m).sistemas[j].subrotina == rotina_ataque) {
                (*m).sistemas[j].subrotina(m, j, (*m).valor_wintermute, &output);

                if (output == -1) {  //verifica se falhou
                    printf("-> [ATAQUE] %s | Energia insuficiente!\n", (*m).sistemas[j].nome);
                } else {
                    printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", 
                           (*m).sistemas[j].nome, output, (*m).energia_atual);
                }
            }
        }

        // energia final do mecha
        printf("ENERGIA FINAL: %d\n", (*m).energia_atual);
        printf("-----------------------------------------\n");
        free(m); //liberacao de memoria do mecha
    }

    printf("Esquadrao pronto para o combate.\n");
    free(esquadrao); //liberando vetor de ponteiros
    return 0;
}

//implementação das sub-rotinas

void rotina_defesa(Mecha *m, int slot, int input, int *output) { //defesa
    int d_base = (*m).sistemas[slot].atrib1;
    int bonus = slot * (*m).sistemas[slot].atrib2;

    int dano = input - d_base - bonus; //formula do enunciado
    if (dano < 0) dano = 0; //nunca pode ser negativo   
    *output = dano;
}

void rotina_utilidade(Mecha *m, int slot, int input, int *output) { //utilidade
    int recuperado = (*m).sistemas[slot].atrib1 + (slot * (*m).sistemas[slot].atrib2);
    (*m).energia_atual += recuperado;

    *output = (*m).energia_atual; //retorna energia atual
}

void rotina_ataque(Mecha *m, int slot, int input, int *output) { //ataque
    SubSistema *s = &((*m).sistemas[slot]);

    if ((*m).energia_atual < (*s).atrib2) { //verifica se tem energia suficiente
        *output = -1; //erro

    } else {
        int dano = (*s).atrib1 + (*m).energia_atual + slot - input; //calculo do dano
        (*m).energia_atual -= (*s).atrib2; //consome energia
        *output = dano;
    }
}
