#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<tuple<int,int,int>> vec;
    for(int i=0;i<k;i++){
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if(x1>x2)swap(x1,x2),swap(y1,y2);
        if(y1<y2)vec.emplace_back(x1,y1,0);
        else vec.emplace_back(x1,y2,1);
    }
    vector<int> p((n+m+1)*2);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp=[&](int u){
        if(p[u]==u)return u;
        return p[u]=fp(p[u]);
    };
    auto unite=[&](int u,int v){
        u=fp(u),v=fp(v);
        p[u]=v;
    };
    for(auto [x,y,t]:vec){
        if(t){
            unite(x,y+n);
            unite(x+n+m,y+n+n+m);
        }else{
            unite(x,y+n+n+m);
            unite(x+n+m,y+n);
        }
    }
    for(int i=1;i<=n+m;i++)if(fp(i)==fp(i+n+m))return void(cout << "NO\n");
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}