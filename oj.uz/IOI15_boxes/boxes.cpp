#include "boxes.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll delivery(int N, int K, int L, int p[]) {
    vector<ll> dpl(N+2),dpr(N+2);
    for(int i=1;i<=N;i++)dpl[i]=dpl[max(0,i-K)]+min(2*p[i-1],L);
    for(int i=N;i>=1;i--)dpr[i]=dpr[min(N+1,i+K)]+min(2*(L-p[i-1]),L);
    ll ans=LLONG_MAX;
    for(int i=0;i<=N;i++)ans=min(ans,dpl[i]+dpr[i+1]);
    return ans;
}