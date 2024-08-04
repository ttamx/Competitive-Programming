#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=3e5+5;

int n,g,t;
int a[N],s[N],e[N],v[N],l[N],r[N];
vector<int> comp[N],res[N];

struct Fenwick{
    ll t[N];
    void update(int i,int v){
        for(;i<=n;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        ll res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
    void clear(){
        for(int i=1;i<=n;i++)t[i]=0;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> g >> n;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        comp[x].emplace_back(i);
    }
    for(int i=1;i<=g;i++)cin >> a[i];
    cin >> t;
    for(int i=1;i<=t;i++)cin >> s[i] >> e[i] >> v[i];
    for(int i=1;i<=g;i++)l[i]=1,r[i]=t+1;
    while(true){
        bool done=true;
        for(int i=1;i<=g;i++)if(l[i]<r[i]){
            res[(l[i]+r[i])/2].emplace_back(i);
            done=false;
        }
        if(done)break;
        for(int i=1;i<=t;i++){
            f.update(e[i]+1,-v[i]);
            f.update(s[i],v[i]);
            if(s[i]>e[i])f.update(1,v[i]);
            for(auto j:res[i]){
                ll sum=0;
                for(auto k:comp[j])sum+=f.query(k);
                if(sum>=a[j])r[j]=i;
                else l[j]=i+1;
            }
            res[i].clear();
        }
        f.clear();
    }
    for(int i=1;i<=g;i++){
        if(l[i]>t)cout << "sad\n";
        else cout << l[i] << "\n";
    }
}