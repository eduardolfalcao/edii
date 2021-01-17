#include <stdio.h>

int soma(int a, int b){
    return a + b;
}

//n é o tamanho do array
int somaLista(int* a, int n){
    int soma = 0;   
    for(int i = 0; i < n; i++){
        soma += a[i];
    }
    return soma;
}

//n é o tamanho do array
int somaMatriz(int mat[10][10], int n){
    int soma = 0;   
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
           soma += mat[i][j];
        }
    }
    return soma;
}

int main() {
    printf("soma(5,10)=%d\n",soma(5,10));
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("somaLista(a,10)=%d\n",somaLista(a,10));
    int mat[10][10] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
    printf("somaMatriz(mat,10)=%d\n",somaMatriz(mat,10));
    return 0;
}