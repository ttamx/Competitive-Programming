#include<bits/stdc++.h>
 
using namespace std;

typedef long long ll;
typedef __int128_t i128;

const i128 inf=1e18;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    int st=0;
    while(st<n&&a[st]==1)st++;
    if(st==n)return void(cout << "1 1\n");
    i128 mul=1,sub=0;
    tuple<i128,int,int> ans(0,0,0);
    vector<tuple<i128,i128,int>> vec;
    for(int i=st;i<n;i++){
        if(mul>=inf&&a[i]!=1){
            ans={inf,st,i};
            continue;
        }
        mul=min(mul*a[i],inf);
        sub+=a[i];
        for(auto &[m,c,id]:vec){
            m=min(m*a[i],inf);
            c+=a[i];
        }
        if(a[i]==1)continue;
        vec.emplace_back(a[i],a[i],i);
        for(auto &[m,c,id]:vec){
            ans=max(ans,{m-c,id,i});
        }
    }
    auto [v,l,r]=ans;
    cout << l+1 << " " << r+1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}