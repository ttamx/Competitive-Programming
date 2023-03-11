#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

struct xy{
    ll x,y;
};

typedef vector<xy> vxy;

bool cmpx(xy a,xy b){
    if(a.x==b.x)return a.y<=b.y;
    return a.x<b.x;
}

bool cmpy(xy a,xy b){
    if(a.y==b.y)return a.x<=b.x;
    return a.y<b.y;
}

ll dist(xy a,xy b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

ll sol(vxy &vx,vxy &vy){
    int sz=vx.size();
    if(sz==1)return 1e18;
    if(sz==2)return dist(vx[0],vx[1]);
    int mid=sz/2;
    vxy vxl(vx.begin(),vx.begin()+mid+1);
    vxy vxr(vx.begin()+mid+1,vx.end());
    vxy vyl,vyr;
    for(auto tmp:vy){
        if(cmpx(tmp,vx[mid]))vyl.emplace_back(tmp);
        else vyr.emplace_back(tmp);
    }
    ll ret=min(sol(vxl,vyl),sol(vxr,vyr));
    vxy res;
    for(auto tmp:vy)if((tmp.x-vx[mid].x)*(tmp.x-vx[mid].x)<ret)res.emplace_back(tmp);
    int rsz=res.size();
    for(int i=0;i<rsz;++i){
        for(int j=i+1;j<rsz;++j){
            if((res[i].y-res[j].y)*(res[i].y-res[j].y)>=ret)break;
            ret=min(ret,dist(res[i],res[j]));
        }
    }
    return ret;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vxy v(n);
    for(auto &[x,y]:v)cin >> x >> y;
    sort(v.begin(),v.end(),cmpx);
    vxy vx=v;
    sort(v.begin(),v.end(),cmpy);
    vxy vy=v;
    cout << sol(vx,vy);
    return 0;
}