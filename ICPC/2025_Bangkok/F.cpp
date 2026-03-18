#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using i128 = __int128_t;

const int N=2e5+5;

int n;
ll lim;
ll a[N],b[N];

struct Fenwick{
    i128 t[N];
    void init(){
        for(int i=1;i<=n;i++)t[i]=0;
    }
    void update(int i,i128 v){
        for(;i<=n;i+=i&-i)t[i]+=v;
    }
    i128 query(int i){
        i128 res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
    int find(i128 k){
        int p=0;
        for(int i=1<<17;i>0;i>>=1)if(p+i<=n&&t[p+i]<=k)k-=t[p+=i];
        return p;
    }
}fw,fw2;

void runcase(){
    cin >> n >> lim;
    for(int i=1;i<=n;i++)cin >> a[i] >> b[i];
    fw.init();
    fw2.init();
    vector<pair<int,int>> ord;
    for(int i=1;i<=n;i++){
        ord.emplace_back(a[i],i);
    }
    sort(ord.rbegin(),ord.rend());
    ord.emplace_back(0,0);
    ll opt=0,thres=0;
    for(int i=0;i<n;i++){
        int j=ord[i].second;
        fw.update(j,b[j]);
        fw2.update(j,a[j]);
        if(ord[i].first==ord[i+1].first)continue;
        ll cur=0,hap=0;
        int p=0;
        while(p<n){
            int l=p+1,r=n+1;
            while(l<r){
                int m=(l+r)/2;
                if(cur+b[m]<=lim)r=m;
                else l=m+1;
            }
            if(l>n)break;
            ll s=fw.query(l-1);
            p=fw.find(s+lim-cur);
            assert(p>=l);
            cur+=fw.query(p)-s;
            hap+=fw2.query(p)-fw2.query(l-1);
        }
        if(hap>=opt){
            opt=hap;
            thres=ord[i+1].first;
        }
    }
    cout << opt << " " << thres << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}