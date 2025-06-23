#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<ll,ll>;

ll cross(P a,P b){
    return a.first*b.second-a.second*b.first;
}

ll cross(P a,P b,P o){
    a.first-=o.first;
    a.second-=o.second;
    b.first-=o.first;
    b.second-=o.second;
    return cross(a,b);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,w,h;
    cin >> n >> m >> w >> h;
    vector<P> a(n),b(m);
    vector<ll> mn(w+1,h+1),mx(w+1,-h-1);
    for(auto &[x,y]:a){
        cin >> x >> y;
        mn[x]=min(mn[x],y);
    }
    for(auto &[x,y]:b){
        cin >> x >> y;
        mx[x]=max(mx[x],y);
    }
    int l=0,r=0;
    int i=0,j=0;
    for(int p=0;p<=w;p++){
        while(a[i+1].first<p)i++;
        while(b[j+1].first<p)j++;
        if(mn[p]<=h){
            while(l<=r&&r>=mn[p])r-=2;
        }else{
            while(l<=r&&cross(a[i+1],P(p,r),a[i])>=0)r-=2;
        }
        if(mx[p]>=-h){
            while(l<=r&&l<=mx[p])l+=2;
        }else{
            while(l<=r&&cross(b[j+1],P(p,l),b[j])<=0)l+=2;
        }
        if(l>r){
            cout << "impossible\n";
            exit(0);
        }
        l--,r++;
    }
    cout << l+1 << " " << r-1 << "\n";
}