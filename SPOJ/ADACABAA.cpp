#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;
typedef tuple<int,int,int,int> t4;

int n,ans;
map<p2,int> f;
vector<t4> v;

void add(int x,int y,int v){
    for(int i=x;i<=n;i+=i&-i){
        for(int j=y;j<=n;j+=j&-j){
            if(f[{i,j}]==0)f[{i,j}]=v;
            else f[{i,j}]=min(f[{i,j}],v);
        }
    }
}

int read(int x,int y){
    int ret=2e9;
    for(int i=x;i>0;i-=i&-i){
        for(int j=y;j>0;j-=j&-j){
            if(f[{i,j}]!=0)ret=min(ret,f[{i,j}]);
        }
    }
    return ret;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;++i){
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        v.emplace_back(a,b,c,d);
    }
    sort(v.begin(),v.end());
    for(auto [a,b,c,d]:v){
        if(d<read(b,c)){
            add(b,c,d);
            ++ans;
        }
    }
    cout << ans;
}
