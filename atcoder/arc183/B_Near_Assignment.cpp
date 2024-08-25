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
    vector<int> a(n),b(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    for(auto &x:b){
        cin >> x;
        x--;
    }
    if(a==b)return void(cout << "Yes\n");
    set<int> s;
    for(auto x:a){
        s.emplace(x);
    }
    for(auto x:b){
        if(s.find(x)==s.end()){
            cout << "No\n";
            return;
        }
    }
    if(k==1){
        a.erase(unique(a.begin(),a.end()),a.end());
        b.erase(unique(b.begin(),b.end()),b.end());
        int p=0;
        for(auto x:b){
            while(p<a.size()&&a[p]!=x)p++;
            if(p>=a.size())return void(cout << "No\n");
            p++;
        }
        cout << "Yes\n";
        return;
    }
    vector<int> pos(n,-INF);
    for(int i=0;i<n;i++){
        if(i-pos[b[i]]<=k){
            cout << "Yes\n";
            return;
        }
        pos[b[i]]=i;
    }
    cout << "No\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}