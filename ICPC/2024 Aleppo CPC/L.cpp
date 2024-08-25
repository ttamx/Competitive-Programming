#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct Fenwick{
    int n;
    vector<ll> t;
    Fenwick(int _n):n(_n),t(n+1,0LL){}
    void update(int x,ll v){
        for(int i=x+1;i<=n;i+=i&-i){
            t[i]+=v;
        }
    }
    ll query(int x){
        ll res=0;
        for(int i=x+1;i>0;i-=i&-i){
            res+=t[i];
        }
        return res;
    }
};

struct Info{
    int l,r,t,v;
    Info(){}
    Info(int _l,int _r,int _t,int _v):l(_l),r(_r),t(_t),v(_v){}
    bool operator<(const Info& o)const{
        return t<o.t;
    }
};

void runcase(){
    int n,q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<int> base(n*2);
    for(auto &x:base)cin >> x;
    vector<Info> a;
    vector<int> qr;
    vector<ll> ans(q);
    for(int i=0;i<q;i++){
        int op;
        cin >> op;
        if(op==1){
            int l1,r1,l2,r2,v;
            cin >> l1 >> r1 >> l2 >> r2 >> v;
            l1--,l2--,r1--,r2--;
            a.emplace_back(Info(min(l1,l2),max(r1,r2),i,v));
        }else if(op==2){
            int l,r;
            cin >> l >> r;
            l--,r--;
            a.emplace_back(Info(l,r,i,0));
            qr.emplace_back(i);
            ans[i]=base[l];
        }else{
            assert(false);
        }
    }
    Fenwick f(2*n);
    vector<Info> b(q);
    function<void(int,int)> dnc=[&](int l,int r){
        if(l==r)return;
        int m=(l+r)/2;
        dnc(l,m);
        dnc(m+1,r);
        vector<pair<int,int>> op;
        for(int p=l,i=l,j=m+1;p<=r;p++){
            if(j>r||(i<=m&&a[i].l>=a[j].l)){
                b[p]=a[i];
                f.update(a[i].r,a[i].v);
                op.emplace_back(a[i].r,a[i].v);
                i++;
            }else{
                b[p]=a[j];
                ans[a[j].t]+=f.query(a[j].r);
                j++;
            }
        }
        for(auto [i,v]:op){
            f.update(i,-v);
        }
        for(int i=l;i<=r;i++){
            a[i]=b[i];
        }
    };
    sort(a.begin(),a.end());
    dnc(0,q-1);
    for(auto i:qr){
        cout << ans[i] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}