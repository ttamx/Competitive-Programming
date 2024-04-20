#include<bits/stdc++.h>

using namespace std;

int main(){
    int n=5,q=100;
    cout << n << "\n";
    for(int i=1;i<=n;i++)cout << rand()%3 << " \n"[i==n];
    for(int i=0;i<n-1;i++)cout << i << " " << i+1 << "\n";
    cout << q << "\n";
    for(int i=0;i<q;i++){
        cout << rand()%n << " " << rand()%3 << "\n";
    }
}