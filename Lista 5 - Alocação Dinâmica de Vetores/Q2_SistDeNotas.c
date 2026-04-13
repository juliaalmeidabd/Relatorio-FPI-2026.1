#include <stdio.h>
#include <stdlib.h>

//funcao pra calcular a media
float calculo_media (float *notas, int n){
    float soma = 0;
    for (int i = 0; i < n; i++){
        soma += notas[i];
    }
    return soma / n; //retorna a media
}

//funcao pra calcular a maior nota e o aluno
void maior_nota (float *notas, int n, float *maior, int *aluno ){
    *maior = notas[0]; //inicia a maior nota sendo a primeira
    *aluno = 1; //inicia o aluno com a maior nota como sendo  o primeiro da lista

    for (int i = 1; i < n; i++){
        if(notas[i] > *maior){
            *maior = notas[i];
            *aluno = i + 1;
        }
    }
}

//funcao pra calcular a menor nota e o aluno
void menor_nota(float *notas, int n, float *menor, int *aluno){
    *menor = notas[0]; //inicia a menor nota sendo a primeira
    *aluno = 1; //inicia o aluno com a menor nota como sendo  o primeiro da lista

    for (int i = 1; i < n; i++){
        if(notas[i] < *menor){
            *menor = notas[i];
            *aluno = i + 1;
        }
    }
}

//funcao para calcular a quant de alunos acima da media
int alunos_acima(float *notas, int n, float media) {
    int quantidade = 0; //inicia em 0 alunos

    for (int i = 0; i < n; i++){
        if (notas[i] > media){
            quantidade++;
        }
    }
    return quantidade;
}

void ordenar(float *vetor, int n){ //bubble sort pra ordenar o vetor
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                float temp = vetor[j]; //
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

//funcao pra calcular a mediana
float calculo_mediana(float *notas, int n){
    if (n % 2 != 0) { //se for uma quant impar
        return notas[n / 2];
    }
    else{ //se for uma quant par
        return (notas[(n / 2) - 1] + notas[n / 2]) / 2.0;
    }
}

//funcao pra calcular a moda
void calculo_moda(float *notas, int n) {
    int maior_freq = 0;
    int freq_atual = 1;
    int quant_modas = 0;
    float moda;

    for (int i = 1; i <= n; i++) {
        if (i < n && notas[i] == notas[i-1]){
            freq_atual++;
        }
        else {
            if (freq_atual > maior_freq) { 
                maior_freq = freq_atual; 
                moda = notas[i-1]; 
                quant_modas = 1; 
            }
            else if (freq_atual == maior_freq){
                quant_modas++;
            }
                freq_atual = 1;
        }
    }
    if (maior_freq > 1 && quant_modas == 1){
        printf("Moda: %.2f\n", moda);
    }
    else{
        printf("Moda: Nao ha moda unica\n");
    }
}

//funcao pra imprimir o relatorio
void imprimir_relatorio(float *notas, int n, char *titulo) {
    float media = calculo_media(notas, n);
    float maior, menor;
    int aluno_maior, aluno_menor;
    
    maior_nota(notas, n, &maior, &aluno_maior); //maior nota e aluno correspondente
    menor_nota(notas, n, &menor, &aluno_menor); //menor nota e aluno correspondente
    
    float *temp = (float *)malloc(n * sizeof(float)); //variavel temporaria para ordenar
    for(int i=0; i<n; i++) temp[i] = notas[i];
    ordenar(temp, n); //ordenando

    printf("%s\n", titulo);
    printf("Media: %.2f\n", media);
    printf("Maior nota: %.2f (aluno %d)\n", maior, aluno_maior);
    printf("Menor nota: %.2f (aluno %d)\n", menor, aluno_menor);
    printf("Acima da media: %d\n", alunos_acima(notas, n, media));
    printf("Mediana: %.2f\n", calculo_mediana(temp, n));
    calculo_moda(temp, n);
    printf("\n");

    free(temp);
}

int main (){

    int n; //quantidade inicial de alunos
    int k; //notas adicionadas

    scanf("%d", &n); //recebe n

    float *notas = malloc((n) * sizeof(float)); //ponteiro para as notas iniciais
    for (int i = 0; i < n; i++){
        scanf("%f", &notas[i]); //recebe e armazena as n notas iniciais
    }

    //print do relatorio inicial
    imprimir_relatorio(notas, n, "Relatorio inicial");

    scanf("%d", &k); //recebe k

    notas = realloc(notas, (n + k) * sizeof(float)); //realloc para aumentar o tamanho do ponteiro notas para n + k

    for (int i = 0; i < k; i++) { 
        scanf("%f", &notas[n + i]); //recebe ae armazena as k notas novas
    }
    n += k;

    //print do relatorio atualizado
    imprimir_relatorio(notas, n, "Relatorio atualizado");
    
    return 0;
}
