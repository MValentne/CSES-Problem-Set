#include <bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> factorial(n);

    //Innecesario pero solicitado en consigna
    if(n == 1){
        cout << "1\n";
        return 0;
    }

    //Aqui se incluiria && n != 1
    if(n <= 3){
        cout << "NO SOLUTION\n";
        return 0;
    }

    // O(n)
    // El escenario con n == 1 se ejecuta normalmente en este proceso
    int step = 0;
    for(int i = 0; i < n; i ++){
        step += 2;
        if(step > n){
            step = 1;
        }
        factorial[i] = step;
        cout << factorial[i] << " ";
    }
    cout << "\n";

    return 0;
}
