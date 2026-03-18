#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;
const int LG=20;

int n,k;
vector<int> ans;
int st[LG][N];
int cl[N],cr[N];

int query(int l,int r){
    if(l>r)return -1;
    int k=31-__builtin_clz(r-l+1);
    return max(st[k][l],st[k][r-(1<<k)+1]);
}

void dfs(int l,int r){
    if(l>r)return;
    for(int ml=cl[l],mr=min(cr[l]-1,r);ml<=mr;ml++,mr--){
        if(query(l+1,ml)<=ml&&query(ml+1,r)<=r){
            dfs(l+1,ml);
            ans.emplace_back(l);
            dfs(ml+1,r);
            return;
        }
        if(query(l+1,mr)<=mr&&query(mr+1,r)<=r){
            dfs(l+1,mr);
            ans.emplace_back(l);
            dfs(mr+1,r);
            return;
        }
    }
    cout << "IMPOSSIBLE\n";
    exit(0);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cl[i]=i;
        cr[i]=n+1;
        st[0][i]=i;
    }
    for(int i=0;i<k;i++){
        int u,v;
        string s;
        cin >> u >> v >> s;
        int t=s[0]=='R';
        if(t==0)cl[u]=max(cl[u],v);
        else cr[u]=min(cr[u],v);
        st[0][u]=max(st[0][u],v);
        if(v<=u){
            cout << "IMPOSSIBLE\n";
            exit(0);
        }
    }
    for(int i=0;i<LG-1;i++){
        for(int j=1;j+(1<<i)<=n;j++){
            st[i+1][j]=max(st[i][j],st[i][j+(1<<i)]);
        }
    }
    dfs(1,n);
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}