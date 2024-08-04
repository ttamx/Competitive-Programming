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

int write(int i,int j){
    cout << "+ " << i << " " << j << endl;
    int res;
    cin >> res;
    assert(res!=-1);
    return res;
}

map<pii,int> memo;

bool compare(int i,int j){
    if(i==j)return false;
    if(memo.count({i,j}))return memo[{i,j}];
    cout << "? " << i << " " << j << endl;
    int res;
    cin >> res;
    assert(res!=-1);
    memo[{i,j}]=res;
    memo[{j,i}]=(res^1);
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vi a(n);
    iota(all(a),1);
    sort(all(a),compare);
    for(int i=1;i<n;i++){
        int x=a[0],y=a.back();
        a.pop_back();
        a.erase(a.begin());
        int z=write(x,y);
        int l=0,r=sz(a);
        while(l<r){
            int m=(l+r)/2;
            if(compare(z,a[m]))r=m;
            else l=m+1;
        }
        a.insert(a.begin()+l,z);
    }
    cout << "!" << endl;
}