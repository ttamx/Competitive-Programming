#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int mob[N];
bool composite[N];
vector<int> divisors[N];
ll f[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(!composite[i])mob[i]=1;
        divisors[i].emplace_back(i);
        for(int j=i*2;j<N;j+=i){
            mob[j]-=mob[i];
            composite[j]=true;
            divisors[j].emplace_back(i);
        }
    }
    for(int i=1;i<N;i++){
        for(auto j:divisors[i]){
            f[i]+=(i/j-1)*mob[j];
        }
        f[i]+=f[i-1];
    }
    int q;
    cin >> q;
    while(q--){
        int l,r;
        cin >> l >> r;
        cout << f[r]-f[l-1] << "\n";
    }
}