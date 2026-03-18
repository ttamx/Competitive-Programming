#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;
const int M=1e6+5;
const int Q=1e6+5;
const int INF=INT_MAX/2;

int n,m,q;
vector<pair<int,int>> qr[N];
int cl[N],cr[N];
int ans[Q];

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(i++;i<N;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(i++;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

map<int,pair<int,int>> dat;

void split(int i){
    auto it=dat.lower_bound(i);
    if(it->first!=i){
        dat[i]=it->second;
        it->second.first=i+1;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> n;
    for(int i=1;i<=n;i++){
        cin >> cl[i] >> cr[i];
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        int l,r;
        cin >> l >> r;
        qr[r].emplace_back(l,i);
    }
    dat[m+1]={0,0};
    f.update(0,m);
    for(int i=1;i<=n;i++){
        split(cl[i]-1);
        split(cr[i]);
        for(auto it=dat.lower_bound(cl[i]);it->first<=cr[i];it=dat.erase(it)){
            int vl=it->second.first;
            int vr=it->first;
            int val=it->second.second;
            f.update(val,-(vr-vl+1));
        }
        dat[cr[i]]={cl[i],i};
        f.update(i,cr[i]-cl[i]+1);
        for(auto [l,j]:qr[i]){
            ans[j]=f.query(i)-f.query(l-1);
        }
    }
    for(int i=1;i<=q;i++){
        cout << ans[i] << "\n";
    }
}