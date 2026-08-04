#include <stdio.h>

int main(){
    int n;
    printf("enter a starting value: ");
    scanf("%d", &n);
    if ((n <=1) || (n>= 10000000)){
        printf("Out of bounds.\n");
        return(1);
    }

    while(n != 1){
        printf("%d ", n);
        if(n%2 == 0) {
            n = n/2;
        } else {
            n = (n*3)+1;
        }
    }
    printf("%d\n", n);
    return 0;
}
