#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int ingresar(char a[]){
int i, error;
do{
error = 1;
printf(a);
fflush( stdin );
error = scanf("%d", &i); //si error != 0 leyo bien
if(error == 0){
printf("Errorrrrr! debes ingresar un numero\n");
} 
}while(error == 0);
return i;
}

void llenar(int ar[], int n){
int i; 
for(i = 0;i < n; i++){
printf("En la posicion %d, ", i);
ar[i] = ingresar("ingresa un entero: ");
}
}

void imprimir(int ar[], int n){
int i; 
for(i = 0;i < n; i++){
printf("%d", ar[i]);
if(i < n - 1) printf(", ");
}
printf(".\n");
}

void entrelazar(int a[], int b[], int c[], int n){
int i; 
for(i = 0;i < n; i++){
c[2*i] = a[i];
c[2*i+1] = b[i];
}
}

int main(){
int n;
do{
n = ingresar("Indica el tamaño de los dos arreglos: ");
if(n <= 0) printf("Errorrrr! el tamnno debe ser mayor que 0\n");
}while(n <= 0);
int array1[n], array2[n], array3[2*n];
printf("Llena el arreglo 1\n");
llenar(array1, n);
printf("Llena el arreglo 2\n");
llenar(array2, n);
printf("El arreglo 1 es:\n");
imprimir(array1, n);
printf("El arreglo 2 es:\n");
imprimir(array2, n);
entrelazar(array1, array2, array3, n);
printf("El arreglo entrelazado es:\n");
imprimir(array3, 2*n); 
printf("\nEnter para salir....\n");
fflush( stdin );
getchar();
return 0;
}
