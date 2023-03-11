#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const ll m=1e9+7;

ll f[N];

void runcase(){
    ll n;
    cin >> n;
    cout << f[n]*n%m*(n-1)%m << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    f[0]=1;
    for(int i=1;i<N;i++)f[i]=f[i-1]*i%m;
    int t(1);
    cin >> t;
    while(t--)runcase();
}