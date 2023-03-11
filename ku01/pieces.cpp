#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int l,w,n,m,q;
    cin >> l >> w >> n >> m >> q;
    map<int,int> cx,cy;
    vector<vector<pair<int,int>>> fac(1e5+1);
    int st=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cx[x-st]++;
        st=x;
    }
    cx[l-st]++;
    for(auto [i,v]:cx){
        if(i>1e5)break;
        for(int j=i;j<=1e5;j+=i)fac[j].push_back({i,v});
    }
    st=0;
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        cy[x-st]++;
        st=x;
    }
    cy[w-st]++;
    vector<long long> a(1e5+1);
    for(auto [i,v]:cy){
        if(i>1e5)break;
        for(int j=i;j<=1e5;j+=i){
            auto it=lower_bound(fac[j].begin(),fac[j].end(),make_pair(j/i,0));
            if(it->first*i==j)a[j]+=1ll*it->second*v;
        }
    }
    while(q--){
        int x;
        cin >> x;
        cout << a[x] << '\n';
    }
}