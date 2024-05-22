#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const ll INF=1e18;

int n,q;
ll d,a,b;
int p[N];
ll ans[N];
ll pos=0,cost=0;
ll l[N],r[N];
vector<pair<ll,int>> qr;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    cin >> d >> a >> b;
    for(int i=1;i<=n;i++)cin >> l[i] >> r[i];
    for(int i=1;i<=q;i++){
        ll x;
        cin >> x;
        qr.emplace_back(x,i);
    }
    sort(qr.rbegin(),qr.rend());
    for(int i=1;i<=n;i++){
        while(!qr.empty()&&qr.back().first<l[i]){
            auto [x,i]=qr.back();
            qr.pop_back();
            if(x<pos)ans[i]=-1;
            else ans[i]=cost+x-pos;
        }
        ll mn=pos+
    }
    for(auto [x,i]:qr)ans[i]=-1;
}