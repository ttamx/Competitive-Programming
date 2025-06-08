#include <bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

struct SuffixMax{
    map<int,int> dat;
    void update(int i,int v){
        auto it=dat.lower_bound(i);
        if(it!=dat.end()&&v<=it->second)return;
        it=dat.insert(it,{i,v});
        it->second=v;
        while(it!=dat.begin()&&prev(it)->second<=v)dat.erase(prev(it));
    }
    int query(int i){
        auto it=dat.lower_bound(i);
        return it==dat.end()?-INF:it->second;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++)cin >> a[i];
    SuffixMax ds1,ds2;
    vector<int> dp(n+1),pre(n+1);
    ds1.update(0,0);
    for(int i=1;i<=n;i++){
        int l=max(1,i-a[i]),r=min(n,i+a[i]);
        int p=-ds1.query(l-1);
        if(p<i){
            dp[i]=max(ds2.query(p+1),i-1);
            pre[i]=p;
        }
        ds1.update(dp[i],-i);
        ds2.update(i,r);
    }
    int i=max_element(dp.begin(),dp.end())-dp.begin();
    if(dp[i]>=n){
        cout << "YES\n";
        string ans(n,'R');
        for(;i;i=pre[i])ans[i-1]='L';
        cout << ans << "\n";
    }else{
        cout << "NO\n";
    }
}