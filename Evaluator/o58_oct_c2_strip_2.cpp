#include<bits/stdc++.h>

using namespace std;

const int N=40005;
const int M=10005;
const int W=1e5+5;

int n,m,k;
int ans[M];
vector<pair<int,int>> vec[W],ask[W];

struct fenwick{
    int t[W];
    void add(int i,int v){
        i++;
        while(i<W)t[i]+=v,i+=i&-i;
    }
    int read(int i){
        i++;
        int res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=0;i<n;i++){
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        vec[x1].emplace_back(y1,1);
        vec[x1].emplace_back(y2+1,-1);
        vec[x2+1].emplace_back(y1,-1);
        vec[x2+1].emplace_back(y2+1,1);
    }
    for(int i=0;i<m;i++){
        int x,y;
        cin >> x >> y;
        ask[x].emplace_back(y,i);
    }
    for(int i=0;i<W;i++){
        for(auto [x,y]:vec[i])f.add(x,y);
        for(auto [x,y]:ask[i])ans[y]=f.read(x);
    }
    for(int i=0;i<m;i++)cout << ans[i] << "\n";
}