#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e6+5;

bool notprime[N];
vector<ll> prime;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    notprime[0]=notprime[1]=true;
    for(int i=2;i<N;i++){
        if(notprime[i])continue;
        prime.emplace_back(i);
        for(int j=i+i;j<N;j+=i)notprime[j]=true;
    }
    ll n;
    cin >> n;
    ll res=n;
    ll val=1;
    for(auto x:prime){
        int cnt=0;
        while(res%x==0){
            res/=x;
            cnt++;
        }
        cnt=(cnt+1)/2;
        while(cnt--){
            val*=x;
        }
    }
    if(res>1)val*=res;
    cout << n/val+1;
}