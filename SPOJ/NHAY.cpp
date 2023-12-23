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
 
vi z_function(const string &s){
    int n=sz(s);
    vi z(n);
    for(int i=1,l=0,r=0;i<n;i++){
        if(i>r){
            l=r=i;
            while(r<n&&s[r-l]==s[r])r++;
            z[i]=r-l,r--;
        }else{
            int k=i-l;
            if(z[k]<r-i+1)z[i]=z[k];
            else{
                l=i;
                while(r<n&&s[r-l]==s[r])r++;
                z[i]=r-l,r--;
            }
        }
    }
    return z;
}
 
void runcase(){
    string a,b;
    cin >> a >> b;
    int n=sz(a),m=sz(b);
    vi z=z_function(a+"$"+b);
    bool ok=false;
    for(int i=0;i<m;i++)if(z[n+i+1]==n)cout << i << "\n",ok=true;
    if(!ok)cout << "\n";
}
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    while(cin >> n)runcase();
} 