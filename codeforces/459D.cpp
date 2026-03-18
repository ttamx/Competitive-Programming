#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    auto b=a;
    sort(b.begin(),b.end());
    for(auto &x:a){
        x=lower_bound(b.begin(),b.end(),x)-b.begin()+1;
    }
    vector<int> pre(n),suf(n);
    {
        vector<int> cnt(n+1);
        for(int i=0;i<n;i++){
            pre[i]=++cnt[a[i]];
        }
    }
    {
        vector<int> cnt(n+1);
        for(int i=n-1;i>=0;i--){
            suf[i]=++cnt[a[i]];
        }
    }
    long long ans=0;
    for(int i=n-1;i>=0;i--){
        ans+=f.query(pre[i]-1);
        f.update(suf[i],+1);
    }
    cout << ans << "\n";
}