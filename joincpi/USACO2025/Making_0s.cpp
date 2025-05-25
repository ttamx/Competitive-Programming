#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int INF=INT_MAX/2;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    auto rec=[&](auto &&self,int l,int r)->tuple<ll,ll,ll> {
        if(l==r){
            return make_tuple(0LL,a[l],a[l]);
        }
        int gap=(r-l+1)/4;
        vector<ll> p;
        vector<pair<ll,ll>> v;
        ll base=0;
        for(int t=0;t<4;t++){
            auto [val,vl,vr]=self(self,l+t*gap,l+(t+1)*gap-1);
            p.emplace_back(vl);
            p.emplace_back(vr);
            v.emplace_back(vl,vr);
            base+=val;
        }
        sort(p.begin(),p.end());
        int mid=p.size()/2-1;
        ll pl=p[mid],pr=p[mid+1];
        for(auto [vl,vr]:v){
            if(vr<pl)base+=pl-vr;
            if(vl>pl)base+=vl-pl;
        }
        return make_tuple(base,pl,pr);
    };
    auto [val,vl,vr]=rec(rec,0,n-1);
    if(vl>0)val+=vl;
    if(vr<0)val-=vr;
    cout << val << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}