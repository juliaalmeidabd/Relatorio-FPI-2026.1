#include <stdio.h>

#define MAX 500

//funcao que simula o gotejamento a partir de uma coordenada
void escorrer(int m, int n, char parede[MAX][MAX], int l, int c) {
    
    //se sair dos limites da matriz ou a posicao ja tiver agua, para
    if (l < 0 || l >= m || c < 0 || c >= n || parede[l][c] == 'o' || parede[l][c] == '#') {
        return;
    }

    //marcando a posicao atual com agua
    parede[l][c] = 'o';

    //se estiver na última linha, não há mais para onde cair
    if (l + 1 == m) return;

    //caminho de baixo livre
    if (parede[l + 1][c] == '.') {
        escorrer(m, n, parede, l + 1, c);
    } 
    //encontrou uma prateleira abaixo
    else if (parede[l + 1][c] == '#') {
        
        //espalha pra esquerda
        int esq = c - 1;

        while (esq >= 0) {
            parede[l][esq] = 'o';
            
            //se encontrar um buraco abaixo da prateleira, a água cai por lá
            if (parede[l + 1][esq] == '.') {
                escorrer(m, n, parede, l + 1, esq);
                break; //para de espalhar pra esse lado
            }
            //se bater na borda ou outra prateleira lateral
            if (parede[l][esq] == '#') break;
            esq--;
        }

        //espalha para a direita
        int dir = c + 1;
        while (dir < n) {
            parede[l][dir] = 'o';

            //se encontrar um buraco abaixo da prateleira, a agua cai por la
            if (parede[l + 1][dir] == '.') {
                escorrer(m, n, parede, l + 1, dir);
                break;
            }
            if (parede[l][dir] == '#') break;
            dir++;
        }
    }
}

int main() {
    int m, n;
    char parede[MAX][MAX];

    //lendo as dimensoes
    scanf("%d %d", &m, &n);

    //lendo a matriz
    int orig_l = -1, orig_c = -1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf(" %c", &parede[i][j]);
            //identifica a posição inicial da gota
            if (parede[i][j] == 'o' || parede[i][j] == 'O') {
                orig_l = i;
                orig_c = j;

                //reinicia para processar na função
                parede[i][j] = '.'; 
            }
        }
    }

    //simula a partir da origem encontrada
    if (orig_l != -1) {
        escorrer(m, n, parede, orig_l, orig_c);
    }

    //print do resultado
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c", parede[i][j]);
        }
        printf("\n");
    }

    return 0;
}
