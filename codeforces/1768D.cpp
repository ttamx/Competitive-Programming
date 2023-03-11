#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

struct fenwick{
    vector<int> t;
    int n;
    fenwick(int _n):n(_n),t(_n+1,0){}
    void add(int i,int v){
        while(i<n)t[i]+=v,i+=i&-i;
    }
    ll read(int i){
        ll res=0;
        while(i)res+=t[i],i-=i&-i;
        return res;
    }
};

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+1),pa(n+1),nxt(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        nxt[a[i]]=i;
        pa[i]=i;
    }
    function<int(int)> fp=[&](int u){
        if(u==pa[u])return u;
        return pa[u]=fp(pa[u]);
    };
    int ans=1;
    for(int i=1;i<=n;i++){
        int cur=nxt[a[i]];
        while(fp(cur)!=fp(a[i])){
            pa[fp(cur)]=fp(a[i]);
            cur=nxt[cur];
            ans++;
        }
    }
    for(int i=2;i<=n;i++){
        if(fp(i)==fp(i-1)){
            ans-=2;
            break;
        }
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}