#include<bits/stdc++.h>

using namespace std;

string s[2]={"LU","DR"};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    if(n==1){
        cout << "U\n";
    }else if(n==2){
        cout << "LU\nDR\n";
    }else if(n%2==1){
        for(int i=0;i<n-2;i++){
            for(int j=0;j<n;j++){
                cout << "U."[j%2];
            }
            cout << "\n";
        }
        for(int j=0;j<n;j++){
            cout << "UD"[j%2];
        }
        cout << "\n";
        cout << "L";
        for(int j=1;j<n-1;j++){
            cout << ".D"[j%2];
        }
        cout << "R\n";
    }else{
        n--;
        for(int i=0;i<n-2;i++){
            for(int j=0;j<n;j++){
                cout << "U."[j%2];
            }
            cout << "R."[i%2];
            cout << "\n";
        }
        for(int j=0;j<n;j++){
            cout << "UD"[j%2];
        }
        cout << ".\n";
        cout << "L";
        for(int j=1;j<n-1;j++){
            cout << ".D"[j%2];
        }
        cout << "RR\n";
        for(int j=0;j<n;j++){
            cout << "D."[j%2];
        }
        cout << ".\n";
    }
}