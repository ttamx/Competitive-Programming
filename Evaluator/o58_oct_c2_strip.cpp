#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> pi;
typedef tuple<int,int,int> tu;

const int W=1e5+5;
const int M=1e4+5;

int n,m,k;
int f[W],ans[M];
vector<tu> l;
vector<pi> q[W];

void add(int i,int v){
    for(;i<W;i+=i&-i)f[i]+=v;
}

int read(int i){
    int ret=0;
    for(;i>0;i-=i&-i)ret+=f[i];
    return ret;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    while(n--){
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        ++x1,++x2,++y1,++y2;
        l.emplace_back(x1,y1,1);
        l.emplace_back(x1,y2+1,-1);
        l.emplace_back(x2+1,y1,-1);
        l.emplace_back(x2+1,y2+1,1);
    }
    sort(l.begin(),l.end());
    l.emplace_back(W-1,W-1,0);
    for(int i=0;i<m;++i){
        int x,y;
        cin >> x >> y;
        ++x,++y;
        int xx = get<0>(*upper_bound(l.begin(),l.end(),tu(x,W,1)));
        q[xx].emplace_back(y,i);

    }
    int prev=0;
    for(auto [x,y,v]:l){
        if(x!=prev){
            prev=x;
            for(auto [yy,i]:q[x])ans[i]=read(yy);
        }
        add(y,v);
    }
    for(int i=0;i<m;++i)cout << ans[i] << '\n';
}
