#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll anillo(ll n){
    //formula para la diagonal principal de la matriz.
    return n*n-n+1;
}

int main(){
    int t;
    cin >> t;

    //stack de entradas
    vector <pair<ll,ll>> in;
    ll x,y;
    for(int i = 0; i<t; i++){
        cin >> y >> x;
        in.push_back({y,x});
    }

    // &p vs p: &p referencia al real, p lo copia. (esfuerzo innecesario)
    //calculo y muestro coordenadas
    for(auto &p: in){
        if(max(p.first, p.second) % 2 == 0){
            if(p.first > p.second){
                cout << anillo(max(p.first,p.second)) + max(p.first,p.second) - min(p.first,p.second) << "\n";
            } else if(p.first < p.second){
                cout << anillo(max(p.first,p.second)) - max(p.first,p.second) + min(p.first,p.second) << "\n";
            }
        } else{
            if(p.first > p.second){
                cout << anillo(max(p.first,p.second)) - max(p.first,p.second) + min(p.first,p.second) << "\n";
            } else if(p.first < p.second){
                cout << anillo(max(p.first,p.second)) + max(p.first,p.second) - min(p.first,p.second) << "\n";
            }
        }
        if(p.first == p.second){
            cout << anillo(max(p.first, p.second)) << "\n";
        }
    }
    return 0;
}
