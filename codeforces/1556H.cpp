#include<bits/stdc++.h>

using namespace std;

const double SCALE=1.0/(1LL<<32);

mt19937 _rng(hash<string>{}("aakhgklg"));

inline int rng(int n){return uniform_int_distribution<int>(0,n-1)(_rng);}

inline double rnd(){return _rng()*SCALE;}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> d(n,n);
    vector<vector<int>> w(n,vector<int>(n));
    for(int i=0;i<k;i++)cin >> d[i];
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)cin >> w[i][j];
    int ans=1e9;
    auto timer=[&](){return clock()<5.9*CLOCKS_PER_SEC;};
    while(timer()){
        auto dd=d;
        int cur=0;
        vector<pair<int,int>> e;
        auto link=[&](int u,int v){
            assert(u<v);
            assert(dd[u]&&dd[v]);
            dd[u]--,dd[v]--;
            e.emplace_back(u,v);
            cur+=w[u][v];
        };
        for(int i=0;i<k;i++)link(i,rng(n-k)+k);
        for(int i=k+1;i<n;i++)link(rng(i-k)+k,i);
        ans=min(ans,cur);
        int counter=0;
        for(double t=1e5;timer();t*=0.99991){
            int id=rng(n-1);
            auto [u,v]=e[id];
            int res=cur-w[u][v];
            dd[u]++,dd[v]++;
            vector<int> p(n);
            iota(p.begin(),p.end(),0);
            function<int(int)> fp=[&](int u){return p[u]=p[u]==u?u:fp(p[u]);};
            for(int i=0;i<n-1;i++)if(i!=id)p[fp(e[i].second)]=fp(e[i].first);
            vector<int> a,b;
            for(int i=0;i<n;i++)if(dd[i])(fp(i)==fp(u)?a:b).emplace_back(i);
            assert(!a.empty()&&!b.empty());
            int uu=a[rng(a.size())];
            int vv=b[rng(b.size())];
            if(uu>vv)swap(uu,vv);
            res+=w[uu][vv];
            ans=min(ans,res);
            if(rnd()<exp(double(cur-res)/t)){
                counter=0;
                dd[uu]--,dd[vv]--;
                e.erase(e.begin()+id);
                e.emplace_back(uu,vv);
                cur=res;
            }else{
                if(++counter>1e4)break;
                dd[u]--,dd[v]--;
            }
        }
    }
    cout << ans;
}