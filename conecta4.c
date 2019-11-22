#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct nodo {
};

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
/*Función para verificar si el jugador gano*/
bool gano(char tablero[6][7], char color){
    int i,j;
    for(i = 0; i < 6; i++) {
        for(j = 0; j < 4;j++) {
            if (tablero[i][j] == color && tablero[i][j+1] == color && tablero[i][j+2] == color && tablero[i][j+3] == color)
                return true;
        }
    }
    for(i = 0; i < 3;i++) {
        for(j = 0; j < 7; j++) {
            if (tablero[i][j] == color && tablero[i+1][j] == color && tablero[i+2][j] == color && tablero[i+3][j] == color)
                return true;
        }
    }
    for(i = 0; i < 6; i++) {
        for(j = 0; j < 7; j++) {
            if (i+3 < 6 && j+3 < 7) {
                if (tablero[i][j] == color && tablero[i+1][j+1] == color && tablero[i+2][j+2] == color && tablero[i+3][j+3] == color){
                    return true;
                }
            }
        }
    }
    for(i = 0; i < 6; i++) {
        for(j = 0; j < 7; j++) {
            if (i+3 < 6 && j-3>=0) {
                if (tablero[i][j] == color && tablero[i+1][j-1] == color && tablero[i+2][j-2] == color && tablero[i+3][j-3] == color){
                    return true;
                }
            }
        }
    }
    return false;
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
        if(tirar(tablero[][], 'R', 1)){
            imprimeTablero(tablero);
        }else{
            continue;
        }
    }while(gano(tablero[][],color));
    getchar();
    return 0;
}
