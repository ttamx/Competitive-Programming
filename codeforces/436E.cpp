#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=LLONG_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<array<ll,3>> a(n,{0,0,0});
    for(auto &x:a){
        for(int i=1;i<=2;i++){
            cin >> x[i];
        }
    }
    vector<int> b(n);
    set<pair<ll,int>> s[3][3];
    auto insert=[&](int i){
        int j=b[i];
        for(int k=0;k<=2;k++){
            if(j!=k){
                s[j][k].emplace(a[i][k]-a[i][j],i);
            }
        }
    };
    auto erase=[&](int i){
        int j=b[i];
        for(int k=0;k<=2;k++){
            if(j!=k){
                s[j][k].erase({a[i][k]-a[i][j],i});
            }
        }
    };
    for(int i=0;i<n;i++){
        insert(i);
    }
    auto find=[&](int i,int j,int x,int y){
        for(auto [dd,kk]:s[i][j]){
            if(kk!=x&&kk!=y){
                return make_pair(dd,kk);
            }
        }
        return make_pair(INF,-1);
    };
    ll ans=0;
    for(int t=0;t<m;t++){
        ll best=INF;
        vector<pair<int,int>> cands;
        for(int i=0;i<2;i++){
            if(s[i][i+1].empty())continue;
            auto [d,ii]=*s[i][i+1].begin();
            if(d<best){
                best=d;
                cands.clear();
                cands.emplace_back(ii,i+1);
            }
        }
        for(int si=0;si<=2;si++){
            for(int ei=0;ei<=2;ei++){
                if(si==ei||s[si][ei].empty())continue;
                auto [di,i]=*s[si][ei].begin();
                for(int sj=0;sj<=2;sj++){
                    for(int ej=0;ej<=2;ej++){
                        if(sj==ej||s[sj][ej].empty())continue;
                        if(ei-si+ej-sj!=1)continue;
                        auto [dj,j]=find(sj,ej,i,-1);
                        if(j==-1)continue;
                        ll d=di+dj;
                        if(d<best){
                            best=d;
                            cands.clear();
                            cands.emplace_back(i,ei);
                            cands.emplace_back(j,ej);
                        }
                    }
                }
            }
        }
        ans+=best;
        for(auto [i,j]:cands){
            erase(i);
            b[i]=j;
            insert(i);
        }
    }
    cout << ans << "\n";
    for(auto x:b)cout << x;
    cout << "\n";
}