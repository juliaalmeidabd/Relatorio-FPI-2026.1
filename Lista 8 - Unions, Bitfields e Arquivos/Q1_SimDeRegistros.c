#include <stdio.h>

typedef union {
    unsigned char rawByte; //byte bruto (8 bits)
    struct { //struct pra "dividir" esse byte

        unsigned char erro: 1; //1 bit, guarda valores de 0 a 1
        unsigned char modo: 3; //2 bits, guarda valores de 0 a 7
        unsigned char leitura: 4; //4 bits, guarda valores de 0 a 15

    } campos; //nome da estrutura interna (erro, modo, leitura)

} SensorStatus; //nome desse novo tipo criado

int main() {
    SensorStatus s; //declarando variavel s, de tipo SensorStatus
    unsigned int entrada; //variavel temporaria pra armazenar o inteiro recebido

    while (scanf("%u", &entrada) == 1) {

        //convertendo o inteiro  pra unsigned char e armazenando em rawByte
        //rawByte e campos dividem a mesma memoria, entao mudando o dado bruto os bitfields se atualizam sozinhos
        s.rawByte = (unsigned char)entrada;

        //saida
        printf("Byte bruto: %u | Erro: %u | Modo: %u | Leitura: %u\n", s.rawByte, s.campos.erro, s.campos.modo, s.campos.leitura);
    }

    return 0;
}
