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
bool check(char tablero[6][7], int color,int a1,int a2,int b1,int b2,int c1,int c2,int d1,int d2 ){
  if (tablero[a1][a2]==tablero[b1][b2]&&tablero[b1][b2]==tablero[c1][c2]&&tablero[c1][c2]==tablero[d1][d2]&&tablero[a1][a2]==color)
    return true;
  return false;
}
bool hor(char tablero[6][7], char color){
  int j,k;
  for (j = 0; j <6; j++) {
    for (k = 0; k < 4; k++) {
      if(check(tablero[6][7],color,j,k,j,k+1,j,k+2,j,k+3))
        return true;
    }
  }
  return false;
}

bool ver(char tablero[6][7], char color){
  int j,k;
  for (j = 0; j <3; j++) {
    for (k = 0; k < 7; k++) {
      if(check(tablero[6][7],color,j,k,j+1,k,j+2,k,j+3,k))
        return true;
    }
  }
  return false;
}

bool diader(char tablero[6][7], char color){
  int j,k;
  for (j = 0; j <3; j++) {
    for (k = 0; k < 4; k++) {
      if(check(tablero[6][7],color,j,k,j+1,k+1,j+2,k+2,j+3,k+3))
        return TRUE;
    }
  }
  return false;
}
bool diaizq(char tablero[6][7], char color){
  int j,k;
  for (j = 0; j < 3; j++) {
    for (k = 3; k < 7; k++) {
      if(check(tablero[6][7],color,j,k,j+1,k-1,j+2,k-2,j+3,k-3))
        return TRUE;
    }
  }
  return false;
}

bool gano(char tablero[6][7], char color){
  if(hor(tablero[][],color)||ver(tablero[][],color)||diader(tablero[][],color)||diaizq(tablero[][],color))
    return true;
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
