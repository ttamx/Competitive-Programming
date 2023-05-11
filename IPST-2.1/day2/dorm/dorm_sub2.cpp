#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=3005;

ll n;
ll a[N];
ll sum=0;

void init(int N,vector<vector<int> > Req){
    n=N;
    for(auto v:Req){
        int l=v[0],r=v[1];
        l++,r++;
        a[l]++;
        a[r+1]--;
        sum+=r-l+1;
    }
    for(int i=1;i<=n;i++)a[i]+=a[i-1];
}
ll least_crowded(int P){
    ll p=P/n+1;
    ll val=a[1];
    if(p>=val)return sum;
    ll num=val/p;
    ll rem=val-num*p;
    //cerr << p << " " << val << " " << num << " " << rem << "\n";
    return n*(rem*((num+1)*(num+1))+(p-rem)*num*num);
}
