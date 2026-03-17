#include<bits/stdc++.h>

using namespace std;

const int M=5e5+5;
const int N=2e5+5;

int n;
int t[N],v[N],w[N];
int mu[M];
vector<int> dv[M];
int cnt[M],ans[N];

void update(int i,int v){
    for(auto d:dv[i]){
        cnt[d]+=v;
    }
}

int query(int i){
    int res=0;
    for(auto d:dv[i]){
        res+=mu[d]*cnt[d];
    }
    return res;
}

void solve(int l,int r,vector<int> a){
    if(l==r){
        for(auto i:a){
            if(t[i]==3){
                ans[i]=l;
            }
        }
        return;
    }
    int mid=(l+r+1)/2;
    vector<int> b,c;
    for(auto i:a){
        if(t[i]==3){
            (query(v[i])>0?c:b).emplace_back(i);
        }else if(w[i]>=mid){
            update(v[i],t[i]==1?1:-1);
            c.emplace_back(i);
        }else{
            b.emplace_back(i);
        }
    }
    for(auto i:a){
        if(t[i]!=3&&w[i]>=mid){
            update(v[i],t[i]==1?-1:1);
        }
    }
    solve(l,mid-1,b);
    solve(mid,r,c);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    mu[1]=1;
    for(int i=1;i<M;i++){
        if(mu[i]!=0){
            for(int j=i;j<M;j+=i){
                dv[j].emplace_back(i);
            }
        }
        for(int j=i*2;j<M;j+=i){
            mu[j]-=mu[i];
        }
    }
    cin >> n;
    for(int i=1;i<=n;i++){
        char c;
        cin >> c;
        if(c=='+'){
            t[i]=1;
            cin >> v[i] >> w[i];
        }else if(c=='-'){
            t[i]=2;
            cin >> v[i] >> w[i];
        }else{
            t[i]=3;
            cin >> v[i];
        }
    }
    vector<int> a;
    for(int i=1;i<=n;i++){
        a.emplace_back(i);
    }
    solve(0,n,a);
    for(int i=1;i<=n;i++){
        if(t[i]==3){
            cout << (ans[i]?ans[i]:-1) << "\n";
        }
    }
}