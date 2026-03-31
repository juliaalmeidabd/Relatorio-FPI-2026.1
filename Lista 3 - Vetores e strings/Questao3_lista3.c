#include <stdio.h>

int main() {
    char frase[101];

    //lendo a frase completa (com espaços)
    scanf("%[^\n]", frase);

    //vetores para guardar informações das palavras
    int inicio_palavra[50]; //onde começa cada palavra
    int tam_palavra[50]; //tamanho de cada uma
    int quant_palavras = 0; //quantidade de palavras

    for (int i = 0; frase[i] != '\0'; i++) { //separando as palavras

        //se encontrou uma letra, achou o inicio de uma palavra
        if ((frase[i] >= 'a' && frase[i] <= 'z') || (frase[i] >= 'A' && frase[i] <= 'Z')) {

            inicio_palavra[quant_palavras] = i;

            int tamanho = 0;

            // Conta o tamanho da palavra
            while ((frase[i] >= 'a' && frase[i] <= 'z') || (frase[i] >= 'A' && frase[i] <= 'Z')) {
                tamanho++;
                i++;
            }

            tam_palavra[quant_palavras] = tamanho;
            quant_palavras++;
        }
    }

    int total_anagramas = 0;
    int ja_apareceu = 0;

    //comparando cada par de palavras
    for (int i = 0; i < quant_palavras; i++) {
        for (int j = i + 1; j < quant_palavras; j++) {

            //se tiverem tamanhos diferentes, já não são anagramas
            if (tam_palavra[i] != tam_palavra[j]) continue;
            
            //para controlar a frequencia de cada letra na palavra
            int freq_letras1[26] = {0};
            int freq_letras2[26] = {0};

            //contando letras da palavra i
            for (int k = 0; k < tam_palavra[i]; k++) {
                char letra = frase[inicio_palavra[i] + k];

                if (letra >= 'A' && letra <= 'Z') {
                    letra = letra + ('a' - 'A');
                }

                freq_letras1[letra - 'a']++;
            }

            //contando letras da palavra j
            for (int k = 0; k < tam_palavra[j]; k++) {
                char letra = frase[inicio_palavra[j] + k];

                if (letra >= 'A' && letra <= 'Z') {
                    letra = letra + ('a' - 'A');
                }

                freq_letras2[letra - 'a']++;
            }

            //verificando se são anagramas
            int anagrama = 1;

            for (int k = 0; k < 26; k++) {
                if (freq_letras1[k] != freq_letras2[k]) {
                    anagrama = 0;
                    break;
                }
            }

            //se for anagrama, imprime
            if (anagrama) {
                if (!ja_apareceu) {
                    printf("Pares de anagramas encontrados:\n");
                    ja_apareceu = 1;
                }

                //imprime palavra i
                for (int k = 0; k < tam_palavra[i]; k++) {
                    printf("%c", frase[inicio_palavra[i] + k]);
                }

                printf(" e ");

                //imprime palavra j
                for (int k = 0; k < tam_palavra[j]; k++) {
                    printf("%c", frase[inicio_palavra[j] + k]);
                }

                printf("\n");

                total_anagramas++;
            }
        }
    }

    //print final
    if (total_anagramas > 0) {
        printf("\nTotal de pares: %d\n", total_anagramas);
    } else {
        printf("Nao existem anagramas na frase.\n");
    }

    return 0;
}
