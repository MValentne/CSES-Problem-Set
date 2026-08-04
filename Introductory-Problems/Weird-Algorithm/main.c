/*
 * Uso esta consigna como excusa para probar la plataforma
 * Tambien se prueba con los tests y el script cses-test
 * Se estudia la forma de evaluacion de estos tests
 */

#include <stdio.h>

int main(){
    //Lo primero es definir una entrada directa para el archivo .in
    long long n;
    if (scanf("%lld", &n) != 1) {
        return 0;
    }

    while(n != 1){
        printf("%lld ", n);
        if(n%2 == 0) {
            n = n/2;
        } else {
            n = (n*3)+1;
        }
    }

    //Revisar los caracteres de salida adecuados en el .out
    printf("%lld \n", n);
    return 0;
}
