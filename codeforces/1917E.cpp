#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
    if(k%2)return void(cout << "No\n");
    vector<vi> a(n,vi(n));
    auto ok=[&](int i,int j){
        return (a[i][j]+a[i+1][j]+a[i][j+1]+a[i+1][j+1])==0;
    };
    if(k%4==2){
        if(k==2){
            if(n==2){
                cout << "Yes\n";
                for(int i=0;i<2;i++)for(int j=0;j<2;j++)cout << (i==j) << " \n"[j];
            }else{
                cout << "No\n";
            }
            return;
        }
        k-=6;
        for(int i=0;i<3;i++)for(int j=0;j<3;j++)a[i][j]=i!=j;
    }
    for(int i=0;i<n;i+=2)for(int j=0;j<n;j+=2)if(k&&ok(i,j)){
        k-=4;
        a[i][j]=a[i+1][j]=a[i][j+1]=a[i+1][j+1]=1;
    }
    if(k)return void(cout << "No\n");
    cout << "Yes\n";
    for(auto x:a){
        for(auto y:x)cout << y << " ";
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}