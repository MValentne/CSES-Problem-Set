#include <stdio.h>

void quicksort(long long a[], int left, int right) {
    int i = left, j = right;
    long long pivot = a[(left + right) / 2];

    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;

        if (i <= j) {
            long long tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    }

    if (left < j) quicksort(a, left, j);
    if (i < right) quicksort(a, i, right);
}

int main(){
    //cantidad de numeros
    long long n;
    scanf("%lld", &n);
    if(n < 2){
        return 0;
    }

    //secuencia de entrada
    long long secuencia[n-1];
    long long i = 0;
    while( i < n-1){
        scanf("%lld", &secuencia[i]);
        i++;
    }

    //La secuencia pasa por un ordenamiento
    quicksort(secuencia, 0, n-1);

    //Probamos caso particular con el 1
    if(secuencia[0] != 1){
        printf("1\n");
        return 0;
    }

    //recorro buscando numero faltante
    long long j = 0;
    while(j != n){
        if(secuencia[j+1] != secuencia[j] + 1){
            printf("%lld\n", secuencia[j]+1);
            return 0;
        }
        j++;
    }
    return 0;
}
