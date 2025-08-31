#include<bits/stdc++.h>

using namespace std;

const int N=2005;
const int M=4005;

int n,m;
int st[N][M],ed[N][M];
queue<pair<int,int>> q;
int cl[N][M],cr[N][M];
int vis[N][M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        int l,r;
        char dl,dr;
        cin >> l >> dl >> r >> dr;
        for(int t=0;t<2*m;t++){
            st[i][t]=l,ed[i][t]=r;
            if(dl=='R'&&dr=='L'&&l+1==r){
                dl='L',dr='R';
            }else{
                if(dl=='R'&&dr=='L'&&l==r){
                    dl='L',dr='R';
                }
                if(dl=='L'&&l==0){
                    dl='R';
                }
                if(dr=='R'&&r==m){
                    dr='L';
                }
                l+=(dl=='L'?-1:1);
                r+=(dr=='L'?-1:1);
            }
            assert(0<=l&&l<=m);
            assert(0<=r&&r<=m);
            assert(l<=r);
        }
    }
    for(int t=0;t<2*m;t++){
        st[0][t]=0,ed[0][t]=m;
    }
    for(int i=0;i<=n;i++){
        for(int t=0;t<2*m;t++){
            cl[i][t]=m,cr[i][t]=0;
        }
    }
    q.emplace(0,0);
    cl[0][0]=0,cr[0][0]=m;
    while(!q.empty()){
        auto [i,t]=q.front();
        q.pop();
        if(i==n){
            cout << t+1 << "\n";
            exit(0);
        }
        int tt=t%(2*m);
        int l=cl[i][tt],r=cr[i][tt];
        int nt=(t+1)%(2*m);
        for(int d=0;d<2;d++){
            int nl=max(l,st[i+d][nt]);
            int nr=min(r,ed[i+d][nt]);
            if(nl+1<nr&&(nl<cl[i+d][nt]||cr[i+d][nt]<nr)){
                cl[i+d][nt]=min(cl[i+d][nt],nl);
                cr[i+d][nt]=max(cr[i+d][nt],nr);
                if(vis[i+d][nt]!=t+1){
                    q.emplace(i+d,t+1);
                    vis[i+d][nt]=t+1;
                }
            }
        }
    }
    cout << -1 << "\n";
}