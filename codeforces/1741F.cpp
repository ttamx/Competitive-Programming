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
    int n;
    cin >> n;
    vector<tuple<int,int,int,int,int>> a;
    for(int i=0;i<n;i++){
        int l,r,c;
        cin >> l >> r >> c;
        a.emplace_back(l,r,c,i,0);
        a.emplace_back(r,l,c,i,1);
    }
    sort(a.begin(),a.end());
    vector<int> ans(n,INF);
    for(int t=0;t<2;t++){
        pair<int,int> mx(-INF,-1),mx2(-INF,-1);
        auto update=[&](pair<int,int> x){
            if(x.second==mx.second){
                mx.first=max(mx.first,x.first);
            }else{
                mx2=max(mx2,x);
                if(mx2>mx)swap(mx,mx2);
            }
        };
        auto query=[&](int i){
            return mx.second!=i?mx.first:mx2.first;
        };
        for(auto [l,r,c,i,t]:a){
            if(t==0){
                update({r,c});
            }else{
                swap(l,r);
                ans[i]=min(ans[i],max(0,l-query(c)));
            }
        }
        reverse(a.begin(),a.end());
        for(auto &[l,r,c,i,t]:a){
            l=INF-l,r=INF-r;
            swap(l,r);
        }
    }
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}