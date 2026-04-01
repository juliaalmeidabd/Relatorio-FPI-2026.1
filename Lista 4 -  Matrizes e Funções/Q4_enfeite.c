#include <stdio.h>

#define MAX 100

//funcao para verificar se a posicao ta dentro dos limites e pode ser alterada
int pode_marcar(int m, int n, char matriz[MAX][MAX], int l, int c) {
    if (l >= 0 && l < m && c >= 0 && c < n) {
        if (matriz[l][c] != 'P') {
            return 1;
        }
    }
    return 0;
}

//funcao para desenhar os enfeites de um poste especIfico
void desenhar_enfeites(int m, int n, char original[MAX][MAX], char resultado[MAX][MAX], int l, int c) {
    
    //marcações em diagonal (x)
    int diag_l[] = {-1, -1, 1, 1};
    int diag_c[] = {-1, 1, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nl = l + diag_l[i];
        int nc = c + diag_c[i];

        if (pode_marcar(m, n, original, nl, nc)) {
            //so coloca x se a posição ainda estiver vazia
            if (resultado[nl][nc] == '-') {
                resultado[nl][nc] = 'x';
            }
        }
    }

    //marcações em inha reta (+)
    int reta_l[] = {-1, 1, 0, 0};
    int reta_c[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nl = l + reta_l[i];
        int nc = c + reta_c[i];

        if (pode_marcar(m, n, original, nl, nc)) {
            //o + sempre tem prioridade
            resultado[nl][nc] = '+';
        }
    }
}

int main() {
    int m, n;
    char original[MAX][MAX];
    char resultado[MAX][MAX];

    //lendo as dimensoes
    if (scanf("%d %d", &m, &n) != 2) return 0;

    //lendona matriz
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf(" %c", &original[i][j]);
            resultado[i][j] = original[i][j]; // Inicializa a matriz de resultado idêntica
        }
    }

    //processa cada posicao procurando por postes
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (original[i][j] == 'P') {
                desenhar_enfeites(m, n, original, resultado, i, j);
            }
        }
    }

    //matriz final
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c", resultado[i][j]);
        }
        printf("\n");
    }

    return 0;
}
