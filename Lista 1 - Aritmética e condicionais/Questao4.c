#include <stdio.h>
#include <math.h>

int main(void) {

    int x, y, c;
    scanf("%d %d %d", &x, &y, &c);

    int quad_inicial;
    int quad_destino;

    //descobrindo o quadrante inicial

    if (x > 0 && y > 0){
            quad_inicial = 1; //coordenadas (+,+)
        }
    else if (x > 0 && y < 0){
            quad_inicial = 4; //coordenadas (+,-)
        }
    else if (x < 0 && y > 0){
            quad_inicial = 2; //coordenadas (-,+)
        }
    else{
            quad_inicial = 3; //coordenadas (-,-)
        }

    //definindo o quadrante de destino
    if (quad_inicial == 1){
        quad_destino = 3;
    }
    else if(quad_inicial == 2){
        quad_destino = 4;
    }
    else if(quad_inicial == 3){
        quad_destino = 1;
    }
    else{
        quad_destino = 2;
    }

    //coordenadas de cada quadrante de destino
    int x_dest, y_dest;

    if (quad_destino == 1){
        x_dest = 1, y_dest = 1;
    }
    else if (quad_destino == 2){
        x_dest = -1, y_dest = 1;
    }
    else if (quad_destino == 3){
        x_dest = -1, y_dest = -1;
    }
    else{
        x_dest = 1, y_dest = -1;
    }

    //caminhada inválida

    if (c == quad_inicial || c == quad_destino){
        puts("caminhada invalida");
    }

    //evitando o adjacente

    //cálculo dos passos
    int passos_x = x_dest - x;
    int passos_y = y_dest - y;

    if (passos_x < 0) passos_x = -passos_x;
    if (passos_y < 0) passos_y = -passos_y;

    //decidindo por qual caminho vai começar
    if (quad_inicial == 2 || quad_inicial == 4){ //se iniciar no 1° ou 4° quadrante

        if (c == 1){ //evitando o 1° quad
            if (quad_inicial == 2){ //vai por primeiro
                printf("%d passos em y e %d passos em x\n", passos_y, passos_x);
            }
            else if (quad_inicial == 4){ //vai por x primeiro
                printf("%d passos em x e %d passos em y\n", passos_x, passos_y);
            }
        }

        else if (c == 3){ //evitando o 3° quad
            if (quad_inicial == 2){ //vai por x primeiro
                printf("%d passos em x e %d passos em y\n", passos_x, passos_y);
            }
            else if (quad_inicial == 4){ //vai por y primeiro
                printf("%d passos em y e %d passos em x\n", passos_y, passos_x);
            }
        }

    }else if (quad_inicial == 1 || quad_inicial == 3){ //se iniciar no 1° ou 4° quadrante
        
        if (c == 2){ //evitando o 2° quad
            if (quad_inicial == 1){ //vai por y primeiro
                printf("%d passos em y e %d passos em x\n", passos_y, passos_x);
            }
            else if (quad_inicial == 3){ //vai por x primeiro
                printf("%d passos em x e %d passos em y\n", passos_x, passos_y);
            }

        else if (c == 4){ //evitando o 4° quad
            if (quad_inicial == 1){ //vai por x primeiro
                printf("%d passos em x e %d passos em y\n", passos_x, passos_y);
            }
            else if (quad_inicial == 3){ //vai por y primeiro
                printf("%d passos em y e %d passos em x\n", passos_y, passos_x);
            }
        }
    }
}

    return 0;
}
