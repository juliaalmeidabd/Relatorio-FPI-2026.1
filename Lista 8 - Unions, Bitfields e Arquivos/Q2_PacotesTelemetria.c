#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef union {
    uint32_t rawData; //dado bruto de 32 bits
    
    struct { //struct pra dividir os 32 bits do dado bruto
    
        uint32_t idSensor: 10; //10 bits (0 a 1023)
        uint32_t status: 3; //3 bits (0 a 7)
        uint32_t batBaixa : 1; //1 bit (0 ou 1)
        int temp: 12; //12 bits com sinal (complemento de 2)
        uint32_t paridade: 6; //6 bits de controle

    } campos;

} PacoteTelem; //nome do novo tipo criado

int main() {
    //inicializando vetor dinamico
    int capacidade = 2; //capacidade inicial pequena para forçar o realloc
    int totalPacotes = 0;
    
    PacoteTelem *vetorPacotes = (PacoteTelem *)malloc(capacidade * sizeof(PacoteTelem));
    if (vetorPacotes == NULL) {
        return 1; //falha de alocação inicial
    }

uint32_t entradaHex;

    //recebe vealores hexadecimais e só para quando a entrada for 0
    while (scanf("%i", &entradaHex) == 1 && entradaHex != 0) { //%x ou %i lêe formatos hexadecimais (com ou sem o 0x)
        
        //se atingir a capacidade maxima, dobra o tamanho do vetor
        if (totalPacotes >= capacidade) {
            capacidade *= 2; //dobra o tamanho da capacidade
            
            //realloc tenta esticar o vetor atual ou mover os dados para uma região maior na Heap
            PacoteTelem *tempVetor = (PacoteTelem *)realloc(vetorPacotes, capacidade * sizeof(PacoteTelem));

            //se realloc falhar (retornar null), limpa a memoria anterior para evitar memory leak
            if (tempVetor == NULL) {
                free(vetorPacotes); //libera o bloco anterior que ainda estava na memória
                return 1; //encerra o programa indicando erro
            }
            
            //se a realocação der certo, atualiza o ponteiro principal com o novo endereço
            vetorPacotes = tempVetor;
        }

        //armazena o dado bruto no vetor
        //atualizando o .rawData, os bitfields se ajustam sozinhos
        vetorPacotes[totalPacotes].rawData = entradaHex;
        totalPacotes++; //incrementa a quantidade de pacotes armazenados
    }

    //percorre o vetor dinamico do início até o total de pacotes que foram realmente lidos
    for (int i = 0; i < totalPacotes; i++) {

        //exibe o indice do pacote e o valor bruto formatado em hexadecimal com 8 digitos preenchidos com zeros (%08X)
        printf("Pacote [%d] - Dado Bruto: 0x%08X\n", i + 1, vetorPacotes[i].rawData);
        printf("ID do Sensor : %d\n", vetorPacotes[i].campos.idSensor);
        printf("Status : %d\n", vetorPacotes[i].campos.status);
        printf("Bateria Baixa: ");
        //checando o valor do bitfield (1 para SIM, 0 para Não)
        if (vetorPacotes[i].campos.batBaixa == 1) {
            printf("SIM (ALERTA)\n");
        } else {
            printf("Nao\n");
        }
        //para a temperatura, se o bit de sinal for 1, exibira um valor negativo correto
        printf("Temperatura : %d graus\n", vetorPacotes[i].campos.temp);
        printf("-------------------------------------------------\n");
    }

    //liberando memoria
    //limpa o vetor dinamico inteiro da memória ram antes do programa fechar
    free(vetorPacotes);
    
    //zerando o ponteiro pra evitar que ele aponte para um local invalido (ponteiro solto)
    vetorPacotes = NULL;

    return 0;
}
