#include<bits/stdc++.h>

using namespace std;

typedef long double ld;

const int G=20;
const int N=1e5+5;

int n,g;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed;
    string s;
    cin >> s;
    n=s.size();
    if(n%2==0){
        cout << 0.5l*(n/2)*(n/2-1);
    }else{
        cout << 0.5l*(1.l*(n/2)*(n/2-1)+(n/2));
    }
}