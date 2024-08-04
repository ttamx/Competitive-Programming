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
    map<int,vector<int>> mp;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        mp[x%k].emplace_back(x);
    }
    int odd=0;
    ll ans=0;
    for(auto &[_,v]:mp){
        sort(v.begin(),v.end());
        if(v.size()%2){
            if(n%2){
                if(++odd>1)return void(cout << "-1\n");
            }else{
                return void(cout << "-1\n");
            }
            ll sum=0;
            for(int i=0;i+1<v.size();i+=2){
                sum+=(v[i+1]-v[i])/k;
            }
            ll mn=sum;
            int t=1;
            for(int i=v.size()-2;i>=0;i--){
                if(t)sum-=(v[i]-v[i-1])/k;
                ll res=sum;
                if(t)res+=(v[i+1]-v[i-1])/k;
                mn=min(mn,res);
                if(t)sum+=(v[i+1]-v[i])/k;
                t^=1;
            }
            ans+=mn;
        }else{
            for(int i=0;i<v.size();i+=2){
                ans+=(v[i+1]-v[i])/k;
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}