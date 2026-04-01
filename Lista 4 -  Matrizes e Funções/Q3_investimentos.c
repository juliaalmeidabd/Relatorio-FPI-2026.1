#include <stdio.h>

//funcao que processa a contagem na matriz
void registrar_passagem(int cidade[4][4], int x, int y) {
    if (x >= 0 && x < 4 && y >= 0 && y < 4) {
        cidade[x][y] = cidade[x][y] + 1;
    }
}

int main() {
    //matriz 4x4
    int cidade[4][4];
    int x = 0; //linha (X)
    int y = 0; //coluna (Y)
    char comando;

    //inicializando a matriz com zeros
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cidade[i][j] = 0;
        }
    }

    //Pedro começa no ponto (0,0)
    //registra a posição inicial só uma vez.
    registrar_passagem(cidade, x, y);

    //loop para ler exatamente as 20 variaveis
    for (int i = 0; i < 20; i++) {
        //espaco antes de %c ignora o enter e espacos
        if (scanf(" %c", &comando) == 1) {
            
            //comandos para movimentação
            if (comando == 'c' && x > 0) {
                x = x - 1;
            } 
            else if (comando == 'b' && x < 3) {
                x = x + 1;
            } 
            else if (comando == 'e' && y > 0) {
                y = y - 1;
            } 
            else if (comando == 'd' && y < 3) {
                y = y + 1;
            }

            //registra a nova posição após o movimento
            registrar_passagem(cidade, x, y);
        }
    }

    //encontrando a posição mais visitada
    int max = cidade[0][0];
    int maxX = 0, maxY = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (cidade[i][j] > max) {
                max = cidade[i][j];
                maxX = i;
                maxY = j;
            }
        }
    }

    //print final
    printf("Coordenada X:%d, Y:%d\n", maxY, maxX);

    return 0;
}
