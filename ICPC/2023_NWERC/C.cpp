#include<bits/stdc++.h>

using namespace std;

using ll = long long;

ll invmod(ll x,ll mod){
    ll a=x,b=mod,u=1,v=0,q=0;
    while(b>0){
        q=a/b;
        a-=q*b;
        u-=q*v;
        swap(a,b);
        swap(u,v);
    }
    u%=mod;
    if(u<0)u+=mod;
    return u;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    int m=n;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        a[i]=i;
    }
    ll mul=1,add=0,block=1;
    auto getid=[&](ll x){
        x=(x+n-add)%n;
        if(x%block!=0)return -1;
        x/=block;
        x=(x*invmod(mul/block,m))%m;
        return a[x];
    };
    auto eliminate=[&](ll x,ll g){
        vector<pair<int,int>> c(n,{n,-1});
        for(int i=0;i<n;i++){
            if(a[i%m]!=i)continue;
            int id=(i*mul+add)%n;
            int j=(id*x)%n;
            c[j]=min(c[j],{(j+n-id)%n,i});
        }
        m/=g;
        block*=g;
        vector<int> b(m);
        for(int i=0;i<n;i++){
            int j=c[i].second;
            if(j!=-1)b[j%m]=j;
        }
        swap(a,b);
    };
    while(q--){
        char op;
        ll x;
        cin >> op >> x;
        if(op=='+'){
            add=(add+x)%n;
        }else if(op=='*'){
            ll g=gcd(x,m);
            if(g!=1)eliminate(x,g);
            mul=(mul*x)%n;
            add=(add*x)%n;
        }else if(op=='?'){
            int ans=getid(x);
            cout << (ans?ans:n) << "\n";
        }else{
            assert(false);
        }
    }
}