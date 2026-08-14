#include <bits/stdc++.h>

using namespace std;

int main(){
    int best = 0;
    //A C G T
    string s;
    cin >> s;

    // O(n)
    int consecutive = 1;
    for(int i = 0; i < size(s); i++){
        if(s[i] == s[i+1]){
            consecutive ++;
        }
        else {
            best = max(best,consecutive);
            consecutive = 1;
        }
    }

    cout << best << "\n";
}
