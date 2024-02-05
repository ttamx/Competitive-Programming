#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

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

void runcase(){
    int n,k;
    cin >> n >> k;
    vl a(n);
    for(auto &x:a)cin >> x;
    auto check=[&](ll m){
        vi b(n),c(n);
        for(int t=0;t<2;t++){
            priority_queue<int> pq;
            ll sum=0;
            for(int i=0;i<n;i++){
                pq.emplace(a[i]);
                sum+=a[i];
                while(sum>m){
                    sum-=pq.top();
                    pq.pop();
                }
                b[i]=pq.size();
            }
            swap(b,c);
            reverse(all(a));
        }
        if(b.back()>=k||c.back()>=k)return true;
        reverse(all(c));
        for(int i=1;i<n;i++)if(b[i-1]+c[i]>=k)return true;
        return false;
    };
    ll l=0,r=accumulate(all(a),0LL);
    while(l<r){
        ll m=(l+r)/2;
        if(check(m))r=m;
        else l=m+1;
    }
    cout << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}