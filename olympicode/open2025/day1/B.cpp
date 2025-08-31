#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;
const ll INF=LLONG_MAX/2;

int n;
int a[N],b[N];
ll ans;

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<=n;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        b[a[i]]=i;
    }
    for(int i=n;i>=1;i--){
        ans+=f.query(b[i]);
        f.update(b[i],+1);
    }
    int mx=0;
    for(int i=1;i<=n;i++){
        if(b[i]>mx){
            mx=b[i];
            ans++;
        }
    }
    cout << ans-n << "\n";
}