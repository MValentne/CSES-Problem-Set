#include <bits/stdc++.h>

using namespace std;

int main(){

    int t;
    cin >> t;

    //guardo las entradas en pares
    long long x,y;
    vector <pair<long long, long long>> v, vsorted;
    for(int i = 0; i < t; i++){
        scanf("%lld %lld", &y ,&x);
        v.push_back({y,x});
    }

    //las ordeno de menor a mayor.
    vsorted = v;
    sort(vsorted.begin(), vsorted.end());

    //creo la tabla segun el valor mas alto.
    long long highest = max((long long)vsorted.back().first, (long long)vsorted.back().second);
    //hago la tabla con dimensiones highest x highest.

    // forzado a O(n^2)
    long long matrix[highest][highest];
    matrix[0][0] = 1;
    long long counter = 1;
    long long incremental = 1;
    int i = 0;
    int j = 0;
    int paridad = 1;
    while(i < highest && j < highest){
        if(paridad % 2 == 1){
            i ++;
            counter ++;
            matrix[i][j] = counter;
            for(int n = 0; n < incremental; n++){
                j ++;
                counter ++;
                matrix[i][j] = counter;
            }
            for(int n = 0; n < incremental; n++){
                i --;
                counter ++;
                matrix[i][j] = counter;
            }
        } else {
            j ++;
            counter ++;
            matrix[i][j] = counter;
            for(int n = 0; n < incremental; n++){
                i ++;
                counter ++;
                matrix[i][j] = counter;
            }
            for(int n = 0; n < incremental; n++){
                j --;
                counter ++;
                matrix[i][j] = counter;
            }
        }
        paridad ++;
        incremental ++;
    }

    //Empezamos a resolver las salidas segun el orden de entrada
    for(auto n:v){
        cout << matrix[n.second][n.first] << "\n";
    }
    return 0;
}
