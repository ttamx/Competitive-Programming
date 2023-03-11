#include<bits/stdc++.h>

using namespace std;

const int K=32000;

bool sieve[K];
vector<int> prime;

void runcase(){
    int n;
    cin >> n;
    vector<int> f(32,1);
    for(auto p:prime){
        if(p>n)break;
        int cnt=0;
        while(n%p==0){
            n/=p;
            f[cnt++]*=p;
        }
    }
    if(n>1)f[0]*=n;
    int ans=0;
    for(int i=0;i<32;i++){
        if(f[i]==1)break;
        ans+=f[i];
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<K;i++){
        if(sieve[i])continue;
        prime.push_back(i);
        for(int j=i+i;j<K;j+=i)sieve[j]=true;
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}