#include<stdlib.h>
#include<stdio.h>
void imprime(char a []);
int revisar_jugada(int b);
void ejemplo();
/*
1|2|3
4|5|6
7|8|9
*/
char a[8];
int main(){
  ejemplo();
  int pos=0,contador=0;
  do{
    do{
      scanf("%d",&pos);
      pos--;
    }while (revisar_jugada(pos)==0);
    a[pos]='X';
    imprime(a);
    //funcion para reviar si alguien gano
    //Funcion de tirada del arbol
    //funcion para reviar si alguien gano
    contador++;
  }while(contador<9);
  printf("Empate");

  return 0;
}

int revisar_jugada(int b){
  if(a[b]!=' '){
    printf("\nLa casilla que seleccionaste ya esta ocupada");
    return 0;
  }else
  return 1;
}

void ejemplo(){
  printf("Bienvenido !\n Teclea la casilla en la cual quieres tirar, Ejemplo\n");
  int i;
  for ( i = 0; i < 9; i++) {
    a[i]=49+i;
  }
  imprime(a);
  for ( i = 0; i < 9; i++) {
    a[i]=' ';
  }
}
void imprime(char a[]){
  int i;
  for (i = 0; i < 3; i++) {
    printf("   |   |   \n");
    printf(" %c | %c | %c \n", a[3*i],a[3*i+1],a[3*i+2]);
    if (i<2)
    printf("___|___|___\n");
    else
    printf("   |   |   \n");
  }
}
