#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=998244353;

struct Fenwick{
    int n;
    vector<int> t;
    void init(int _n){
        n=_n;
        t.assign(n+1,0);
    }
    void update(int i,int v){
        for(i++;i<=n;i+=i&-i){
            t[i]=(t[i]+v)%MOD;
        }
    }
    int query(int i){
        int res=0;
        for(i++;i>0;i-=i&-i){
            res=(res+t[i])%MOD;
        }
        return res;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<int> vals;
    vector<vector<pair<int,int>>> or_val(n);
    or_val[0].emplace_back(a[0],0);
    for(int i=1;i<n;i++){
        auto tmp=or_val[i-1];
        auto &cur=or_val[i];
        tmp.emplace_back(a[i],i);
        for(auto &[x,j]:tmp){
            x|=a[i];
        }
        sort(tmp.begin(),tmp.end());
        for(auto [x,j]:tmp){
            if(cur.empty()||x>cur.back().first){
                cur.emplace_back(x,j);
            }
        }
    }
    for(auto &v:or_val){
        for(auto [x,i]:v){
            vals.emplace_back(x);
        }
    }
    sort(vals.begin(),vals.end());
    vals.erase(unique(vals.begin(),vals.end()),vals.end());
    Fenwick f;
    f.init(vals.size());
    vector<vector<pair<int,int>>> upd(n);
    auto getid=[&](int x){
        return lower_bound(vals.begin(),vals.end(),x)-vals.begin();
    };
    vector<vector<pair<int,int>>> dp(n);
    for(int i=1;i<n;i++){
        int j=i;
        for(auto [x,p]:or_val[i]){
            x=getid(x);
            if(j>=1)upd[j-1].emplace_back(i,x);
            if(p>=2)upd[p-2].emplace_back(-i,x);
            else if(p==0)dp[i].emplace_back(x,1);
            j=p-1;
        }
    }
    dp[0].emplace_back(getid(a[0]),1);
    for(int i=0;i<n;i++){
        for(auto [j,x]:dp[i]){
            f.update(j,x);
        }
        for(auto [j,x]:upd[i]){
            int val=f.query(x);
            if(j<0)j=-j,val=MOD-val;
            dp[j].emplace_back(x,val);
        }
    }
    int ans=0;
    for(auto [i,x]:dp[n-1]){
        ans=(ans+x)%MOD;
    }
    cout << ans;
}