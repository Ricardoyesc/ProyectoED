#include "conecta.h"

int main()
{
    int i,j;
    struct nodo* raiz = (struct nodo*)malloc(sizeof(struct nodo));
    char tablero[6][7];
    printf("Escribe la dificultad, de preferencia un número menor a 6\n");
    scanf("%i", &dificultad);
    for (i= 0; i < 6; i++){
        for(j = 0; j < 7; j++){
            raiz->tablero[i][j] = ' ';
            tablero[i][j] = ' ';
        }
    }
    bool continuar = true;
    do{
        int columna;
        printf("Elije una columna donde tirar\n");
        imprimeTablero(tablero);
        scanf("%i", &columna);
        columna--;
        if (tirar(tablero, 'A', columna)){
            if(gano(tablero, 'A')){
                printf("Ganaste!\n");
                break;
            }else{
                tirar(raiz->tablero, 'A', columna);
                raiz = generarJugadas(raiz->tablero, 0, 0, 'R', raiz);
                minMax(0,true,raiz);
                if (tirar(tablero, 'R', raiz->siguiente)){
                    if(gano(tablero, 'R')){
                        printf("Perdiste :c!\n");
                        break;
                    }
                }
                for (i= 0; i < 6; i++){
                    for(j = 0; j < 7; j++){
                        raiz->tablero[i][j] = tablero[i][j];
                    }
                }
            }
        }else{
            printf("No se puede tirar mas en esa columna\n");
            continue;
        }
    }while(continuar);
    getchar();
    return 0;
}
