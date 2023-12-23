#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;
const int M=1e5+5;

int n,m;
int a[N],pos[N];
ll ans[M];
ll all;

struct item{
    int t,v,p,i;
    item(int t,int v,int p,int i):t(t),v(v),p(p),i(i){}
    bool operator<(const item &o)const{
        return t>o.t;
    }
};

vector<item> v;

struct fenwick{
    int t[N];
    void add(int i,int v){
        while(i<=n)t[i]+=v,i+=i&-i;
    }
    int read(int i){
        int res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f;

void solve(int l,int r){
    if(l==r)return;
    int m=(l+r)/2;
    solve(l,m);
    solve(m+1,r);
    vector<item> res;
    for(int i=l,j=m+1;i<=m||j<=r;){
        if(j>r||(i<=m&&v[i].v>v[j].v)){
            res.emplace_back(v[i]);
            f.add(v[i].p,1);
            i++;
        }else{
            res.emplace_back(v[j]);
            ans[v[j].i]+=f.read(v[j].p-1);
            j++;
        }
    }
    for(int i=l;i<=m;i++)f.add(v[i].p,-1);
    for(int i=l;i<=r;i++)v[i]=res[i-l];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    while(cin >> n >> m){
        for(int i=1;i<=n;i++){
            cin >> a[i];
            pos[a[i]]=i;
        }
        for(int i=n;i>=1;i--){
            all+=f.read(a[i]);
            f.add(a[i],1);
        }
        for(int i=1;i<=n;i++)f.add(i,-1);
        for(int i=0;i<m;i++){
            int x;
            cin >> x;
            v.emplace_back(i,x,pos[x],i+1);
            pos[x]=0;
        }
        for(int i=1;i<=n;i++)if(pos[i])v.emplace_back(m,i,pos[i],0);
        sort(v.begin(),v.end());
        solve(0,n-1);
        for(auto &x:v)swap(x.v,x.p);
        sort(v.begin(),v.end());
        solve(0,n-1);
        for(int i=1;i<=m;i++){
            cout << all << "\n";
            all-=ans[i];
            ans[i]=0;
        }
        all=0;
        v.clear();
    }
}