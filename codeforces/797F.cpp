#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> a;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a.emplace_back(x,0);
    }
    ll tot=0;
    for(int i=0;i<m;i++){
        int x,c;
        cin >> x >> c;
        a.emplace_back(x,c);
        tot+=c;
    }
    if(tot<n){
        cout << -1 << "\n";
        return;
    }
    sort(a.begin(),a.end());
    vector<ll> dpl(n+1,LINF),dpr(n+1,LINF);
    dpl[0]=dpr[0]=0LL;
    ll p=a[0].first;
    for(auto [x,c]:a){
        ll d=x-p;
        p=x;
        for(int i=0;i<=n;i++){
            dpl[i]+=i*d;
            dpr[i]+=i*d;
        }
        vector<ll> ndpl(n+1,LINF),ndpr(n+1,LINF);
        if(c){
            for(int i=0;i<=n;i++){
                ndpl[i]=min(dpl[i],dpl[max(i-c,0)]);
            }
            for(int i=0;i<=n;i++){
                int j=max(i-c,0);
                ndpr[j]=min(ndpr[j],dpr[i]);
                if(j==0){
                    int rem=min(c-(i-j),n);
                    ndpl[rem]=min(ndpl[rem],dpr[i]);
                }
            }
        }else{
            for(int i=1;i<=n;i++){
                ndpl[i-1]=dpl[i];
                ndpr[i]=dpr[i-1];
            }
        }
        for(int i=n;i>=1;i--){
            ndpl[i-1]=min(ndpl[i-1],ndpl[i]);
        }
        for(int i=1;i<=n;i++){
            ndpr[i]=min(ndpr[i],ndpr[i-1]);
        }
        ndpl[0]=ndpr[0]=min(ndpl[0],ndpr[0]);
        dpl=move(ndpl),dpr=move(ndpr);
    }
    cout << min(dpl[0],dpr[0]) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}