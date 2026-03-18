#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
string s;
vector<pair<int,int>> qr[N];
int a[N];
int ans[N];
int last[3];
vector<pair<int,int>> pre[N],suf[N];
vector<pair<int,int>> event[N];

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
    cin >> n  >> s >> q;
    for(int i=1;i<=q;i++){
        int l,r;
        cin >> l >> r;
        qr[r].emplace_back(l,i);
    }
    last[0]=last[1]=last[2]=0;
    for(int i=1;i<=n;i++){
        int x=(s[i-1]=='F'?0:s[i-1]=='G'?1:2);
        int y=last[(x+1)%3],z=last[(x+2)%3];
        if(y>=z){
            pre[i].emplace_back(1,i);
        }else{
            pre[i].emplace_back(1,y);
            pre[i].emplace_back(z+1,i);
        }
        last[x]=i;
    }
    last[0]=last[1]=last[2]=n+1;
    for(int i=n;i>=1;i--){
        int x=(s[i-1]=='F'?0:s[i-1]=='G'?1:2);
        int y=last[(x+1)%3],z=last[(x+2)%3];
        if(y<=z){
            suf[i].emplace_back(i,n);
        }else{
            suf[i].emplace_back(y,n);
            suf[i].emplace_back(i,z-1);
        }
        last[x]=i;
    }
    for(int i=1;i<=n;i++){
        for(auto [l1,r1]:pre[i]){
            for(auto [l2,r2]:suf[i]){
                event[l2].emplace_back(l1,+1);
                event[l2].emplace_back(r1+1,-1);
                event[r2+1].emplace_back(l1,-1);
                event[r2+1].emplace_back(r1+1,+1);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(auto [x,v]:event[i]){
            f.update(x,v);
        }
        for(auto [l,j]:qr[i]){
            ans[j]=f.query(l);
        }
    }
    for(int i=1;i<=q;i++){
        cout << ans[i] << "\n";
    }
}