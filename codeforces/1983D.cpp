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
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    auto sorted=[&](vector<int> a){
        sort(a.begin(),a.end());
        return a;
    };
    if(sorted(a)!=sorted(b))return void(cout << "NO\n");
    map<int,int> pos;
    for(int i=0;i<n;i++)pos[b[i]]=i;
    auto swap2=[&](int i,int j){
        swap(b[i],b[j]);
        pos[b[i]]=i;
        pos[b[j]]=j;
    };
    for(int i=0;i+1<n;i++){
        int p=pos[a[i]];
        int d=p-i;
        if(d>0){
            d--;
            swap(a[n-1],a[n-2]);
            swap2(p-1,p);
        }
        if(d>0){
            swap(a[n-1],a[n-d-1]);
            swap2(i,p-1);
        }
    }
    cout << (a==b?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}