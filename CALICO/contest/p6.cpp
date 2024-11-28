#include "template.hpp"

using namespace std;

const int N=1e5+5;

int phi[N];
ll dp[N+1];

void runcase(){
    int k;
    cin >> k;
    ll l=0,r=N;
    while(l<r){
        ll m=(l+r)/2;
        if(m*m-dp[m]>=k){
            r=m;
        }else{
            l=m+1;
        }
    }
    cout << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=1;i<N;i++){
        phi[i]=i;
        dp[i]+=phi[i];
        dp[i+1]+=dp[i];
        for(int j=i*2;j<N;j+=i){
            phi[j]-=phi[i];
        }
    }
    cerr << (ll)1e10-dp[int(1e5)] << "\n";
    int t;
    cin >> t;
    while(t--)runcase();
}