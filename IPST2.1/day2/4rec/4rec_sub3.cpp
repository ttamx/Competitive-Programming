#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2005;

vector<pair<int,int>> a;
ll qs[N][N];
set<int> sx,sy;
vector<int> vx,vy;

long long find_rec(vector<vector<int>> Point,int p,int q){
    sx.emplace(0);
    sy.emplace(0);
    int n=Point.size();
    for(auto v:Point){
        int x=v[0],y=v[1];
        a.emplace_back(x,y);
        sx.emplace(x);
        sy.emplace(y);
    }
    for(auto x:sx)vx.emplace_back(x);
    for(auto y:sy)vy.emplace_back(y);
    for(auto &[x,y]:a){
        x=lower_bound(vx.begin(),vx.end(),x)-vx.begin();
        y=lower_bound(vy.begin(),vy.end(),y)-vy.begin();
    }
    for(auto [x,y]:a){
        qs[x][y]++;
    }
    for(int i=1;i<N;i++){
        for(int j=1;j<N;j++){
            qs[i][j]+=qs[i-1][j]+qs[i][j-1]-qs[i-1][j-1];
        }
    }
    ll ans=0;
    for(int x=0;x<vx.size();x++){
        for(int y=0;y<vy.size();y++){
            ll bl=qs[x][y];
            ll tl=qs[x][N-1]-qs[x][y];
            ll br=qs[N-1][y]-qs[x][y];
            ll tr=n-tl-br-bl;
            if(abs(tl-br)<=p&&abs(tr-bl)<=q)ans++;
        }
    }
    return ans;
}
