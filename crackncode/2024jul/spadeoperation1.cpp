#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=20005;

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
    for(int i=1;i<=n;i++){
        int x=b[i];
        int l=x-1-f.query(x),r=n-x-(i-1-f.query(x));
        ans+=min(l,r);
        f.update(x,1);
    }
    cout << ans << "\n";
}