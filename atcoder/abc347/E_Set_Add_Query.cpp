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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vl a(n),qr(q),t(q),cnt(q);
    for(auto &x:qr)cin >> x,x--;
    set<int> s;
    for(int i=0;i<q;i++){
        if(s.emplace(qr[i]).second){
            t[i]=1;
        }else{
            s.erase(qr[i]);
            t[i]=-1;
        }
        cnt[i]=s.size();
    }
    for(int i=q-2;i>=0;i--)cnt[i]+=cnt[i+1];
    for(int i=0;i<q;i++){
        a[qr[i]]+=t[i]*cnt[i];
    }
    for(auto x:a)cout << x << " ";
}