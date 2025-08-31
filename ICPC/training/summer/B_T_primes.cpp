#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;

bool composite[N];
set<ll> s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(composite[i])continue;
        s.emplace(1LL*i*i);
        for(int j=i*2;j<N;j+=i)composite[j]=true;
    }
    int n;
    cin >> n;
    while(n--){
        ll x;
        cin >> x;
        cout << (s.count(x)?"YES":"NO") << "\n";
    }
}