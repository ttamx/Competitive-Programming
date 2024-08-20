#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=998244353;

template<class T>
struct SegTree{
    int n;
    vector<T> t;
    SegTree(int _n):n(_n){
        int sz=1;
        while(sz<2*n)sz*=2;
        t.assign(sz,T());
        build();
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=T());
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(1,n,1);
    }
    void modify(int l,int r,int i,int x,const T &v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        modify(l,m,i*2,x,v);
        modify(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void modify(int x,const T &v){
        modify(1,n,1,x,v);
    }
    T query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return T();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    T query(int x,int y){
        return query(1,n,1,x,y);
    }
};

struct Sum{
    ll val;
    Sum():val(0LL){}
    Sum(ll _val):val(_val){}
    friend Sum operator+(const Sum &l,const Sum &r){
        return Sum((l.val+r.val)%MOD);
    }
};

struct Info{
    ll val,sz;
    Info():val(0LL),sz(1LL){}
    Info(ll _val,ll _sz):val(_val),sz(_sz){}
    friend Info operator+(const Info &l,const Info &r){
        return Info((l.val*r.sz+r.val)%MOD,(l.sz*r.sz)%MOD);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    int n=s.size();
    s=" "+s;
    int q;
    cin >> q;
    SegTree<Sum> seg1(n);
    SegTree<Info> seg2(n);
    set<int> pos;
    vector<ll> sgn(n+2,1);
    pos.emplace(0);
    pos.emplace(n+1);
    for(int i=1;i<=n;i++){
        if(s[i]=='+'){
            sgn[i+1]=1;
            pos.emplace(i);
        }else if(s[i]=='-'){
            sgn[i+1]=-1;
            pos.emplace(i);
        }else{
            int v=s[i]-'0';
            seg2.modify(i,Info(v,10));
        }
    }
    auto update=[&](int l,int r){
        if(l>r)return;
        ll val=(seg2.query(l,r).val*sgn[l]+MOD)%MOD;
        seg1.modify(l,Sum(val));
    };
    auto clear=[&](int i){
        seg1.modify(i,Sum(0));
    };
    for(auto l=pos.begin(),r=next(l);r!=pos.end();l++,r++){
        update(*l+1,*r-1);
    }
    while(q--){
        char op;
        cin >> op;
        if(op=='!'){
            int i;
            char c;
            cin >> i >> c;
            if(s[i]==c)continue;
            if(c=='+'){
                sgn[i+1]=1;
                if(s[i]=='-'){
                    int nxt=*pos.upper_bound(i);
                    update(i+1,nxt-1);
                }else{
                    auto it=pos.emplace(i).first;
                    int pre=*prev(it);
                    int nxt=*next(it);
                    update(pre+1,i-1);
                    update(i+1,nxt-1);
                    clear(i);
                }
            }else if(c=='-'){
                sgn[i+1]=-1;
                if(s[i]=='+'){
                    int nxt=*pos.upper_bound(i);
                    update(i+1,nxt-1);
                }else{
                    auto it=pos.emplace(i).first;
                    int pre=*prev(it);
                    int nxt=*next(it);
                    update(pre+1,i-1);
                    update(i+1,nxt-1);
                    clear(i);
                }
            }else{
                seg2.modify(i,Info(c-'0',10));
                if(s[i]=='+'||s[i]=='-'){
                    clear(i+1);
                    pos.erase(i);
                }
                int pre=*prev(pos.lower_bound(i));
                int nxt=*pos.upper_bound(i);
                update(pre+1,nxt-1);
            }
            s[i]=c;
        }else{
            int l,r;
            cin >> l >> r;
            auto itl=pos.lower_bound(l);
            auto itr=pos.upper_bound(r);
            if(itl==itr){
                cout << seg2.query(l,r).val << "\n";
            }else{
                itr--;
                ll ans=0;
                ans+=seg1.query(*itl+1,*itr-1).val;
                ans+=seg2.query(l,*itl-1).val;
                ans+=MOD+seg2.query(*itr+1,r).val*sgn[*itr+1];
                ans%=MOD;
                cout << ans << "\n";
            }
        }
    }
}