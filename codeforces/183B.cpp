#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<pair<ll,ll>> a(m);
    for(auto &[x,y]:a){
        cin >> x >> y;
    }
    auto cross=[&](pair<ll,ll> a,pair<ll,ll> b){
        return a.first*b.second-a.second*b.first;
    };
    auto cross2=[&](pair<ll,ll> a,pair<ll,ll> b,pair<ll,ll> o){
        a.first-=o.first,a.second-=o.second;
        b.first-=o.first,b.second-=o.second;
        return cross(a,b);
    };
    vector<ll> b;
    for(int i=0;i<m;i++){
        auto [x1,y1]=a[i];
        for(int j=0;j<i;j++){
            auto [x2,y2]=a[j];
            if(y1==y2)continue;
            ll num=y1*(x1-x2);
            ll den=y2-y1;
            if(den<0){
                num=-num;
                den=-den;
            }
            if(num%den==0){
                ll v=x1+num/den;
                if(1<=v&&v<=n){
                    b.emplace_back(v);
                }
            }
        }
    }
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    ll ans=n;
    for(auto x:b){
        auto cross2=[&](pair<ll,ll> a,pair<ll,ll> b){
            a.first-=x,b.first-=x;
            return cross(a,b);
        };
        sort(a.begin(),a.end(),[&](pair<ll,ll> a,pair<ll,ll> b){
            return cross2(a,b)<0;
        });
        int mx=0;
        for(int i=0;i<m;i++){
            int j=i;
            while(j+1<m&&cross2(a[j],a[j+1])==0){
                j++;
            }
            mx=max(mx,j-i);
            i=j;
        }
        ans+=mx;
    }
    cout << ans << "\n";
}