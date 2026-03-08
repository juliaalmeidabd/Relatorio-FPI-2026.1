#include <stdio.h>
#include <math.h>

int main(void)
{ 
    long long int N, a, b;

    scanf("%lld", &N);
    scanf("%lld %lld", &a, &b);

    long long int soma_total = (N*(N + 1)) / 2;

    //soma dos multiplos de a 
    long long int soma_mult_a = a * (N / a) * (N / a + 1) / 2;

    //soma multiplos de b
    long long int soma_mult_b = b * (N / b) * (N / b + 1) / 2;

    //soma multiplos de ab (corrigir a exclusão dupla, pois são primos)
    long long int soma_mult_ab = a*b * (N / (a*b)) * (N / (a*b) + 1) / 2;

    //resultado final
    long long int resultado = soma_total - soma_mult_a - soma_mult_b + soma_mult_ab;

    printf("%lld\n", resultado);

    //se o resultado for par
    if (resultado % 2 == 0){
        puts("Lá ele!!!");
    }
    else{
        puts("Opa xupenio AULAS...");
    }

    return 0;

}
