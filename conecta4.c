#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct nodo {
};

bool gano(char tablero[6][7], int i, char color){
}
bool tirar(char tablero[6][7], char color, int columna){
    int i;
    columna--;
    for(i = 0;i < 6; i++){
        if(tablero[i][columna] == ' '){
            tablero[i][columna] = color;
            return true;
        }
    }
    return false;
}
void imprimeTablero(char tablero[6][7]){
    int i, j;
    printf("|");
    for(j = 1; j < 7; j++){
        printf("%d|",j);
    }
    printf("\n");
    for (i = 5; i >= 0; i--)
    {
        printf("|");
        for(j = 0; j < 6; j++){
            printf("%c|",tablero[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    char tablero[6][7];
    int i,j;
    for (i= 0; i < 6; i++)
    {
        for(j = 0; j < 7; j++){
            tablero[i][j] = ' ';
        }
    }
    do{
        if(tirar(tablero, 'R', 1)){
            imprimeTablero(tablero);
        }else{
            continue;
        }
    }while(gano(tablero, i, color));
    getchar();
    return 0;
}
