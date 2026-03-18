#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int B=20;
const int S=700;

int n,q;
int a[N],cl[N],cr[N];
int op[N],ql[N],qr[N];
int pos[B][B];
vector<pair<int,int>> event[N];
vector<int> eqr[N];
int ans[N];

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
}fw;

inline void build(){
    for(int x=0;x<B;x++){
        for(int y=0;y<B;y++){
            pos[x][y]=0;
        }
    }
    for(int i=1;i<=n;i++){
        cl[i]=1;
        for(int x=0;x<B;x++){
            if(a[i]>>x&1)continue;
            for(int y=0;y<B;y++){
                if(a[i]>>y&1){
                    cl[i]=max(cl[i],pos[y][x]+1);
                }
            }
        }
        for(int x=0;x<B;x++){
            if(a[i]>>x&1)continue;
            for(int y=0;y<B;y++){
                if(a[i]>>y&1){
                    pos[x][y]=i;
                }
            }
        }
    }
    for(int x=0;x<B;x++){
        for(int y=0;y<B;y++){
            pos[x][y]=n+1;
        }
    }
    for(int i=n;i>=1;i--){
        cr[i]=n;
        for(int x=0;x<B;x++){
            if(a[i]>>x&1)continue;
            for(int y=0;y<B;y++){
                if(a[i]>>y&1){
                    cr[i]=min(cr[i],pos[y][x]-1);
                }
            }
        }
        for(int x=0;x<B;x++){
            if(a[i]>>x&1)continue;
            for(int y=0;y<B;y++){
                if(a[i]>>y&1){
                    pos[x][y]=i;
                }
            }
        }
    }
    fw.init();
    for(int i=1;i<=n;i++){
        event[i].emplace_back(cl[i],+1);
        event[i].emplace_back(i+1,-1);
        event[cr[i]+1].emplace_back(cl[i],-1);
        event[cr[i]+1].emplace_back(i+1,+1);
    }
    for(int i=1;i<=q;i++){
        if(op[i]==2){
            eqr[qr[i]].emplace_back(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(auto [j,v]:event[i]){
            fw.update(j,v);
        }
        vector<pair<int,int>>().swap(event[i]);
        for(auto j:eqr[i]){
            ans[j]=fw.query(ql[j]);
        }
        vector<int>().swap(eqr[i]);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=q;i++){
        cin >> op[i] >> ql[i] >> qr[i];
        assert(op[i]==2);
    }
    // for(int st=1,ed=S;st<=q;st+=S,ed+=S){
    //     ed=min(ed,q);
    // }
    build();
    for(int i=1;i<=q;i++){
        cout << ans[i] << "\n";
    }
}