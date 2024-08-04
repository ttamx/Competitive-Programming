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
    vector a(3,vector<int>(n));
    for(auto &x:a)for(auto &y:x)cin >> y;
    ll s=(accumulate(a[0].begin(),a[0].end(),0LL)+2)/3;
    vector<int> ord{0,1,2};
    do{
        vector<pair<int,int>> ans(3);
        int i=0,p=0,cnt=0;
        ll sum=0;
        for(auto x:ord){
            while(i<n&&sum<s){
                sum+=a[x][i];
                i++;
            }
            if(sum>=s){
                ans[x]={p,i-1};
                sum=0;
                cnt++;
                p=i;
            }
        }
        if(cnt<3)continue;
        for(auto [l,r]:ans)cout << l+1 << " " << r+1 << " ";
        cout << "\n";
        return;

    }while(next_permutation(ord.begin(),ord.end()));
    cout << "-1\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}