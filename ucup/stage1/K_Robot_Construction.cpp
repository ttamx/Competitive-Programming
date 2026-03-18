#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=3e5+5;

int n,q,d;
ll a[N],b[N];
int fa[N],id[N];
vector<int> st[N],ed[N];
set<int> s;
int buf=0;
ll ans[N],base[N];

struct Fenwick{
    ll t[N];
    void update(int i,ll v){
        for(;i<N;i++)t[i]+=v;
    }
    ll query(int i){
        ll res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

int fp(int u){
    return fa[u]=fa[u]==u?u:fp(fa[u]);
}

ll calc(int i){
    return base[i]-f.query(i);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q >> d;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=q;i++){
        int l,r;
        cin >> l >> r;
        l--,r--;
        st[l].emplace_back(i);
        ed[r].emplace_back(i);
    }
    for(int i=1;i<=n;i++){
        for(auto j:st[i]){
            id[j]=++buf;
            base[buf]=d+f.query(buf);
            s.emplace(j);
        }
        int l=1,r=buf+1;
        while(l<r){
            int m=(l+r)/2;
            if(calc(m)>=a[i]-1)r=m;
            else l=m+1;
        }
        vector<int> comp;
        auto it=s.lower_bound(l);
        while(it!=s.end()&&calc(*it)<2*a[i]-1){
            comp.emplace_back(*it);
        }
        if(!comp.empty()){
            int st=comp[0];
            int r=fp(st);
            for(int j=1;j<comp.size();j++){
                fa[fp(comp[0])]=r;
            }
            
        }
        for(auto j:ed[i]){
            ans[j]=base[id[fp(j)]]-f.query(j);
        }
    }
}