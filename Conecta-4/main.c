#include "conecta.h"

extern int dificultad;

int main()
{
    int i,j;
    struct nodo* raiz = (struct nodo*)malloc(sizeof(struct nodo));
    char tablero[6][7];
    printf("Escribe la dificultad, de preferencia un número menor a 6\n");
    scanf("%i", &dificultad);
    if(dificultad == 0){
        dificultad = 1;
    }
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
                imprimeTablero(tablero);
                printf("Ganaste!\n");
                break;
            }else{
                tirar(raiz->tablero, 'A', columna);
                generarJugadas(raiz->tablero, 0, 'R', raiz);
                minMax(true,raiz);
                if (tirar(tablero, 'R', raiz->siguiente)){
                    if(gano(tablero, 'R')){
                        imprimeTablero(tablero);
                        printf("Perdiste :c!\n");
                        break;
                    }
                }else{
                    printf("Que?\n");
                }
                bool empate =  true;
                for (i= 0; i < 6; i++){
                    for(j = 0; j < 7; j++){
                        if(tablero[i][j] == ' '){
                            empate = false;
                        }
                        raiz->tablero[i][j] = tablero[i][j];
                    }
                }
                if(empate){
                    printf("Nadie ha ganado! Suerte la proxima vez\n");
                    break;
                }
            }
        }else{
            printf("No se puede tirar mas en esa columna\n");
            continue;
        }
    }while(continuar);
    scanf("%i", &dificultad);
    return 0;
}
