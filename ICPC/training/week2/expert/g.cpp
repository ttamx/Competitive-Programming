#include <bits/stdc++.h>
#pragma GCC optimize("O3, unroll-loops")
using namespace std;

using ll = long long;

const int N=1e5+5;
const int S=320;

int n,sq;
int a[N];
int lb[S],rb[S];
ll dp[S][S],pre[S][N],suf[S][N];

struct Fenwick{
    int t[N];
    void init(){
        for(int i=1;i<=n;i++){
            t[i]=0;
        }
    }
    void update(int i,int v){
        for(;i<=n;i+=i&-i){
            t[i]+=v;
        }
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i){
            res+=t[i];
        }
        return res;
    }
}f;

ll brute(int l,int r){
    ll res=0;
    for(int i=r;i>=l;i--){
        res+=f.query(a[i]-1);
        f.update(a[i],+1);
    }
    for(int i=l;i<=r;i++){
        f.update(a[i],-1);
    }
    return res;
}

ll query(int l,int r){
    int bl=(l-1)/sq+1,br=(r-1)/sq+1;
    if(bl==br){
        return brute(l,r);
    }
    ll res=brute(l,rb[bl])+brute(lb[br],r);
    if(bl+1<br){
        res+=dp[bl+1][br-1];
        res+=pre[bl+1][r];
        res+=suf[br-1][l];
    }
    int cnt=0;
    for(int i=l;i<=rb[bl];i++){
        f.update(a[i],+1);
        cnt++;
    }
    for(int i=r;i>=lb[br];i--){
        res+=cnt-f.query(a[i]);
    }
    for(int i=l;i<=rb[bl];i++){
        f.update(a[i],-1);
    }
    return res;
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    while(sq*sq<n){
        sq++;
    }
    for(int i=1;i<=sq;i++){
        lb[i]=rb[i-1]+1;
        rb[i]=min(sq*i,n);
    }
    for(int i=1;i<=sq;i++){
        int cnt=0;
        f.init();
        for(int j=i;j<=sq;j++){
            ll res=0;
            for(int k=lb[j];k<=rb[j];k++){
                res+=cnt-f.query(a[k]);
                pre[i][k]=res;
            }
            for(int k=lb[j];k<=rb[j];k++){
                f.update(a[k],+1);
                cnt++;
            }
        }
    }
    for(int i=sq;i>=1;i--){
        int cnt=0;
        f.init();
        for(int j=i;j>=1;j--){
            ll res=0;
            for(int k=rb[j];k>=lb[j];k--){
                res+=f.query(a[k]-1);
                suf[i][k]=res;
            }
            for(int k=lb[j];k<=rb[j];k++){
                f.update(a[k],+1);
                cnt++;
            }
        }
    }
    for(int i=1;i<=sq;i++){
        int st=lb[i];
        int cnt=0;
        f.init();
        ll res=0;
        for(int j=i;j<=sq;j++){
            for(int k=lb[j];k<=rb[j];k++){
                res+=cnt-f.query(a[k]);
                f.update(a[k],+1);
                cnt++;
            }
            dp[i][j]=res;
        }
    }
    f.init();
    map<pair<int,int>,ll> memo;
    auto calc=[&](int l,int r)->ll {
        pair<int,int> key(l,r);
        if(!memo.count(key)){
            memo[key]=query(l,r);
        }
        return memo[key];
    };
    multiset<ll> ms;
    ms.emplace(calc(1,n));
    set<int> s;
    s.emplace(0);
    s.emplace(n+1);
    for(int i=1;i<=n;i++){
        ll ans=*ms.rbegin();
        cout << ans << " \n"[i==n];
        ll p;
        cin >> p;
        p^=ans;
        if(i==n)break;
        auto it=s.emplace(p).first;
        int l=*prev(it)+1;
        int r=*next(it)-1;
        ms.erase(ms.find(calc(l,r)));
        if(p<r){
            ms.emplace(calc(p+1,r));
        }
        if(p>l){
            ms.emplace(calc(l,p-1));
        }
    }
}

int main (){
    ios::sync_with_stdio(0); cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}