#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<8;i++){
        char c;
        cin >> c;
        if(c=='9'){
            cout << "F\n";
            exit(0);
        }
    }
    cout << "S\n";
}