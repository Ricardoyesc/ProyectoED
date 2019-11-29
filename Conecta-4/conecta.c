#include "conecta.h"

int dificultad = 0;

bool tirar(char tablero[6][7], char color, int columna){
    int i;
    for(i = 0; i < 6; i++){
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
    for(j = 1; j < 8; j++){
        printf("%d|",j);
    }
    printf("\n");
    for (i = 5; i >= 0; i--){
        printf("|");
        for(j = 0; j < 7    ; j++){
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

/*Funcion que devuelve el nodo al cual va a tirar*/
int minMax(bool buscarMax, struct nodo* nodo) {
    int k = 0;
    bool todosNulos = true;
    for(k = 0; k < 7; k++){
        if(nodo->hijos[k] != NULL){
            todosNulos = false;
            break;
        }
    }
    if(todosNulos){
        return nodo->valor;
    }
    if(buscarMax){
        int i = 0, j = 0;
        int valorMax;
        for(i = 0; i < 7; i++){
            if(nodo->hijos[i] != NULL){
                valorMax = minMax(false, nodo->hijos[i]);
                free(nodo->hijos[i]);
                nodo->hijos[i] = NULL;
                nodo->siguiente = i;
                break;
            }
        }
        for(i; i < 7; i++){
            if(nodo->hijos[i] != NULL){
                int temp = minMax(false, nodo->hijos[i]);
                if(valorMax < temp){
                    valorMax = temp;
                    nodo->siguiente =  i;
                }
                free(nodo->hijos[i]);
                nodo->hijos[i] = NULL;
            }
        }
        nodo->valor = valorMax;
        return nodo->valor;
    }else{
        int i = 0;
        int valorMin;
        for(i = 0; i < 7; i++){
            if(nodo->hijos[i] != NULL){
                valorMin = minMax(true, nodo->hijos[i]);
                nodo->siguiente = i;
                free(nodo->hijos[i]);
                nodo->hijos[i] = NULL;
                break;
            }
        }
        for(i; i < 7; i++){
            if(nodo->hijos[i] != NULL){
                int temp = minMax(true, nodo->hijos[i]);
                if(valorMin > temp){
                    valorMin = temp;
                    nodo->siguiente = i;
                }
                free(nodo->hijos[i]);
                nodo->hijos[i] = NULL;
            }
        }
        nodo->valor = valorMin;
        return nodo->valor;
    }
}
/*Función para generar un árbol de jugadas*/
void generarJugadas(char tablero[6][7], int nivel, char color, struct nodo* padre){
    if(nivel == dificultad){
        int i,j;
        for(i = 0; i < 6; i++){
            padre->hijos[i] = NULL;
        }
        if (color == 'A'){
            padre->valor = puntuarJugada(padre->tablero, 'R');
        }else{
            padre->valor = -puntuarJugada(padre->tablero, 'A');
        }
        return;
    }
    int i,j,k;
    for (i = 0; i < 7; i++){
        padre->hijos[i] = (struct nodo*)malloc(sizeof(struct nodo));
    }
    for(i = 0; i < 7; i++){
        for(j = 0; j < 6; j++){
            for (k = 0; k < 7; k++){
                padre->hijos[i]->tablero[j][k] = tablero[j][k];
            }
        }
    }
    for(int i = 0; i < 7; i++){
        if(tirar(padre->hijos[i]->tablero, color, i)){
            if(!gano(padre->hijos[i]->tablero, color)){
                if(color == 'R'){
                    generarJugadas(padre->hijos[i]->tablero, nivel+1, 'A', padre->hijos[i]);
                }else{
                    generarJugadas(padre->hijos[i]->tablero, nivel+1, 'R', padre->hijos[i]);
                }
            }else{
                if (color == 'A'){
                    padre->valor = puntuarJugada(padre->tablero, 'R');
                }else{
                    padre->valor = -puntuarJugada(padre->tablero, 'A');
                }
                for (j = 0; j < 7; j++){
                    padre->hijos[i]->hijos[j] = NULL;
                }
            }
        }else{
            free(padre->hijos[i]);
            padre->hijos[i] = NULL;
        }
    }
}

int puntuarJugada(char tablero[6][7], char color){
    int score=0;
//Score en Horizontal
    int x;
    int y;
    for (x = 0; x < 7; x++) {
        for(y=0;y<4;y++){
            if(tablero[x][y]==color&&tablero[x][y+1]==color&&tablero[x][y+2]==color&&tablero[x][y+3]==color){
                score+=1000;
            }else if(tablero[x][y]==color&&tablero[x][y+1]==color&&tablero[x][y+2]==color&&tablero[x][y+3]==' '){
                score+=20;
            }else if(tablero[x][y]==' '&&tablero[x][y+1]==color&&tablero[x][y+2]==color&&tablero[x][y+3]==color){
                score+=20;
            }else if(tablero[x][y]==color&&tablero[x][y+1]==' '&&tablero[x][y+2]==color&&tablero[x][y+3]==color){
                score+=20;
            }else if(tablero[x][y]==color&&tablero[x][y+1]==color&&tablero[x][y+2]==' '&&tablero[x][y+3]==color){
                score+=20;
            }else if(tablero[x][y]==color&&tablero[x][y+1]==color&&tablero[x][y+2]==' '&&tablero[x][y+3]==' '){
                score+=5;
            }else if(tablero[x][y]==color&&tablero[x][y+1]==' '&&tablero[x][y+2]==color&&tablero[x][y+3]==' '){
                score+=5;
            }else if(tablero[x][y]==color&&tablero[x][y+1]==' '&&tablero[x][y+2]==' '&&tablero[x][y+3]==color){
                score+=5;
            }else if(tablero[x][y]==' '&&tablero[x][y+1]==color&&tablero[x][y+2]==color&&tablero[x][y+3]==' '){
                score+=5;
            }
        }
    }
//score en Vertical
    for (x=0; x <=7; x++) {
        for (y = 0; y < 3; y++) {
            if(tablero[y][x]==color&&tablero[y+1][x]==color&&tablero[y+2][x]==color&&tablero[y+3][x]==color){
                score+=1000;
            }else if(tablero[y][x]==color&&tablero[y+1][x]==color&&tablero[y+2][x]==color&&tablero[y+3][x]==' '){
                score+=20;
            }else if(tablero[y][x]==color&&tablero[y+1][x]==color&&tablero[y+2][x]==' '&&tablero[y+3][x]==' '){
                score+=10;
            }else if(tablero[y][x]==color&&tablero[y+1][x]==' '&&tablero[y+2][x]==' '&&tablero[y+3][x]==' '){
                score+=5;
            }
            if(tablero[y][x]==color&&x==3){
                score+=2;
            }
        }
    }
       
    
//Score en Diagonal
int j;
for(x = 0; x < 6; x++) {
    for(j = 0; j < 7; j++) {
        if (x+3 < 6 && j+3 < 7) {
            if (tablero[x][j] == color && tablero[x+1][j+1] == color && tablero[x+2][j+2] == color && tablero[x+3][j+3] == color){
                score+=1000;
            }else if(tablero[x][j] == color && tablero[x+1][j+1] == color && tablero[x+2][j+2] == color && tablero[x+3][j+3] == ' '){
              score+=20;
            }else if(tablero[x][j] == color && tablero[x+1][j+1] == color && tablero[x+2][j+2] == ' ' && tablero[x+3][j+3] == color){
              score+=20;
            }else if(tablero[x][j] == color && tablero[x+1][j+1] == ' ' && tablero[x+2][j+2] == color && tablero[x+3][j+3] == color){
              score+=20;
            }else if(tablero[x][j] == ' ' && tablero[x+1][j+1] == color && tablero[x+2][j+2] == color && tablero[x+3][j+3] == color){
              score+=20;
            }else if(tablero[x][j] == color && tablero[x+1][j+1] == color && tablero[x+2][j+2] == ' ' && tablero[x+3][j+3] == ' '){
              score+=5;
            }else if(tablero[x][j] == color && tablero[x+1][j+1] == ' ' && tablero[x+2][j+2] == color && tablero[x+3][j+3] == ' '){
              score+=5;
            }else if(tablero[x][j] == color && tablero[x+1][j+1] == ' ' && tablero[x+2][j+2] == ' ' && tablero[x+3][j+3] == color){
              score+=5;
            }else if(tablero[x][j] == ' ' && tablero[x+1][j+1] == ' ' && tablero[x+2][j+2] == color && tablero[x+3][j+3] == color){
              score+=5;
            }else if(tablero[x][j] == ' ' && tablero[x+1][j+1] == color && tablero[x+2][j+2] == ' ' && tablero[x+3][j+3] == color){
              score+=5;
            }else if(tablero[x][j] == ' ' && tablero[x+1][j+1] == color && tablero[x+2][j+2] == color && tablero[x+3][j+3] == ' '){
              score+=5;
            }
        }
    }
}

    return score;
}
