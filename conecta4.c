#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int dificultad = 0;

struct nodo {
    char tablero[6][7];
    int valor;
    int siguiente;
    struct nodo *hijos[7];
};

struct nodo* generarJugadas(char tablero[6][7], int columna, int nivel, char color, struct nodo* padre);
bool gano(char tablero[6][7], char color);
bool tirar(char tablero[6][7], char color, int columna);
void imprimeTablero(char tablero[6][7]);
void imprimeArbol(struct nodo* raiz);
void liberarMemoria(struct nodo* raiz);
int minMax(int nivel, bool buscarMax, struct nodo* nodo);
int puntuarJugada(char tablero[6][7], int i);

bool tirar(char tablero[6][7], char color, int columna){
    int i;
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
    for (i = 5; i >= 0; i--){
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

/*Funcion que devuelve el nodo al cual va a tirar*/
int minMax(int nivel, bool buscarMax, struct nodo* nodo) {
    if (nivel == dificultad){
        int valor = nodo->valor;
        return valor;
    }
    int k = 0;
    bool todosNulos = true;
    for(k = 0; k < 7; k++){
        if(nodo->hijos[k] != NULL){
            todosNulos = false;
            break;
        }
    }
    if(todosNulos){
        return puntuarJugada(nodo->tablero, k);
    }
    if (buscarMax){
        int i = 0,j=0;
        int valorMax;
        for(i = 0; i < 7; i++){
            if(nodo->hijos[i] != NULL){
                valorMax = minMax(nivel+1, false, nodo->hijos[i]);
                nodo->siguiente=i;
                break;
            }
        }
        for(j = i; i < 7; i++){
            if(nodo->hijos[i] != NULL){
                int temp = minMax(nivel+1, false, nodo->hijos[i]);
                if(valorMax < temp){
                    valorMax = temp;
                    nodo->siguiente =  i;
                }
            }
        }
        nodo->valor = valorMax;
        return valorMax;
    }else{
        int i = 0,j=0;
        int valorMin;
        for(i = 0; i < 7; i++){
            if(nodo->hijos[i] != NULL){
                valorMin = minMax(nivel+1, false, nodo->hijos[i]);
                nodo->siguiente=i;
                break;
            }
        }
        for(j = i; i < 7; i++){
            if(nodo->hijos != NULL){
                int temp = minMax(nivel+1, true, nodo->hijos[i]);
                if(valorMin > temp){
                    valorMin = temp;
                    nodo->siguiente = i;
                }
            }
        }
        nodo->valor = valorMin;
        return valorMin;
    }
}
/*Función para generar un árbol de jugadas*/
struct nodo* generarJugadas(char tablero[6][7], int columna, int nivel, char color, struct nodo* padre){
    struct nodo* hoja = (struct nodo*)malloc(sizeof(struct nodo));
    if(hoja == NULL){
        printf("Se acabo la memoria");
        return NULL;
    }
    if(nivel == dificultad){
        int i,j;
        for(i = 0; i < 6; i++){
            hoja->hijos[i] = NULL;
            for(j = 0; j < 7; j++){
                hoja->tablero[i][j] = tablero[i][j];
            }
        }
        if(tirar(hoja->tablero, color, columna)){
            hoja->valor = puntuarJugada(hoja->tablero, columna);
            return hoja;
        }else{
            free(hoja);
            return NULL;
        }
    }
    int i,j;
    for(i = 0; i < 6; i++){
        for(j = 0; j < 7; j++){
            hoja->tablero[i][j] = tablero[i][j];
        }
    }
    if(tirar(hoja->tablero, color, columna)){
        if(gano(hoja->tablero, color)){
            for(i = 0; i < 6; i++){
                hoja->hijos[i] = NULL;
            }
            return hoja;
        }
        for(i = 0; i < 7 ; i++){
            if(nivel%2 == 0){
                hoja->hijos[i] = generarJugadas(hoja->tablero, i, nivel+1, 'A', hoja);
            }else{
                hoja->hijos[i] = generarJugadas(hoja->tablero, i, nivel+1, 'R', hoja);
            }
        }
        return hoja;
    }else{
        free(hoja);
        return NULL;
    }
}

int puntuarJugada(char tablero[6][7], int i){
  return 8;
}
