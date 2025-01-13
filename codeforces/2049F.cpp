#include "template.hpp"
#include "data-structure/dsu.hpp"

struct DS{
    int cnt,l,r;
    vector<int> freq;
    void init(int i,int t){
        l=r=i;
        cnt=t;
    }
    void insert(int x){
        if(!freq.empty()){
            if(++freq[x]==1)cnt--;
        }
    }
    void erase(int x){
        if(!freq.empty()){
            if(--freq[x]==0)cnt++;
        }
    }
    void merge(const DS &o){
        l=min(l,o.l);
        r=max(r,o.r);
        if(!o.freq.empty()){
            for(int i=0;i<freq.size();i++){
                if(freq[i]==0)cnt--;
                freq[i]+=o.freq[i];
                if(freq[i]==0)cnt++;
            }
        }
    }
    bool check(){
        return cnt==0;
    }
};

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<ll> a(n);
    vector<pair<int,int>> qr(q);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &[i,x]:qr){
        cin >> i >> x;
        i--;
    }
    vector<int> ans(q);
    for(int s=1;s-1<=n;s<<=1){
        for(auto [i,x]:qr){
            a[i]+=x;
        }
        DSU dsu(n);
        vector<DS> ds(n);
        vector<bool> alive(n);
        for(int i=0;i<n;i++){
            ds[i].init(i,s);
        }
        multiset<int> ms;
        auto build=[&](int i){
            if(ds[i].freq.empty()&&dsu.sz[i]>=s){
                ds[i].freq.assign(s,0);
                for(int j=ds[i].l;j<=ds[i].r;j++){
                    ds[i].insert(a[j]);
                }
            }
        };
        auto insert=[&](int i){
            if(ds[i].check()){
                ms.emplace(dsu.sz[i]);
            }
        };
        auto erase=[&](int i){ 
            if(ds[i].check()){
                ms.erase(ms.find(dsu.sz[i]));
            }
        };
        auto update=[&](int i){
            alive[i]=true;
            build(i);
            insert(i);
        };
        auto merge=[&](int u,int v){
            if(u<0||v>=n||!alive[u]||!alive[v])return;
            u=dsu.find(u),v=dsu.find(v);
            if(u==v)return;
            erase(u),erase(v);
            if(dsu.sz[u]<dsu.sz[v]){
                swap(u,v);
            }
            ds[u].merge(ds[v]);
            dsu.merge(u,v);
            assert(!(ds[u].freq.empty()&&!ds[v].freq.empty()));
            if(!ds[u].freq.empty()&&ds[v].freq.empty()){
                for(int i=ds[v].l;i<=ds[v].r;i++){
                    ds[u].insert(a[i]);
                }
            }
            build(u);
            insert(u);
        };
        for(int i=0;i<n;i++){
            if(a[i]<s){
                update(i);
            }
        }
        for(int i=0;i+1<n;i++){
            merge(i,i+1);
        }
        for(int i=q-1;i>=0;i--){
            if(!ms.empty()){
                ans[i]=max(ans[i],*ms.rbegin());
            }
            auto [j,x]=qr[i];
            int p=dsu.find(j);
            if(alive[j]){
                erase(p);
                ds[p].erase(a[j]);
            }
            a[j]-=x;
            if(a[j]<s){
                if(alive[j]){
                    ds[p].insert(a[j]);
                    insert(p);
                }else{
                    update(j);
                    merge(j-1,j);
                    merge(j,j+1);
                }
            }
        }
    }
    for(auto x:ans){
        cout << x << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}