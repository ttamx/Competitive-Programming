#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n,m;
ll a[N],b[N];
ll ans;

struct Info{
    ll c0,c1;
    bool operator<(const Info &o)const{
        return c0*o.c1<o.c0*c1;
    }
    void update(const Info &o){
        c0+=o.c0,c1+=o.c1;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    for(int i=0;i<m;i++){
        cin >> b[i];
    }
    ans+=a[0]*(m-1)+b[0]*(n-1);
    vector<Info> c,d;
    for(int i=1;i<n;i++){
        Info cur{a[i]-a[i-1],1};
        while(!c.empty()&&cur<c.back()){
            cur.update(c.back());
            c.pop_back();
        }
        c.emplace_back(cur);
    }
    for(int i=1;i<m;i++){
        Info cur{b[i]-b[i-1],1};
        while(!d.empty()&&cur<d.back()){
            cur.update(d.back());
            d.pop_back();
        }
        d.emplace_back(cur);
    }
    Info va{0,0},vb{0,0};
    for(int i=0,j=0;i<c.size()||j<d.size();){
        if(i==c.size()||(j<d.size()&&d[j]<c[i])){
            ans+=va.c0*d[j].c1;
            vb.update(d[j]);
            j++;
        }else{
            ans+=vb.c0*c[i].c1;
            va.update(c[i]);
            i++;
        }
    }
    cout << ans << "\n";
}