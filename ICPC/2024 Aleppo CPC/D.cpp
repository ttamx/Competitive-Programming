#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int K=1<<19;
const int MOD=1e9+7;
const int MOD2=983295767;
const int BASE=29;
const int BASE2=31;

int n;
int pw[N],pw2[N];
set<int> sz;
map<ll,int> id;
ll hsh[N];

struct Tag{
    ll add,mod;
    bool is_mod;
    Tag():add(0),mod(0),is_mod(false){}
    Tag(ll _add,ll _mod,bool _is_mod):add(_add),mod(_mod),is_mod(_is_mod){}
};

struct Segtree{
    ll t[K];
    Tag lz[K];
    void apply(int i,const Tag &v){
        if(v.is_mod){
            t[i]=v.mod;
            lz[i].mod=v.mod;
            lz[i].is_mod=true;
        }else{
            t[i]+=v.add;
            lz[i].add+=v.add;
            lz[i].mod+=v.add;
        }
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=Tag();
    }
    void modify(int l,int r,int i,int x,ll v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        push(i);
        modify(l,m,i*2,x,v);
        modify(m+1,r,i*2+1,x,v);
    }
    void modify(int x,ll v){
        modify(1,n,1,x,v);
    }
    void update(int l,int r,int i,int x,int y,const Tag &v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        int m=(l+r)/2;
        push(i);
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
    }
    void update(int x,int y,const Tag &v){
        update(1,n,1,x,y,v);
    }
    ll query(int l,int r,int i,int x){
        if(l==r)return t[i];
        int m=(l+r)/2;
        push(i);
        if(x<=m)return query(l,m,i*2,x);
        else return query(m+1,r,i*2+1,x);
    }
    ll query(int x){
        return query(1,n,1,x);
    }
}seg;

int enc(const string &s){
    int m=s.size();
    int res=0;
    for(int i=0;i<m;i++){
        res=(res+1LL*pw[i]*(s[i]-'a'+1))%MOD;
    }
    return 1LL*res*pw[N-1]%MOD;
}

int enc2(const string &s){
    int m=s.size();
    int res=0;
    for(int i=0;i<m;i++){
        res=(res+1LL*pw2[i]*(s[i]-'a'+1))%MOD2;
    }
    return 1LL*res*pw2[N-1]%MOD2;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    pw[0]=1;
    for(int i=1;i<N;i++)pw[i]=1LL*pw[i-1]*BASE%MOD;
    pw2[0]=1;
    for(int i=1;i<N;i++)pw2[i]=1LL*pw2[i-1]*BASE2%MOD2;
    cin >> n;
    for(int i=1;i<=n;i++){
        int t;
        cin >> t;
        if(t==1){
            string s;
            ll v;
            cin >> s >> v;
            int m=s.size();
            sz.emplace(m);
            hsh[i]=ll(enc(s))<<32|enc2(s);
            id[hsh[i]]=i;
            seg.modify(i,v);
        }else if(t==2){
            int x;
            cin >> x;
            id.erase(hsh[x]);
        }else if(t==3){
            int l,r;
            ll v;
            cin >> l >> r >> v;
            seg.update(l,r,Tag(0,v,true));
        }else if(t==4){
            int l,r;
            ll v;
            cin >> l >> r >> v;
            seg.update(l,r,Tag(v,0,false));
        }else if(t==5){
            string s;
            ll l,r;
            cin >> s >> l >> r;
            int m=s.size();
            vector<int> dp(m),dp2(m);
            int res=0,res2=0;
            for(int i=0;i<m;i++){
                res=(res+1LL*pw[i]*(s[i]-'a'+1))%MOD;
                dp[i]=res;
                res2=(res2+1LL*pw2[i]*(s[i]-'a'+1))%MOD2;
                dp2[i]=res2;
            }
            map<int,int> cnt;
            int ans=0;
            for(auto k:sz){
                for(int i=k-1;i<m;i++){
                    int cur=dp[i],cur2=dp2[i];
                    if(i>=k){
                        cur=(MOD+cur-dp[i-k])%MOD;
                        cur2=(MOD2+cur2-dp2[i-k])%MOD2;
                    }
                    cur=1LL*cur*pw[N-(i-k+1)-1]%MOD;
                    cur2=1LL*cur2*pw2[N-(i-k+1)-1]%MOD2;
                    auto it=id.find(ll(cur)<<32|cur2);
                    if(it!=id.end()){
                        cnt[it->second]++;
                    }
                }
            }
            for(auto [idx,x]:cnt){
                ll v=seg.query(idx);
                if(l<=v&&v<=r){
                    ans+=x;
                }
            }
            cout << ans << "\n";
        }else{
            assert(false);
        }
    }
}