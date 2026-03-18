#include <bits/allocator.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int B=20;
const int S=450;

int n,q;
int a[N],b[N],cl[N],cr[N];
int op[N],ql[N],qr[N],mask[N];
vector<int> masks,pos;
int id[N];
bool mark[N];
int qs[N][S];

struct Fenwick{
    int t[N];
    void init(){
        for(int i=1;i<=n;i++)t[i]=0;
    }
    void update(int i,int v){
        for(;i<=n;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
    int query(int l,int r){
        return query(r)-query(l-1);
    }
}fw[B][B];

inline void insert(int x){
    if(!mark[x]){
        mark[x]=true;
        pos.emplace_back(x);
    }   
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        b[i]=a[i];
    }
    for(int i=1;i<=n;i++){
        for(int x=0;x<B;x++){
            if(b[i]>>x&1)continue;
            for(int y=0;y<B;y++){
                if(b[i]>>y&1){
                    fw[x][y].update(i,+1);
                }
            }
        }
    }
    for(int i=1;i<=q;i++){
        cin >> op[i] >> ql[i] >> qr[i];
        if(op[i]==1){
            for(int x=0;x<B;x++){
                if(b[ql[i]]>>x&1)continue;
                for(int y=0;y<B;y++){
                    if(b[ql[i]]>>y&1){
                        fw[x][y].update(ql[i],-1);
                        fw[x][y].update(qr[i],+1);
                    }
                }
            }
            for(int x=0;x<B;x++){
                if(b[qr[i]]>>x&1)continue;
                for(int y=0;y<B;y++){
                    if(b[qr[i]]>>y&1){
                        fw[x][y].update(qr[i],-1);
                        fw[x][y].update(ql[i],+1);
                    }
                }
            }
            swap(b[ql[i]],b[qr[i]]);
        }else{
            for(int x=0;x<B;x++){
                for(int y=0;y<x;y++){
                    if(fw[x][y].query(ql[i],qr[i])&&fw[y][x].query(ql[i],qr[i])){
                        mask[i]|=1<<x;
                        mask[i]|=1<<y;
                    }
                }
            }
        }
    }
    for(int st=1,ed=S;st<=q;st+=S,ed+=S){
        ed=min(ed,q);
        for(int i=st;i<=ed;i++){
            if(op[i]==1){
                insert(ql[i]);
                insert(qr[i]);
            }else{
                id[i]=masks.size();
                masks.emplace_back(mask[i]);
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=0;j<masks.size();j++){
                qs[i][j]=qs[i-1][j]+(!mark[i]&&((a[i]&masks[j])==masks[j]||((~a[i])&masks[j])==masks[j]));
            }
        }
        for(int i=st;i<=ed;i++){
            if(op[i]==1){
                swap(a[ql[i]],a[qr[i]]);
            }else{
                int ans=qs[qr[i]][id[i]]-qs[ql[i]-1][id[i]];
                for(auto x:pos){
                    if(ql[i]<=x&&x<=qr[i]&&((a[x]&mask[i])==mask[i]||((~a[x])&mask[i])==mask[i])){
                        ans++;
                    }
                }
                cout << ans << "\n";
            }
        }
        for(auto x:pos){
            mark[x]=false;
        }
        pos.clear();
        masks.clear();
    }
}