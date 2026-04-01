#include <stdio.h>

#define MAX 100 //definindo os tamanhos maximos

//função para encontrar a menor distância
int buscar_fuga(int linhas, int colunas, char mapa[MAX][MAX]) {
    int dist[MAX][MAX];
    int fila_l[MAX * MAX], fila_c[MAX * MAX];
    int inicio = 0, fim = 0;
    
    //iniciando a matriz de distâncias com -1 (não foi visitada)
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            dist[i][j] = -1;
            //encontra a origem o para começar a busca
            if (mapa[i][j] == 'o') {
                fila_l[fim] = i;
                fila_c[fim] = j;
                dist[i][j] = 0;
                fim++;
            }
        }
    }

    //vetores de movimento, cima, baixo, esquerda e direita
    int dl[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (inicio < fim) {
        int l_atual = fila_l[inicio];
        int c_atual = fila_c[inicio];
        inicio++;

        //quando chega em 'd', retorna a distância acumulada
        if (mapa[l_atual][c_atual] == 'd') {
            return dist[l_atual][c_atual];
        }

        //tenta mover para as 4 direções
        for (int i = 0; i < 4; i++) {
            int nova_l = l_atual + dl[i];
            int nova_c = c_atual + dc[i];

            //verificando se está dentro do mapa, se não é parede e se não foi visitado
            if (nova_l >= 0 && nova_l < linhas && nova_c >= 0 && nova_c < colunas) {
                if (mapa[nova_l][nova_c] != '#' && dist[nova_l][nova_c] == -1) {
                    dist[nova_l][nova_c] = dist[l_atual][c_atual] + 1;
                    fila_l[fim] = nova_l;
                    fila_c[fim] = nova_c;
                    fim++;
                }
            }
        }
    }

    return -1; //se a fila esvaziar e não achar 'd
}

int main() {
    int l, c;
    char mapa[MAX][MAX];

    //lendo"linhasxcolunas"
    if (scanf("%dx%d", &l, &c) != 2) return 0;

    //lendo a matriz
    for (int i = 0; i < l; i++) {
        scanf("%s", mapa[i]);
    }

    int resultado = buscar_fuga(l, c, mapa);

    //prints dos resultados
    if (resultado != -1) {
        printf("Apos correr %d metros e quase desistir por causa da distância, Rebeka conseguiu escapar!\n", resultado);
    } else {
        printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");
    }

    return 0;
}
