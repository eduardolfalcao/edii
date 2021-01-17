#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool ehPrimoDaniel(unsigned int n){
    for(int i = 2; i < n; i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
} 

bool ehPrimoMarina(unsigned int n){
    for(int i = 2; i <= sqrt(n); i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
} 

int main() {
    printf("%i",ehPrimoDaniel(7));
    return 0;
}