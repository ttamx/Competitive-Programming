#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

struct SuffixMin{
    map<int,int> dat;
    void insert(int i,int v){
        auto it=dat.lower_bound(i);
        if(it!=dat.end()&&it->second<=v)return;
        it=dat.insert(it,{i,v});
        it->second=v;
        while(it!=dat.begin()&&prev(it)->second>=v)dat.erase(prev(it));
    }
    int query(int i){
        auto it=dat.lower_bound(i);
        return it==dat.end()?INF:it->second;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<tuple<int,int,int>>> pos(k);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int x;
            cin >> x;
            pos[x-1].emplace_back(i,j,INF);
        }
    }
    for(auto &[x,y,v]:pos[0])v=x+y;
    for(int i=1;i<k;i++){
        for(int t=0;t<2;t++){
            for(int tt=0;tt<2;tt++){
                int p=0;
                SuffixMin ds;
                for(auto &[x,y,v]:pos[i]){
                    while(p<pos[i-1].size()&&get<0>(pos[i-1][p])<=x){
                        auto [x,y,v]=pos[i-1][p];
                        ds.insert(y,v-x+y);
                        p++;
                    }
                    v=min(v,ds.query(y)+x-y);
                }
                for(auto &[x,y,v]:pos[i])y=-y;
                for(auto &[x,y,v]:pos[i-1])y=-y;
            }
            for(auto &[x,y,v]:pos[i])x=-x;
            for(auto &[x,y,v]:pos[i-1])x=-x;
            reverse(pos[i].begin(),pos[i].end());
            reverse(pos[i-1].begin(),pos[i-1].end());
        }
    }
    int ans=INF;
    for(auto [x,y,v]:pos[k-1])ans=min(ans,v);
    cout << ans << "\n";
}