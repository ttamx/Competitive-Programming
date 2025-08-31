#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n;
ll k;
ll a[N],qs[N];
ll best=0;
vector<pair<int,int>> ans;

ll range_sum(int l,int r){
    return qs[r]-qs[l-1];
}

ll calc_dist(int l,int r){
    if(l==r)return 0;
    if((r-l)%2==1){
        int m=(l+r)/2;
        return 2*range_sum(m+1,r)-2*range_sum(l,m)+a[m]-a[m+1];
    }else{
        int m=(l+r)/2;
        ll res=0;
        res=max(res,2*range_sum(m+2,r)-2*range_sum(l,m-1)+a[m]+a[m+1]);
        res=max(res,2*range_sum(m+1,r)-2*range_sum(l,m-2)-a[m]-a[m-1]);
        return res;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        qs[i]=qs[i-1]+a[i];
    }
    for(int i=1;i<=n;i++){
        int l=i,r=n;
        while(l<r){
            int m=(l+r+1)/2;
            if(calc_dist(i,m)<=k)l=m;
            else r=m-1;
        }
        ll cand=calc_dist(i,l);
        if(cand>best){
            best=cand;
            ans={make_pair(i,l)};
        }else if(cand==best){
            ans.emplace_back(i,l);
        }
    }
    for(auto [l,r]:ans){
        cout << l << " " << r << "\n";
    }
}