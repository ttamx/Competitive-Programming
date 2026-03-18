#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

const int N=50005;
const int Q=1e5+5;
const int M=30;

int n,q,m;
int a[N];
vector<pair<int,int>> qr[N];
int ans[Q];

struct Fenwick{
    int t[N];
    void init(){
        for(int i=1;i<=n;i++){
            t[i]=INF;
        }
    }
    void update(int i,int v){
        for(;i<=n;i+=i&-i)t[i]=min(t[i],v);
    }
    int query(int i){
        int res=INF;
        for(;i>0;i-=i&-i)res=min(res,t[i]);
        return res;
    }
}fw;

struct Gauss{
    int basis[M];
    int idx[M];
    void insert(int v,int id){
        for(int i=m-1;i>=0;i--){
            if(v>>i&1){
                if(basis[i]){
                    if(id<idx[i]){
                        swap(basis[i],v);
                        swap(idx[i],id);
                    }
                    v^=basis[i];
                }else{
                    basis[i]=v;
                    idx[i]=id;
                    break;
                }
            }
        }
    }
    int query(){
        int v=(1<<m)-1;
        int res=0;
        for(int i=m-1;i>=0;i--){
            if(v>>i&1){
                if(!basis[i]){
                    return INF;
                }
                v^=basis[i];
                res=max(res,idx[i]);
            }
        }
        return res;
    }
}gauss;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    int all=(1<<m)-1;
    for(int i=1;i<=n;i++){
        int k;
        cin >> k;
        while(k--){
            int x;
            cin >> x;
            a[i]|=1<<(x-1);
        }
    }
    for(int i=1;i<=q;i++){
        int l,r;
        cin >> l >> r;
        qr[l].emplace_back(r,i);
    }
    fw.init();
    int mask=0;
    for(int l=n;l>=1;l--){
        gauss.insert(a[l],l);
        int v=gauss.query();
        if(v<INF){
            fw.update(v,v-l+1);
        }
        for(auto [r,i]:qr[l]){
            ans[i]=fw.query(r);
        }
    }
    for(int i=1;i<=q;i++){
        cout << (ans[i]==INF?-1:ans[i]) << "\n";
    }
}