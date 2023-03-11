#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    ll n,x,m;
    cin >> n >> x;
    m=n;
    while(n>x){
        m=n+(n&-n);
        n&=m;
    }
    if(n<x)m=-1;
    cout << m << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}