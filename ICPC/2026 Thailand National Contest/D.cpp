#include<bits/stdc++.h>

using namespace std;

using ll = long long;

using T = array<ll,4>;

T calc(ll x,ll y){
    if(x<=0||y<=0)return {};
    ll d=min(x-1,y);
    T res{};
    for(int i=0;i<4;i++){
        ll c=d/4+(i<d%4);
        res[i]=c*2*(i+1)+c*(c-1)*4;
    }
    int s=d%4;
    x-=d+1,y-=d;
    if(x>0){
        for(auto &e:res)e+=x/4*d;
        for(int i=0;i<x%4;i++){
            res[s]+=d;
            s=(s+1)%4;
        }
    }
    if(y>0){
        for(auto &e:res)e+=y/4*(d+1);
        for(int i=0;i<y%4;i++){
            res[s]+=(d+1);
            s=(s+1)%4;
        }
    }
    return res;
}

T calc2(ll x1,ll y1,ll x2,ll y2){
    T a=calc(x2,y2);
    T b=calc(x2,y1);
    T c=calc(x1,y2);
    T d=calc(x1,y1);
    for(int i=0;i<4;i++)a[i]+=d[i]-b[i]-c[i];
    return a;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        ll x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        T res{};
        for(int rot=0;rot<4;rot++){
            T a=calc2(x1,y1,x2,y2);
            rotate(a.begin(),a.begin()+rot,a.end());
            for(int i=0;i<4;i++)res[i]+=a[i];
            tie(x1,y1,x2,y2)=make_tuple(-y2,x1,-y1,x2);
        }
        for(int i=0;i<4;i++)cout << res[i] << " \n"[i==3];
    }
}