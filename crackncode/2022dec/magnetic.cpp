#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m,ans;
int p[N],cnt[N];
string s;
vector<int> v;

int fp(int u){
    if(u==p[u])return u;
    return p[u]=fp(p[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    cin >> s;
    for(int i=0;i<n;i++)if(s[i]=='1')v.push_back(i);
    iota(p,p+n,0);
    for(auto i:v){
        for(int j=1;j<=m;j++){
            if(s[(i-j+n)%n]=='1')break;
            int u=fp(i),v=fp((i-j+n)%n);
            if(u==v)break;
            p[v]=u;
        }
        for(int j=1;j<=m;j++){
            if(s[(i+j)%n]=='1')break;
            int u=fp(i),v=fp((i+j)%n);
            if(u==v)break;
            p[v]=u;
        }
    }
    for(int i=0;i<n;i++){
        int u=fp(i);
        if(cnt[u]==0){
            ans++;
            cnt[u]=1;
        }
    }
    cout << ans;
}