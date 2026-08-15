#include <bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<long long> v(n);
    for (int i = 0; i < n; i++){
        cin >> v[i];
    }

    // O(n)
    long long moves = 0;
    for(int i = 0; i < n-1; i++){
        if(v[i+1] < v[i]){
            moves = moves + (v[i] - v[i + 1]);
            v[i+1] = v[i];
        }
    }

    cout << moves << "\n";
}
