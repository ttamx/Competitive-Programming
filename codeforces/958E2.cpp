#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using V = vector<ll>;
using T = array<array<V,2>,2>;

const int N=5e5+5;
const ll INF=2e9;

int n;
ll a[N];

V merge(V a,V b){
    if(a.empty()||b.empty())return {};
    V c{a[0]+b[0]};
    int i=1,j=1;
    while(i<a.size()||j<b.size()){
        if(j==b.size()||(i<a.size()&&a[i]-a[i-1]<b[j]-b[j-1])){
            c.emplace_back(a[i]-a[i-1]);
            i++;
        }else{
            c.emplace_back(b[j]-b[j-1]);
            j++;
        }
    }
    for(int i=1;i<c.size();i++){
        c[i]+=c[i-1];
    }
    return c;
}

void upd(V &a,V b){
    for(int i=0;i<b.size();i++){
        if(i==a.size())a.emplace_back(b[i]);
        else a[i]=min(a[i],b[i]);
    }
}

T dnc(int l,int r){
    T res{};
    if(l==r){
        res[0][0]={0};
        res[1][0]={a[l]};
        res[0][1]={-a[l]};
    }else{
        int m=(l+r)/2;
        auto vl=dnc(l,m);
        auto vr=dnc(m+1,r);
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                res[i][j]=merge(vl[i][0],vr[0][j]);
                auto v=merge(vl[i][1],vr[1][j]);
                v.insert(v.begin(),INF);
                upd(res[i][j],v);
            }
        }
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int k,n;
    cin >> k >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    sort(a+1,a+n+1);
    cout << dnc(1,n)[0][0][k] << "\n";
}